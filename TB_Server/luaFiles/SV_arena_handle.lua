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

    -- SendReliable(host,ip,guid,PacketChannel.ArenaChannel,ArenaResponse.Arena_RequestLobbyListResponse,{tData})
    -- SendReliable(host,ip,guid,PacketChannel.ArenaChannel,ArenaResponse.Arena_RequestLobbyList,{tData})
    SV_SendLobbyListToClientEP(host,ip,guid)
end


function  SV_SendLobbyListToClientEP(host,ip,guid)

    print("request from " .. guid .. " for lobby list")
    local serverList = {}
    for k,v in pairs(BSEP_List) do
        serverList[k] = {}
        serverList[k].name = v.name
        serverList[k].lobbyList = {}
        for n,m in pairs(v.lobbyList) do
            print("data check " .. n)
            print("id " .. m.id)
            print("name " .. m.name)
            print("password " .. m.password)
            print("state " .. m.lobbyState)
            serverList[k].lobbyList[n] = {}
            serverList[k].lobbyList[n].id = m.id
            serverList[k].lobbyList[n].name = m.name
            serverList[k].lobbyList[n].password = m.password
            serverList[k].lobbyList[n].lobbyState = m.lobbyState
            serverList[k].lobbyList[n].battleClientEP_List = {}
            for i = 1, #m.battleClientEP_List do
                print("player #" .. i)
                serverList[k].lobbyList[n].battleClientEP_List[i] = {}
                serverList[k].lobbyList[n].battleClientEP_List[i].id = m.battleClientEP_List[i].id
                serverList[k].lobbyList[n].battleClientEP_List[i].guid = m.battleClientEP_List[i].guid
            end
        end
    end

    local tData = JSON_Encode(serverList,false)
    print("json check " .. tData)
    SendReliable(host,ip,guid,PacketChannel.ArenaChannel,ArenaResponse.Arena_RequestLobbyListResponse,{tData})
end

MessageHandling[PacketChannel.ArenaChannel][ArenaResponse.Arena_RequestLobby_Create] = function(host, data,ip,guid)

    print("request from " .. guid .. " for lobby create")

    local tTargetGUID, targetID, serverGUID , combineData = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|([^|]+)|$")

    if CH_FindClient(tTargetGUID) == nil then
        print("invalid user,  warning, craft packet found from ip " .. SV_GetIPString(ip))
        return
    end

    print("user " .. targetID .. " wants to create a lobby in " .. serverGUID)

    local lobbyName, lobbyPassword = string.match(combineData, "^{(.-)%$(.-)}$")

    print("lobby name " .. lobbyName)
    print("lobby password " .. lobbyPassword)

    if BSEP_List[serverGUID] == nil then
        print("invalid server,  warning, craft packet found from ip " .. SV_GetIPString(ip))
        return
    end

    SendReliable2BattleServer(host, BSEP_List[serverGUID].IP,  BSEP_List[serverGUID].GUID, BattleChanel.Lobby,LobbyResponse.Lobby_Create_Request,{tTargetGUID,targetID,serverGUID, combineData})


    -- SendReliable2BattleServer(host, BSEP_List[serverGUID].IP,  BSEP_List[serverGUID].GUID, BattleChanel.Lobby,LobbyResponse.Lobby_Create_Request,{tTargetGUID,targetID,serverGUID,combineData})

end
