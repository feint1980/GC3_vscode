-- =============================================================================
--  PollTask.lua
--  Frame-polled task system. Tasks fire when their signal is set to true.
--  C++ calls Poll_HasTasks() and Poll_Update() every frame.
-- =============================================================================

PollTaskCount = 0

PollTask = {}
PollTask.__index = PollTask

function PollTask:new()
    local o  = setmetatable({}, self)
    o.name   = ""
    o.signal = false
    o.func   = nil
    o.args   = {}

    self.__index = self
    return o
end

-- signal table: signalName → bool
PollSignals = {}

-- task table: signalName → PollTask
PollTasks = {}

-- ─── Signal API ───────────────────────────────────────────────────────────────

-- Set a signal to true (triggers any task waiting on it next update)
function Poll_SetSignal(signalName,value)
    local tValue = value or true
    PollSignals[signalName] = tValue
end



-- Clear a signal (reset for reuse)
function Poll_ClearSignal(signalName)
    PollSignals[signalName] = nil
end

-- Check a signal manually
function Poll_CheckSignal(signalName)
    return PollSignals[signalName] == true
end


-- ─── Task API ─────────────────────────────────────────────────────────────────

-- Register a task to fire when signalName becomes true.
-- func signature: func(args)
-- Replaces any existing task under the same signal name.
function Poll_AddTask(signalName, func, args)
    -- print("Poll_AddTask: " .. signalName)
    if not PollTasks[signalName] then
        PollTaskCount = PollTaskCount + 1
    end
    PollTasks[signalName] = PollTask:new({
        name   = signalName,
        func   = func,
        args   = args or {}
    })
end

-- Remove a task without firing it
function Poll_RemoveTask(signalName)
    if PollTasks[signalName] then
        PollTasks[signalName] = nil
        PollTaskCount = PollTaskCount - 1
    end
end

-- List all pending tasks (debug)
function Poll_ListTasks()
    print("[PollTask] pending: " .. PollTaskCount)
    for k, v in pairs(PollTasks) do
        print("  " .. k .. " | signal: " .. tostring(PollSignals[k]))
    end
end


-- ─── C++ Bridge ───────────────────────────────────────────────────────────────

function Poll_HasTasks()
    return PollTaskCount > 0
end

-- Called every frame by C++
function Poll_Update(deltaTime)
    if PollTaskCount <= 0 then return end

    for signalName, task in pairs(PollTasks) do
        if PollSignals[signalName] == true then
            -- fire the task
            task.func(task.args)
            -- clean up
            Poll_RemoveTask(signalName)
            Poll_ClearSignal(signalName)
        end
    end
end