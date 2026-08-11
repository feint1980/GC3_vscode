package.path = package.path .. ';../../Lua/system/Input/?.lua;'

require "controlHandler"

local function issueFocus(controlHost, tguiHost)
    local label =  cpp_FocusStack_GetFocusLabel(tguiHost)
    if label == nil then
        print("label is nil")
        return
    end
    -- local txt = TGUI_Label_GetText(label)
    -- -- print("txt: " .. txt)
    -- local tX, tY = TGUI_Label_GetPos(label)
    -- ControlHandler_setCursorPos(controlHost,tX,tY)
end

local function tFocusNext(controlHost,tguiHost)
    cpp_FocusLabel_ChangeIndex(tguiHost,1)
    issueFocus(controlHost,tguiHost)
end

local function tFocusPrev(controlHost,tguiHost)
    cpp_FocusLabel_ChangeIndex(tguiHost,-1)
    issueFocus(controlHost,tguiHost)
end

Dispatch_Recievers = {} -- reset the recievers only 1 scene active

-- Signals Map : 



Dispatch_Recievers["combatScene"] = function (controlHandlerHost,tguiHost,signal)
    -- print("login handle signal " .. signal)
    if signal < 16 then ---- contain at least left, right, up, down
    -- if (signal & Signal.left) ~= 0 then
        -- print("movement detect " )
        -- ControlHandler_Info()
        if (signal & Signal.left) ~= 0 then
            -- tFocusPrev(controlHandlerHost,tguiHost)
            print("left !")
        elseif (signal & Signal.right) ~= 0 then
            print("right !")
            -- tFocusNext(controlHandlerHost,tguiHost)
            -- focusNext(controlHandlerHost)
        elseif (signal & Signal.up) ~= 0 then
            print("up !")
        elseif (signal & Signal.down) ~= 0 then
            print("down !")
        end
    elseif (signal & Signal.enter) ~= 0 then
        print("enter !")
        -- local x,y = ControlHandler_getCursorPos()
        -- print("x " .. x .. " y " .. y)
        -- Controller_fireLeftClickEvent(controlHandlerHost,1,x,y)
    elseif (signal & Signal.escape) ~=0  then
        print("escape !")
    elseif (signal & Signal.mouseLeft) ~=0  then
        print("mouse left click !")
    elseif (signal & Signal.mouseRight) ~=0  then
        print("mouse right click !")
    elseif (signal & Signal.key_q) ~=0  then
        if(signal & Signal.isAlted) ~=0 then
            print("alt + q")
        elseif (signal & Signal.isShifted) ~=0 then
            print("shift + q")
        elseif (signal & Signal.isCntrled) ~=0 then
            print("ctrl + q")
        else
            print("just q")
        end

    end
    Combat_Dock_Middle_Instance:handleInput(signal)

end

