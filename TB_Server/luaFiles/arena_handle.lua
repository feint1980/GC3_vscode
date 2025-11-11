package.path = package.path .. ";../luaFiles/?.lua" .. ";../luaFiles/BattleServer/?.lua" 

require "serverWrapper"
require "SV_global"
require "BSEP"

MessageHandling[PacketChannel.ArenaChannel][ArenaResponse.Arena_Request_GetServerList] = function(host, data,ip,guid)

    print("request from " .. guid .. " for arena server list")
    -- BSEP_List = _G.BSEP_List
    for k,v in pairs(BSEP_List) do
        print("Server ID : " .. k .. " \t|IP: " .. SV_GetIPString(v.IP) )
    end


end

