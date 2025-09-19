package.path = package.path .. ';../../Lua/system/Input/?.lua;'

require "controlHandler"

Login_Focus_Panel = {

}

local function focusNext(host) 
    if #SignalReceivers.stack > 0 then
        -- handle inside focus panel
        if SignalReceivers.stack[SignalReceivers.focusIndex] ~= nil then
            print("reach here, focus index is " .. SignalReceivers.focusIndex)
            print("total stacks " .. #SignalReceivers.stack)
            local panel = SignalReceivers.stack[SignalReceivers.focusIndex]
            print("get panel at " .. SignalReceivers.focusIndex)
            if Panel_Focus_List[panel] ~= nil then
                Panel_Focus_List[panel]:autoFocus()

                print("current seelction is " .. Panel_Focus_List[panel].currentSelection)

                local txt = TGUI_Label_GetText(Panel_Focus_List[panel].subLabels[Panel_Focus_List[panel].currentSelection])
                print("txt: " .. txt)

                local pX, pY = TGUI_Label_GetPos(Panel_Focus_List[panel].subLabels[Panel_Focus_List[panel].currentSelection])
                print("pX:" .. pX .. " pY:" .. pY)
                ControlHandler_setCursorPos(host,pX,pY)
            else
                print("Panel_Focus_List[panel] is nil")
            end
        end
    else 
        if #Parentless_Widgets > 0 then
            print("reach here, parentless index is " .. Parentless_WidgetsIndex)
            -- ControlHandler_Parentless_ChangeIndex(1)
            Parentless_WidgetsIndex = 1
            if Parentless_Widgets[Parentless_WidgetsIndex] ~= nil then
                print(Parentless_Widgets[Parentless_WidgetsIndex]
            )

                local txt = TGUI_Label_GetText(Parentless_Widgets[Parentless_WidgetsIndex])
                print("txt: " .. txt)

                local tX, tY = TGUI_Label_GetPos(Parentless_Widgets[Parentless_WidgetsIndex])
                ControlHandler_setCursorPos(host,tX,tY)
            else
                print("Parentless_Widgets[Parentless_WidgetsIndex] is nil")
            end
            -- local x,y = TGUI_Label_GetPos(Parentless_Widgets[Parentless_WidgetsIndex])
            -- ControlHandler_setCursorPos(host,x,y)
            -- if Parentless_Widgets[Parentless_WidgetsIndex] ~= nil then
            -- end
        end
    end
end


local function tFocusNext(host)
    local label =  cpp_FocusStack_GetFocusLabel(host)
    -- if label == nil then
    --     print("label is nil")
    --     return
    -- end
    -- local txt = TGUI_Label_GetText(label)
    -- print("txt: " .. txt)

    -- local tX, tY = TGUI_Label_GetPos(label)
    -- ControlHandler_setCursorPos(host,tX,tY)
end

Dispatch_Recievers["loginScene"] = function (controlHandlerHost,signal)
    print("login handle signal " .. signal)
    if signal < 16 then ---- contain at least left, right, up, down
    -- if (signal & Signal.left) ~= 0 then
        print("movement detect " )
        ControlHandler_Info()
        if (signal & Signal.left) ~= 0 then
            print("left !")
        elseif (signal & Signal.right) ~= 0 then
            print("right !")
            tFocusNext(controlHandlerHost)
            -- focusNext(controlHandlerHost)
        elseif (signal & Signal.up) ~= 0 then
            print("up !")
        elseif (signal & Signal.down) ~= 0 then
            print("down !")
        end
    elseif signal == 16 then
        local x,y = ControlHandler_getCursorPos()
        print("x " .. x .. " y " .. y)
        Controller_fireLeftClickEvent(controlHandlerHost,1,x,y)
    end

end
