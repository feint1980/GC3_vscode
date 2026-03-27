
-- =============================================================================
--  BS_EventPipeline.lua
--  Sequential event-to-animation pipeline.
--
--  Sits on top of TaskManager.lua — delegate timer to TM_addTask via setTimerFn.
--  C++ drives this the same way as LuaTaskManager (hasTasks / update pattern).
--
--  Step types:
--    "instant" : runs fn(data), continues immediately
--    "async"   : runs fn(data, done), pauses until done() is called
--    "timed"   : runs fn(data), auto-continues after duration seconds
--                requires EventPipeline_setTimerFn() to be called first
--
--  Any step can have a condition = function(data) return bool end field.
--  If condition returns false, that step is skipped silently.
-- =============================================================================


-- ─── Internal queue state ─────────────────────────────────────────────────────

local EP_queue   = {}      -- array of { co, waiting, id }
local EP_running = false   -- re-entrancy guard
local EP_timerFn = nil     -- injected timer: fn(delaySec, callback)


-- ─── Internal: tick the queue ─────────────────────────────────────────────────

local function EP_tick()
    if EP_running then return end
    EP_running = true

    while #EP_queue > 0 do
        local entry = EP_queue[1]

        if entry.waiting then
            break  -- blocked on async/timed step, stop here
        end

        local status = coroutine.status(entry.co)

        if status == "dead" then
            table.remove(EP_queue, 1)
            -- loop: pick up next entry immediately

        elseif status == "suspended" then
            local ok, err = coroutine.resume(entry.co)
            if not ok then
                print("[EventPipeline] Error in '" .. tostring(entry.id) .. "': " .. tostring(err))
                table.remove(EP_queue, 1)
            end
            -- after resume: if entry.waiting became true → loop will break
            -- if coroutine finished → next iteration removes it

        else
            -- "normal" or unexpected status — remove and continue
            table.remove(EP_queue, 1)
        end
    end

    EP_running = false
end


-- ─── Internal: push a raw coroutine task ──────────────────────────────────────

