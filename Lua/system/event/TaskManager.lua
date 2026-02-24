
DelayTask = {
    callback = nil,
    time = 0
}

function DelayTask:new(time, callback)
    local o = {}
    setmetatable(o, self)
    self.__index = self
    o.callback = callback
    o.time = time
    return o
end

TM_Tasks = {

}

function TM_addTask(callback, time)
    -- print("TM_addTask called")
    table.insert(TM_Tasks, DelayTask:new(time, callback))
    -- table.insert(TM_Tasks, {time = time, callback = callback})
end

function TaskManager_update(dt)
    -- print("TaskManager_update called")
    -- local tasks = TaskManager.tasks
    for i = #TM_Tasks, 1, -1 do
        local task = TM_Tasks[i]
        task.time = task.time - dt
        -- print("task time " .. task.time)
        if task.time <= 0 then
            task.callback()
            table.remove(TM_Tasks, i)
        end
    end
end

function TaskManager_hasTasks()

    return #TM_Tasks > 0
end

TM_waitTasks = {}

function TM_waitUntil(condition)
    while not condition() do
        coroutine.yield()
    end
end

