
W_Host = nil

Current_Player = nil

function InitWonderlandBase(host)
    W_Host = host
    cppLoadScene(W_Host,"./Scence/test.fsc")
    Current_Player = cppCreatePlayer(W_Host, "./Assets/F_AObjects/wonderland_char_p1.xml", 100, 100)
end

function WonderLandTestHost()
    if W_Host == nil then
        print("W_Host is nil")
    else
        print("W_Host is not nil")
    end
end

function WonderLandInputHandling(signal)
    print("input signal " .. signal)
end