local function EP_push(fn, id)
    local entry = {
        id      = id or ("ep_task_" .. (#EP_queue + 1)),
        waiting = false,
        co      = nil,
    }

    entry.co = coroutine.create(function()
        local handle = {
            -- Call inside async step fn: pauses queue until done() is called
            wait = function()
                entry.waiting = true
                coroutine.yield()
            end,
            -- Call from anim callback / timer to resume queue
            done = function()
                entry.waiting = false
                EP_tick()
            end,
        }
        fn(handle)
    end)

    table.insert(EP_queue, entry)

    -- Kick off immediately if nothing is currently ticking
    if not EP_running then
        EP_tick()
    end
end


-- ─── Handler registry ─────────────────────────────────────────────────────────

local EP_handlers = {}   -- eventName → array of step definitions
local EP_guards   = {}   -- eventName → fn(data) → bool


-- =============================================================================
--  PUBLIC API
-- =============================================================================

EventPipeline = {}

-- -----------------------------------------------------------------------------
--  EventPipeline.setTimerFn(fn)
--
--  Inject a timer function for "timed" steps.
--  fn signature: fn(delaySec, callback)
--
--  To reuse your existing TaskManager:
--    EventPipeline.setTimerFn(function(sec, cb) TM_addTask(cb, sec) end)
-- -----------------------------------------------------------------------------
function EventPipeline.setTimerFn(fn)
    EP_timerFn = fn
end

-- -----------------------------------------------------------------------------
--  EventPipeline.on(eventName, steps)
--
--  Register an ordered list of steps for a named event.
--  Calling on() again for the same event replaces the previous registration.
--
--  Example:
--    EventPipeline.on("ROLL_RESULTS", {
--        { type = "async",   fn = function(data, done) Anim.showDeltas(data, done) end },
--        { type = "instant", fn = function(data)       UI.updateSpeeds(data)       end },
--        { type = "async",   fn = function(data, done) Anim.sortCards(data, done)  end },
--    })
-- -----------------------------------------------------------------------------
function EventPipeline.on(eventName, steps)
    assert(type(eventName) == "string", "[EventPipeline] on(): eventName must be a string")
    assert(type(steps) == "table",      "[EventPipeline] on(): steps must be a table")
    EP_handlers[eventName] = steps
end

-- -----------------------------------------------------------------------------
--  EventPipeline.guard(eventName, fn)
--
--  Optional gate for an event. If fn(data) returns false, the entire event
--  is dropped — no tasks are pushed.
--
--  Useful for: "ignore all events while victory screen is active", etc.
--
--  Example:
--    EventPipeline.guard("CHARACTER_TURN", function(data)
--        return not GameState.isCutscenePlaying
--    end)
-- -----------------------------------------------------------------------------
function EventPipeline.guard(eventName, fn)
    EP_guards[eventName] = fn
end

-- -----------------------------------------------------------------------------
--  EventPipeline.emit(eventName, data)
--
--  Call this from your packet receive handler.
--  Pushes all steps for this event onto the tail of the queue.
--  Safe to call while a previous event is still animating.
--
--  Example:
--    function onPacketReceived(eventName, data)
--        EventPipeline.emit(eventName, data)
--    end
-- -----------------------------------------------------------------------------
function EventPipeline.emit(eventName, data)
    local steps = EP_handlers[eventName]
    if not steps then
        -- No handler registered — silently ignore
        -- Uncomment to debug: print("[EventPipeline] No handler for: " .. tostring(eventName))
        return
    end

    -- Check event-level guard
    local guardFn = EP_guards[eventName]
    if guardFn and not guardFn(data) then
        return
    end

    -- Push one coroutine task per step
    for i, step in ipairs(steps) do
        local taskId    = eventName .. "_s" .. i
        local stepType  = step.type
        local stepFn    = step.fn
        local condition = step.condition
        local duration  = step.duration

        EP_push(function(handle)

            -- Per-step condition gate
            if condition and not condition(data) then
                return  -- skip this step, coroutine ends, queue advances
            end

            if stepType == "instant" then
                stepFn(data)
                -- no wait needed, coroutine ends → queue advances

            elseif stepType == "async" then
                handle:wait()                             -- pause queue
                stepFn(data, function() handle:done() end) -- resume when anim calls done()

            elseif stepType == "timed" then
                assert(EP_timerFn, "[EventPipeline] 'timed' step requires setTimerFn()")
                handle:wait()                             -- pause queue
                stepFn(data)                              -- run the visual
                EP_timerFn(duration or 0, function()     -- auto-resume after delay
                    handle:done()
                end)

            else
                print("[EventPipeline] Unknown step type: '" .. tostring(stepType) .. "' in event '" .. eventName .. "'")
                if stepFn then stepFn(data) end
                -- treat as instant, don't block queue
            end

        end, taskId)
    end
end

-- -----------------------------------------------------------------------------
--  EventPipeline.remove(eventName)
--  Remove handler + guard for an event.
-- -----------------------------------------------------------------------------
function EventPipeline.remove(eventName)
    EP_handlers[eventName] = nil
    EP_guards[eventName]   = nil
end

-- -----------------------------------------------------------------------------
--  EventPipeline.clearQueue()
--  Wipe all pending tasks. Does NOT affect registered handlers.
--  Use when transitioning scenes or aborting a match mid-sequence.
-- -----------------------------------------------------------------------------
function EventPipeline.clearQueue()
    EP_queue   = {}
    EP_running = false
end

-- -----------------------------------------------------------------------------
--  EventPipeline.isActive()
--  Returns true if any tasks are pending or running.
-- -----------------------------------------------------------------------------
function EventPipeline.isActive()
    return #EP_queue > 0
end


-- =============================================================================
--  C++ BRIDGE  (same naming pattern as TaskManager.lua)
--  C++ calls these every frame via lua_getglobal / lua_call.
-- =============================================================================

function EventPipeline_hasTasks()
    return #EP_queue > 0
end

-- dt is passed by C++ but the pipeline is callback-driven, not frame-polled.
-- This function is a no-op unless you add poll-type steps in the future.
-- It exists so LuaEventPipeline.cpp can follow the exact same pattern as
-- LuaTaskManager.cpp without any special casing.
function EventPipeline_update(dt)
    -- reserved for future "poll" step type
    -- (a step that checks a condition each frame instead of waiting for a callback)
end
