
package.path = package.path .. ';./player/?.lua' .. ';../../Lua/Wonderland/player/?.lua;'
W_Host = nil

require "W_Player"

---@type W_Player
Current_Player = nil

function InitWonderlandBase(host)
    W_Host = host
    cppLoadScene(W_Host,"./Scence/test.fsc")
    Current_Player = W_Player:new()
    Current_Player:init(W_Host, "./Assets/F_AObjects/wonderland_char_p1.xml", 100, 100,2.5,2.25)
end

function WonderLandTestHost()
    if W_Host == nil then
        print("W_Host is nil")
    else
        print("W_Host is not nil")
    end
end

function WonderLandInputHandling(signal)
    if Current_Player ~= nil then
        Current_Player:inputHandling(signal)
    end
end
