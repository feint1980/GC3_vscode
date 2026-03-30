-- =============================================================================
--  EventPipeline.lua
--  Sequential event-to-animation pipeline.
--
--  Sits on top of TaskManager.lua — uses TM_addTask for deferred ticks and
--  timed steps. C++ drives this the same way as LuaTaskManager.
--
--  Step types:
--    "instant" : fn(data)            — runs and continues immediately
--    "async"   : fn(data, done)      — pauses until done() is called
--    "timed"   : fn(data), duration  — pauses for duration seconds, then continues
--
--  Any step accepts an optional: condition = function(data) return bool end
--  If condition returns false, that step is skipped silently.
-- =============================================================================


-- ─── Internal state ───────────────────────────────────────────────────────────

local EP_queue   = {}     -- { co, waiting, id }
local EP_running = false  -- re-entrancy guard
local EP_timerFn = nil    -- injected: fn(delaySec, callback)


-- ─── Internal: advance the queue ─────────────────────────────────────────────

local function EP_tick()
    if EP_running then return end
    EP_running = true

    while #EP_queue > 0 do
        local entry = EP_queue[1]

        if entry.waiting then
            break  -- blocked, stop until done() fires
        end

        local status = coroutine.status(entry.co)

        if status == "dead" then
            table.remove(EP_queue, 1)  -- finished, pick up next

        elseif status == "suspended" then
            local ok, err = coroutine.resume(entry.co)
            if not ok then
                print("[EventPipeline] Error in '" .. tostring(entry.id) .. "': " .. tostring(err))
                table.remove(EP_queue, 1)
            end
            -- loop continues:
            --   if it yielded into wait → entry.waiting=true → loop breaks
            --   if it finished          → status="dead"      → next iter removes it

        else
            table.remove(EP_queue, 1)
        end
    end

    EP_running = false
end


-- ─── Internal: push one coroutine onto the queue ─────────────────────────────

local function EP_push(fn, id)
    local entry = {
        id      = id or ("ep_task_" .. (#EP_queue + 1)),
        waiting = false,
        co      = nil,
    }

    entry.co = coroutine.create(function()

        -- isDone flag handles the race between done() and wait():
        --
        --   Case A — done() called BEFORE wait()   (sync: done at end of fn body)
        --     → isDone = true
        --     → wait() sees it, skips yield, coroutine finishes naturally
        --
        --   Case B — done() called AFTER wait()    (async: done inside anim callback)
        --     → wait() yields, entry.waiting = true
        --     → done() clears waiting, resumes coroutine via TM_addTask
        --     → coroutine finishes, EP_tick picks up next entry
        --
        local isDone = false

        local handle = {

            wait = function()
                if isDone then
                    return  -- done() already called, no need to yield
                end
                entry.waiting = true
                coroutine.yield()
                -- execution resumes here after done() triggers resume
            end,

            done = function()
                isDone = true
                if entry.waiting then
                    -- coroutine is already yielded — resume it next frame
                    entry.waiting = false
                    TM_addTask(function()
                        if coroutine.status(entry.co) == "suspended" then
                            local ok, err = coroutine.resume(entry.co)
                            if not ok then
                                print("[EventPipeline] Error after done(): " .. tostring(err))
                                table.remove(EP_queue, 1)
                            end
                        end
                        EP_tick()
                    end, 0)
                end
                -- if not waiting yet: wait() will see isDone and skip yield
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
--
--  Inject a timer for "timed" steps. Reuse your existing TaskManager:
--    EventPipeline.setTimerFn(function(sec, cb) TM_addTask(cb, sec) end)
-- -----------------------------------------------------------------------------
function EventPipeline.setTimerFn(fn)
    EP_timerFn = fn
end

-- -----------------------------------------------------------------------------
--  EventPipeline.on(eventName, steps)
--
--  Register steps for a named event. Replaces any previous registration.
--
--  EventPipeline.on("MY_EVENT", {
--      { type = "instant", fn = function(data) ... end },
--      { type = "async",   fn = function(data, done) ... done() ... end },
--      { type = "timed",   fn = function(data) ... end, duration = 1.5 },
--  })
-- -----------------------------------------------------------------------------
function EventPipeline.on(eventName, steps)
    assert(type(eventName) == "string", "[EventPipeline] on(): eventName must be a string")
    assert(type(steps) == "table",      "[EventPipeline] on(): steps must be a table")
    EP_handlers[eventName] = steps
end

-- -----------------------------------------------------------------------------
--  EventPipeline.guard(eventName, fn)
--
--  Event-level gate. If fn(data) returns false, the whole event is dropped.
--
--  EventPipeline.guard("CHARACTER_TURN", function(data)
--      return not GameState.cutscenePlaying
--  end)
-- -----------------------------------------------------------------------------
function EventPipeline.guard(eventName, fn)
    EP_guards[eventName] = fn
end

-- -----------------------------------------------------------------------------
--  EventPipeline.emit(eventName, data)
--
--  Call from your packet handler. Appends all steps to the queue tail.
--  Safe to call while a previous event is still running.
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

            if condition and not condition(data) then
                return  -- skip, coroutine ends cleanly, queue advances
            end

            if stepType == "instant" then
                stepFn(data)
                -- coroutine ends here → queue advances immediately

            elseif stepType == "async" then
                stepFn(data, function() handle:done() end)
                handle:wait()
                -- if done() was called synchronously inside stepFn:
                --   isDone=true → wait() returns immediately → coroutine ends
                -- if done() is called later (inside anim callback):
                --   wait() yields → done() resumes via TM_addTask next frame

            elseif stepType == "timed" then
                assert(EP_timerFn, "[EventPipeline] 'timed' step requires setTimerFn()")
                stepFn(data)
                EP_timerFn(duration or 0, function()
                    handle:done()
                end)
                handle:wait()

            else
                print("[EventPipeline] Unknown step type: '" .. tostring(stepType) .. "'")
                if stepFn then stepFn(data) end
            end

        end, taskId)
    end
end

-- -----------------------------------------------------------------------------
--  EventPipeline.remove(eventName)   — unregister handler + guard
--  EventPipeline.clearQueue()        — wipe pending tasks (not handlers)
--  EventPipeline.isActive()          — true if anything is queued
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
-- =============================================================================

function EventPipeline_hasTasks()
    return #EP_queue > 0
end

function EventPipeline_update(dt)
    -- no-op: pipeline is callback-driven, not frame-polled.
    -- reserved for a future "poll" step type.
end
