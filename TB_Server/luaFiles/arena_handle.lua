package.path = package.path .. ";../luaFiles/?.lua" .. ";../luaFiles/BattleServer/?.lua" 

require "serverWrapper"
require "SV_global"
require "BSEP"


MessageHandling[PacketChannel.ArenaChannel][ArenaResponse.Arena_Request_GetServerList] = function(host, data,ip,guid)

    print("request from " .. guid .. " for arena server list")

    local tGUID, rquest = string.match(data, "^|([^|]+)|([^|]+)|$") 

    print("guid check " .. tGUID .. "/" .. guid) 
    if tGUID ~= guid then
        print("invalid user,  warning, craft packet found from ip " .. SV_GetIPString(ip))
        return
    end

    local serverList = {} 

    BSEP_List = _G.BSEP_List
    for k,v in pairs(BSEP_List) do
        serverList[k] = {}
        print("Server ID : " .. k .. " \t|IP: " .. SV_GetIPString(v:getIP())
        .. " port: " .. v.port  .. "\t|Ping: " .. SV_GetTargetPing(v:getIP()))
        serverList[k].name = v.name
        serverList[k].IP = SV_GetIPString(v.IP)
        serverList[k].port = v.port
        serverList[k].ping = SV_GetTargetPing(v.IP)
    end

    SendReliable(host,ip,guid,PacketChannel.ArenaChannel,ArenaResponse.Arena_Request_GetServerList,{JSON_Encode(serverList,false)})

end

MessageHandling[PacketChannel.ArenaChannel][ArenaResponse.Arena_RequestLobbyList] = function(host, data,ip,guid)

    print("request from " .. guid .. " for lobby list")

end

