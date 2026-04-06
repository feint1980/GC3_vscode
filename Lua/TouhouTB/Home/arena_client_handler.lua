package.path = package.path .. ';../../Lua/TouhouTB/skills/?.lua;'

require "clientGlobal"
require "homeGlobal"

require "EventPipeline"
require "PollEvent"
---MARK: Main server


--- Get battle server list
--- Get Battle Server List from main server
ClientMessageHandling[PacketChannel.ArenaChannel][ArenaResponse.Arena_Request_GetServerList] = function(host,data, guid)

    print("server list get !!!")
    local tData = string.match(data, "^|([^|]+)|$")
    local serverList, pos , err = JSON_Decode(tData)

    if err then
        print("Ke3 F3i117 exception (PacketChannel.ArenaChannel][ArenaResponse.Arena_Request_GetServerList)  JSON decode error:", err)
    end
    if serverList == nil then
        print("Ke3 F3i117 exception (PacketChannel.ArenaChannel][ArenaResponse.Arena_Request_GetServerList)")
        return
    end

    Arena_ResetList() --- Clear list
    for k,v in pairs(serverList) do
        print("server ID " .. k)
        print("server name " .. v.name)
        print("server IP " .. v.IP)
        print("server port " .. v.port)
        print("server ping " .. v.ping)
        ClientPingToServer(host, v.IP, v.port)
        Arena_Ping_List[k] = ArenaServer:new()
        Arena_Ping_List[k]:init(host,k,v.name,v.port,0,v.IP)

    end
    Arena_RequestLobbyList()
    print("CreateLobby_Request suppose to switch on")

    -- Poll_SetSignal("CreateLobby_Request")
end

--- Get the response from main server about the create lobby status
ClientMessageHandling[PacketChannel.ArenaChannel][ArenaResponse.Arena_RequestLobbyResponse] = function(host,data, guid)
    print("lobby response get !!!")

    -- print("data " .. data)
    local tTargetGUID, targetID, serverGUID , lobbyID, combineData = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|([^|]+)|([^|]+)|$")
    print("tTargetGUID " .. tTargetGUID)
    print("targetID " .. targetID)
    print("serverGUID " .. serverGUID)
    print("lobbyID " .. lobbyID)

    local lobbyName, lobbyPassword = string.match(combineData, "^{(.-)%$(.-)}$")

    print("lobbyName " .. lobbyName)
    print("lobbyPassword " .. lobbyPassword)

    local targetBattleServer = Arena_Ping_List[serverGUID] 
    if targetBattleServer == nil then
        print("Ke3 F3i117 exception (PacketChannel.ArenaChannel][ArenaResponse.Arena_RequestLobbyResponse) invalid server GUID")
        return
    end

    -- LobbyName = lobbyName

    InfoHolder_setStrVal("LobbyName", lobbyName)
    -- InfoHolder_setStrVal("Target_Lobby_ID", lobbyID)

    print(targetBattleServer.IP .. "|" .. targetBattleServer.port)
    Target_Lobby_ID = lobbyID
    Target_BattleServer_GUID = serverGUID
    InfoHolder_setStrVal("Target_Lobby_ID", lobbyID)
    InfoHolder_setStrVal("Target_BattleServer_GUID", serverGUID)

    --- Connect to battle server ( if passed, it will auto join to the lobby)
    ClientConnect2SV(host,targetBattleServer.IP,targetBattleServer.port)

    
end

ClientMessageHandling[PacketChannel.ArenaChannel][ArenaResponse.Arena_RequestLobbyListResponse] = function(host,data, guid)

    print("response from " .. guid .. " for lobby list")
    local tData = string.match(data, "^|([^|]+)|$")
    -- print("tData " .. tData)

    local serverList, pos, err = JSON_Decode(tData)
    if err then
        print("Ke3 F3i117 exception (PacketChannel.ArenaChannel][ArenaResponse.Arena_RequestLobbyListResponse)  JSON decode error:", err)
    end
    if serverList == nil then
        print("Ke3 F3i117 exception (PacketChannel.ArenaChannel][ArenaResponse.Arena_RequestLobbyListResponse)")
        return
    end

    TM_addTask(function()
        print("update the lobbies ")
        for k,v in pairs(serverList) do
            if Arena_Ping_List[k] == nil then
                print("mismatch battle server ID found" .. k)
            else
                print("found lobby list for battle server " .. k)
                Arena_Ping_List[k].lobbyList = {}
                for n,m in pairs(serverList[k].lobbyList) do
                    print("data check " .. n)
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
                    Arena_Ping_List[k].lobbyList[n] = serverList[k].lobbyList[n]
                end
            end
        end
        Arena_UpdateLobbies(serverList) -- update afterward
    end
    ,
    10)
end

---Arena_CreateLobby_Request 

---- MARK:Home Common

--- Home common
--- handle pong from battle servers
HomeMain_HandleTask[PacketID.ID_UNCONNECTED_PONG] = function(host,packet,RakNetPacket)
    print("ID_UNCONNECTED_PONG get")
    -- local tData = SV_GetPacketData(host,RakNetPacket)
    -- print("tData " .. tData)
    cppCollectPong(host,RakNetPacket)
