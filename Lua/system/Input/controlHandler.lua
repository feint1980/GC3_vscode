Input_host = nil

Signal = {

}

---@type table of Panel
SignalReceivers = {
    stack = {},
    focusIndex = 0,
}

function ControlHandler_Init(host)
    Input_host = host

    print("ControlHandler_Init called")
end

function ControlHandler_DispatchSignal(signal)
    print("Get signal " .. signal)
    for i = 1, #SignalReceivers.stack do
        if SignalReceivers.stack[i] ~= nil then
            --- esc/B button hit
            if signal == 32 then
                TGUI_Panel_SetVisible(SignalReceivers.stack[i],true)
                TGUI_Panel_HideWithEffect(SignalReceivers.stack[i],0,250)
            end
            --- consider handle left/right/up/down
            --- todo here
        end
    end
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

