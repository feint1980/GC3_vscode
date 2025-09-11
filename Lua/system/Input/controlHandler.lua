Input_host = nil

Signal = {

}

---@type table of Panel
SignalReceivers = {
    stack = {},
    focusIndex = 0,
    buttons = {},
    buttonIndex = 0,
}

Dispatch_Recievers = {}



function ControlHandler_Init(host)
    Input_host = host

    print("ControlHandler_Init called")
end

function ControlHandler_DispatchSignal(host,signal)
    print("Get signal " .. signal)
    for k,v in pairs(Dispatch_Recievers) do
        if v ~= nil then
            v(host,signal)
        end
    end
    -- for i = 1, #SignalReceivers.stack do
    --     if SignalReceivers.stack[i] ~= nil then
    --         --- esc/B button hit
    --         if signal == 32 then
    --             TGUI_Panel_SetVisible(SignalReceivers.stack[i],true)
    --             TGUI_Panel_HideWithEffect(SignalReceivers.stack[i],0,250)
    --         elseif signal == 16 then
    --             ControlHandler_setCursorPos(0,0)
    --         end
    --         --- consider handle left/right/up/down
    --         --- todo here
    --     end
    -- end
end

function ControlHandler_reciever_push(panel)
    table.insert(SignalReceivers.stack, panel)
    SignalReceivers.focusIndex = #SignalReceivers.stack
end

function ControlHandler_reciever_pop()
    if #SignalReceivers.stack > 0 then
        table.remove(SignalReceivers.stack, #SignalReceivers.stack)
        SignalReceivers.focusIndex = #SignalReceivers.stack
    else
        print("stack is empty")
    end
end
function ControlHandler_reciever_remove(panel)
    for i = 1, #SignalReceivers.stack do
        if SignalReceivers.stack[i] == panel then
            table.remove(SignalReceivers.stack, i)
            SignalReceivers.focusIndex = #SignalReceivers.stack
            return
        end
    end
end

function ControlHandler_reciever_getTop()
    if #SignalReceivers.stack == 0 then
        return nil
    end
    return SignalReceivers.stack[SignalReceivers.focusIndex]
end

function ControlHandler_receiver_switchFocus(panel)
    for i = 1, #SignalReceivers.stack do
        if SignalReceivers.stack[i] == panel then
            SignalReceivers.focusIndex = i
            return
        end
    end
end

---@Description set the cursor position 
---@param host pointer instance of TGUIScriptingManager
---@param x number x position
---@param y number y position
function ControlHandler_setCursorPos(host,x,y)
    print("ControlHandler_setCursorPos called ")
    if host == nil then
        print("Input_host is nil")
        return
    else
        cpp_ControlHandler_Cursor_Set(host,x,y)
    end
    -- TGUI_Panel_SetMousePos(Input_host,x,y)
end

---@Description get the cursor position 
---@return number x position, y position
function ControlHandler_getCursorPos()
    return cpp_ControlHandler_Cursor_Get()
end

---@Description fire left click event
---@param host pointer instance of TGUIScriptingManager
---@param times number (optional) times of fire
---@param x number (optional) x position
---@param y number (optional) y position
function Controller_fireLeftClickEvent(host,times,x,y)
    cpp_ControlHandler_Cursor_SendLeftClickEvent(host,times,x,y)
end