end

--- Connected to battle server
HomeMain_HandleTask[PacketID.ID_CONNECTION_REQUEST_ACCEPTED] = function(host,packet,RakNetPacket)

    local currentServerGUID = cppGetCurrentBattleServerGUID(host)
    print("step 1")
    print("current server guid " .. currentServerGUID)
    local tGuid = Client_GetGUID_FromPacket(RakNetPacket)
    if currentServerGUID == "" then 
        print("step 2a")
        print("no current server selected(this is OK) ")

        -- print("guid : " .. tGuid)
        cppSelecBattleServer(host,tGuid)
        print("accepted by battle server " .. tGuid)
        -- end
    else
        -- print("step 2b")
        -- local tGUID = InfoHolder_getStrVal("MainInfo.guid")
        -- local tID = InfoHolder_getStrVal("MainInfo.id")
            
        -- cppSelecBattleServer(host,tGuid) -- register to C++ side
        -- print("accepted by battle server " .. tGuid)
        -- print("battle server registered to C++ side")
        -- local targetLobbyID = InfoHolder_getStrVal("Target_Lobby_ID")
        -- if targetLobbyID ~= "" then
        --     print("got lobby " .. targetLobbyID)
        -- end
        -- SendBattleRequest(BattlePacketChannel.Lobby,CLobbyResponse.Lobby_Join_Request, {tGUID, tID ,targetLobbyID },5,0.1,0.15)
    end

    local tIP = Client_GetIP_FromPacket(RakNetPacket)
    print("IP " .. tIP)
    currentServerGUID = cppGetCurrentBattleServerGUID(host)

    local targetLobbyID = InfoHolder_getStrVal("Target_Lobby_ID")
    if targetLobbyID ~= "" then
        print("got lobby " .. Target_Lobby_ID)
        -- local tIP = cppGetCurrentBattleServerIP(host)

        -- print("my id " .. MainInfo.id)
        print("current server guid " .. currentServerGUID)


        local tGUID = InfoHolder_getStrVal("MainInfo.guid")
        local tID = InfoHolder_getStrVal("MainInfo.id")
        

        SendBattleRequest(BattlePacketChannel.Lobby,CLobbyResponse.Lobby_Join_Request, {tGUID, tID ,targetLobbyID },5,0.1,0.15)

        -- SendReliable2BattleServer(host, tIP, currentServerGUID,   )
        -- send request to join lobby to server
    end
end

HomeMain_HandleTask[PacketID.ID_DISCONNECTION_NOTIFICATION] = function(host,packet,RakNetPacket)
    local tGuid = Client_GetGUID_FromPacket(RakNetPacket)

    print("ID_DISCONNECTION_NOTIFICATION from " .. tGuid)
    cppSelecBattleServer(host,"")

end

-- HomeMain_HandleTask[PacketID.ID_CONNECTION_REQUEST_ACCEPTED] = function(host,packet,RakNetPacket)
--     local tGuid = Client_GetGUID_FromPacket(RakNetPacket)
--     print("ID_CONNECTION_REQUEST_ACCEPTED from " .. tGuid)
-- end

ClientMessageHandling[PacketChannel.ArenaChannel][ArenaResponse.Arena_RequestJoinLobby_WithBSGUID_LobbyID_Response] = function(host,data, guid)

    local serverGUID, lobbyID, lobbyName, joinResult = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|([^|]+)|$")
    print("serverGUID " .. serverGUID)
    print("lobbyID " .. lobbyID)
    print("joinResult " .. joinResult)
    local tResult = tonumber(joinResult)
    
    if tResult == 1 then
        print("joining lobby " .. lobbyID .. " succeed")
        local targetBattleServer = Arena_Ping_List[serverGUID] 
        if targetBattleServer == nil then
            print("Ke3 F3i117 exception (PacketChannel.ArenaChannel][ArenaResponse.Arena_RequestLobbyResponse) invalid server GUID")
            return
        end

        InfoHolder_setStrVal("Target_Lobby_ID", lobbyID)
        InfoHolder_setStrVal("LobbyName", lobbyName)
        print(targetBattleServer.IP .. "|" .. targetBattleServer.port)
        Target_Lobby_ID = lobbyID
        --- Connect to battle server ( if passed, it will auto join to the lobby)
        ClientConnect2SV(host,targetBattleServer.IP,targetBattleServer.port)

    Join_State = 0
    Prompt_UI_Table["Arena_Status"]:show(false)


    elseif tResult == 2 then
        -- Prompt_UI_Table["Arena_Status"]:show(false)
        Prompt_UI_Table["Arena_Noti"]:showMsg("Invalid password !")
        Join_State = 0
    elseif tResult == 3 then
        -- Prompt_UI_Table["Arena_Status"]:show(false)
        Prompt_UI_Table["Arena_Noti"]:showMsg("Room is full !")
        Join_State = 0
    else
        -- Prompt_UI_Table["Arena_Status"]:show(false)
        Prompt_UI_Table["Arena_Noti"]:showMsg("Invalid join !")
        -- Join_State = 0
    end
        

    InfoHolder_setStrVal("Target_BattleServer_GUID", serverGUID)
end



--- MARK:Battle Server 


