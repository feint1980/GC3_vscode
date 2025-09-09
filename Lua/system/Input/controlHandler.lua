
Input_host = nil

Signal = {

}

function ControlHandler_Init(host)
    Input_host = host

    print("ControlHandler_Init called")
end


function ControlHandler_DispatchSignal(signal)
    print("Get signal " .. signal)
end