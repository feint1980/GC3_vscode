

Tscheduler = {}


EventTasks = {
    time = 0,
    callback = nil
}

function EventTasks:new( time, callback)
    local o = {}
    o.time = time
    o.callback = callback
    setmetatable(o, self)
    self.__index = self
    return o
end



EvenTaskList = {}

_G.HandlerHost = nil
Tsize = 0
function InitEventHandler(host)
    _G.HandlerHost = host
    if _G.HandlerHost == nil then
        print("host is nil")
    else
        print("host is not nil")
        print(_G.HandlerHost)
    end
end


function Tscheduler_addTask(time, callback,host)

    -- if host == nil then

    local task = EventTasks:new(time, callback)

    table.insert(EvenTaskList, task)

    if(Tsize == 0) then
        print("start event handler")
        print("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! host use !!!!!!!!!!!!!!!!!!!!!!!!!!")
        cppEventHandlerStart()
    end
    Tsize =  Tsize + 1
end


function EventHandlerUpdate(dt)
    -- print("lua update regardless " )
    if Tsize > 0 then 
        -- print("lua update " .. dt)
        for i = #EvenTaskList, 1, -1 do
            local task = EvenTaskList[i]
            -- print("task " .. task.time)
            task.time = task.time - dt
            if task.time <= 0 then
                task.callback()
                table.remove(EvenTaskList, i)
                Tsize = Tsize - 1
            end
            if(Tsize == 0) then
                cppEventHandlerStop()
                print("stop event handler")
            end
        end
    end
end