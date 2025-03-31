

Tscheduler = {}

HandlerHost = nil
Tsize = 0

function InitHandler(host)
    HandlerHost = host
end

function Tscheduler:wait(time, callback)
    print("Wait call " .. time)
    table.insert(self, {time = time, callback = callback})
    -- if size of table > 0 then kick start in C++
    if(Tsize == 0) then
        cppEventHandlerStart(HandlerHost)
    end
    Tsize =  Tsize + 1
end

function Tscheduler:update(dt)
    -- print("update call ")
    for i = #self, 1, -1 do
        local task = self[i]
        -- print("task " .. task.time)
        task.time = task.time - dt
        if task.time <= 0 then
            task.callback()
            table.remove(self, i)
            Tsize = Tsize - 1
            if Tsize == 0 then
                cppEventHandlerStop(HandlerHost)
            end
        end
    end
end

function EventHandlerUpdate(dt)
    Tscheduler:update(dt)
end