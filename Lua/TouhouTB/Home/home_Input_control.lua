package.path = package.path .. ';../../Lua/system/Input/?.lua;'

require "controlHandler"


-- Main register to handle signal
Dispatch_Recievers["homeScene"] = function (controlHandlerHost,signal)
    print("homescene handle signal " .. signal)

    if signal == 1 then
        ControlHandler_setCursorPos(controlHandlerHost,150,730)
    elseif signal == 16 then
        local x,y = ControlHandler_getCursorPos()
        print("x " .. x .. " y " .. y)
        Controller_fireLeftClickEvent(controlHandlerHost,1,x,y)
    end
end

