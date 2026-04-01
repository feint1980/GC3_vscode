-- =============================================================================
--  EventPipeline.lua
--  Sequential event-to-animation pipeline.
--
--  Sits on top of TaskManager.lua — uses TM_addTask for timed steps.
--  C++ drives this the same way as LuaTaskManager (hasTasks / update pattern).
--
--  Step types:
--    "instant" : fn(data)               — runs and continues immediately
--    "async"   : fn(data, done)         — pauses until done() is called
--    "timed"   : fn(data), duration     — runs fn, pauses for duration seconds
--    "poll"    : condition()            — pauses until condition() returns true
--                fn(data) optional      — runs once when condition becomes true
--
--  Any non-poll step accepts:
--    condition = function(data) return bool end
--    If false, that step is skipped silently.
--
--  Signals (for async steps):
--    EP_SendSignal(key)       — fires done() stored under key
--
--  Poll signals (for poll steps):
--    EP_SetPollSignal(key)    — sets EP_PollSignals[key] = true
--    EP_ClearPollSignal(key)  — sets EP_PollSignals[key] = false
-- =============================================================================


-- ─── Signal tables ────────────────────────────────────────────────────────────

EP_Signals     = {}   -- async signals: stores done() functions
EP_PollSignals = {}   -- poll signals:  stores bool flags

-- Fire a stored async done() callback
function EP_SendSignal(key)
    if EP_Signals[key] then
        EP_Signals[key]()
        EP_Signals[key] = nil
    end
end

-- Set a poll signal flag to true (condition becomes true → poll step advances)
function EP_SetPollSignal(key,value)

    EP_PollSignals[key] = value
end

-- Clear a poll signal flag (reset for reuse)
function EP_ClearPollSignal(key)
    EP_PollSignals[key] = false
end

-- List all active signals (debug helper)
function EP_ListSignals()
    print("[EP_Signals]")
    for k, v in pairs(EP_Signals) do
        print("  async | " .. k .. " = " .. type(v))
    end
    for k, v in pairs(EP_PollSignals) do
        print("  poll  | " .. k .. " = " .. tostring(v))
    end
end


-- ─── Internal state ───────────────────────────────────────────────────────────

local EP_queue   = {}     -- array of { co, waiting, pollCondition, id }
local EP_running = false  -- re-entrancy guard
local EP_timerFn = nil    -- injected: fn(delaySec, callback)


-- ─── Internal: advance the queue ─────────────────────────────────────────────

local function EP_tick()
    if EP_running then return end
    EP_running = true

    while #EP_queue > 0 do
        local entry = EP_queue[1]

        if entry.waiting then
            break  -- blocked — async waiting for done(), or poll waiting for condition
        end

        local status = coroutine.status(entry.co)

        if status == "dead" then
            table.remove(EP_queue, 1)

        elseif status == "suspended" then
            local ok, err = coroutine.resume(entry.co)
            if not ok then
                print("[EventPipeline] Error in '" .. tostring(entry.id) .. "': " .. tostring(err))
                table.remove(EP_queue, 1)
            end

        else
            table.remove(EP_queue, 1)
        end
    end

    EP_running = false
end


-- ─── Internal: push one coroutine onto the queue ─────────────────────────────

