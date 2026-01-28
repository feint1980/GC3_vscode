package.path = package.path .. ';../../Lua/system/Input/?.lua;'

require "controlHandler"

local function issueFocus(controlHost, tguiHost)
    local label =  cpp_FocusStack_GetFocusLabel(tguiHost)
    if label == nil then
        print("label is nil")
        return
    end
    local txt = TGUI_Label_GetText(label)
    -- print("txt: " .. txt)

    local tX, tY = TGUI_Label_GetPos(label)
    ControlHandler_setCursorPos(controlHost,tX,tY)
end

local function tFocusNext(controlHost,tguiHost)
    cpp_FocusLabel_ChangeIndex(tguiHost,1)
    issueFocus(controlHost,tguiHost)
end

local function tFocusPrev(controlHost,tguiHost)
    cpp_FocusLabel_ChangeIndex(tguiHost,-1)
    issueFocus(controlHost,tguiHost)
end
-- Main register to handle signal

Dispatch_Recievers = {} -- reset recievers
Dispatch_Recievers["lobbyScene"] = function (controlHandlerHost,tguiHost,signal)
    -- print("homeScene handle signal " .. signal)
    if signal < 16 then ---- contain at least left, right, up, down
    -- if (signal & Signal.left) ~= 0 then
        -- print("movement detect " )
        -- ControlHandler_Info()
    if (signal & Signal.left) ~= 0 then
            tFocusPrev(controlHandlerHost,tguiHost)
            -- print("left !")
        elseif (signal & Signal.right) ~= 0 then
            -- print("right !")
            tFocusNext(controlHandlerHost,tguiHost)
            -- focusNext(controlHandlerHost)
        elseif (signal & Signal.up) ~= 0 then
            -- print("up !")
        elseif (signal & Signal.down) ~= 0 then
            -- print("down !")
        end
    elseif signal == 16 then
        local x,y = ControlHandler_getCursorPos()
        -- print("x " .. x .. " y " .. y)
        Controller_fireLeftClickEvent(controlHandlerHost,1,x,y)
    else 
        if signal == Signal.escape then 
            -- _G.Formation_Edit_Instance:resetSelections()
            -- Formation_MainUpdate(tguiHost)
        end
    end
end