local function EP_push(fn, id)
    local entry = {
        id            = id or ("ep_task_" .. (#EP_queue + 1)),
        waiting       = false,
        pollCondition = nil,   -- set by handle:setPollCondition(), checked in update()
        co            = nil,
    }

    entry.co = coroutine.create(function()

        -- isDone flag solves the done()-before-wait() race:
        --
        --   Case A — done() called BEFORE wait()  (sync: done at end of fn body)
        --     isDone=true → wait() skips yield → coroutine finishes naturally
        --
        --   Case B — done() called AFTER wait()   (async: done inside anim callback)
        --     wait() yields → done() resumes coroutine directly → EP_tick continues
        --
        local isDone = false

        local handle = {

            wait = function()
                if isDone then
                    return  -- already done, skip yield
                end
                entry.waiting = true
                coroutine.yield()
                -- resumes here after done() or after poll condition is met
            end,

            done = function()
                isDone = true
                if entry.waiting then
                    entry.waiting = false
                    if coroutine.status(entry.co) == "suspended" then
                        local ok, err = coroutine.resume(entry.co)
                        if not ok then
                            print("[EventPipeline] Error after done(): " .. tostring(err))
                            table.remove(EP_queue, 1)
                        end
                    end
                    EP_tick()
                end
            end,

            -- poll steps call this to register their condition
            -- entry is captured here since handle is defined inside EP_push
            setPollCondition = function(condFn)
                -- print("[setPollCondition] storing type: " .. type(condFn))
                entry.pollCondition = condFn
            end,
        }

        fn(handle)
    end)

    table.insert(EP_queue, entry)

    if not EP_running then
        EP_tick()
    end
end


-- ─── Handler registry ─────────────────────────────────────────────────────────

local EP_handlers = {}
local EP_guards   = {}


-- =============================================================================
--  PUBLIC API
-- =============================================================================

EventPipeline = {}

-- -----------------------------------------------------------------------------
--  EventPipeline.setTimerFn(fn)
--  Inject a timer for "timed" steps.
--    EventPipeline.setTimerFn(function(sec, cb) TM_addTask(cb, sec) end)
-- -----------------------------------------------------------------------------
function EventPipeline.setTimerFn(fn)
    EP_timerFn = fn
end

-- Wire timed steps to TaskManager by default
EventPipeline.setTimerFn(function(sec, cb)
    TM_addTask(cb, sec)
end)

-- -----------------------------------------------------------------------------
--  EventPipeline.on(eventName, steps)
--  Register steps for a named event. Replaces any previous registration.
-- -----------------------------------------------------------------------------
function EventPipeline.on(eventName, steps)
    assert(type(eventName) == "string", "[EventPipeline] on(): eventName must be a string")
    assert(type(steps) == "table",      "[EventPipeline] on(): steps must be a table")
    EP_handlers[eventName] = steps
end

-- -----------------------------------------------------------------------------
--  EventPipeline.guard(eventName, fn)
--  Event-level gate. If fn(data) returns false, the whole event is dropped.
-- -----------------------------------------------------------------------------
function EventPipeline.guard(eventName, fn)
    EP_guards[eventName] = fn
end

-- -----------------------------------------------------------------------------
--  EventPipeline.emit(eventName, data)
--  Call from your packet handler. Appends all steps to the queue tail.
-- -----------------------------------------------------------------------------
function EventPipeline.emit(eventName, data)
    local steps = EP_handlers[eventName]
    if not steps then
        return
    end

    local guardFn = EP_guards[eventName]
    if guardFn and not guardFn(data) then
        return
    end

    for i, step in ipairs(steps) do
        local taskId    = eventName .. "_s" .. i
        local stepType  = step.type
        local stepFn    = step.fn
        local condition = step.condition
        local duration  = step.duration

        EP_push(function(handle)

            -- per-step skip condition (non-poll steps only)
            if stepType ~= "poll" and condition and not condition(data) then
                return
            end

            if stepType == "instant" then
                stepFn(data)

            elseif stepType == "async" then
                stepFn(data, function() handle:done() end)
                handle:wait()

            elseif stepType == "timed" then
                assert(EP_timerFn, "[EventPipeline] 'timed' step requires setTimerFn()")
                stepFn(data)
                EP_timerFn(duration or 0, function()
                    handle:done()
                end)
                handle:wait()

            elseif stepType == "poll" then
                assert(condition, "[EventPipeline] 'poll' step requires a condition function")
                -- print("[poll] condition type before set: " .. type(condition))
                -- register condition on the entry via handle
                -- entry is not directly accessible here — handle bridges the scope
                handle.setPollCondition(condition)
                handle:wait()
                -- resumes here once EventPipeline_update() sees condition() == true
                -- run optional fn after condition is met
                if stepFn then stepFn(data) end

            else
                print("[EventPipeline] Unknown step type: '" .. tostring(stepType) .. "'")
                if stepFn then stepFn(data) end
            end

        end, taskId)
    end
end

-- -----------------------------------------------------------------------------
--  EventPipeline.remove(eventName)  — unregister handler + guard
--  EventPipeline.clearQueue()       — wipe pending tasks, keep handlers
--  EventPipeline.isActive()         — true if anything is queued
-- -----------------------------------------------------------------------------

function EventPipeline.remove(eventName)
    EP_handlers[eventName] = nil
    EP_guards[eventName]   = nil
end

function EventPipeline.clearQueue()
    EP_queue   = {}
    EP_running = false
end

function EventPipeline.isActive()
    return #EP_queue > 0
end


-- =============================================================================
--  C++ BRIDGE  (same pattern as TaskManager.lua)
--  C++ calls EventPipeline_hasTasks() and EventPipeline_update(dt) every frame.
-- =============================================================================

function EventPipeline_hasTasks()
    return #EP_queue > 0
end

-- Called every frame by C++ (LuaEventPipeline::update).
-- Checks poll conditions on the front entry each frame.
function EventPipeline_update(dt)
    if #EP_queue > 0 then
        local entry = EP_queue[1]
        if entry.waiting and entry.pollCondition then
            -- safety check
            if type(entry.pollCondition) ~= "function" then
                print("[EventPipeline] poll error: pollCondition is a " .. type(entry.pollCondition) .. ", expected function")
                entry.pollCondition = nil
                entry.waiting = false
                EP_tick()
                return
            end
            if entry.pollCondition() then
                entry.pollCondition = nil
                entry.waiting       = false
                if coroutine.status(entry.co) == "suspended" then
                    local ok, err = coroutine.resume(entry.co)
                    if not ok then
                        print("[EventPipeline] Error in poll resume: " .. tostring(err))
                        table.remove(EP_queue, 1)
                    end
                end
                EP_tick()
            end
        end
    end
end