package.path = package.path .. ';../../Lua/TouhouTB/skills/?.lua;'

require "homeGlobal"


Target_Lobby_ID = ""

---MARK: Main server


--- Get battle server list
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

    Arena_ResetList()
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

end

ClientMessageHandling[PacketChannel.ArenaChannel][ArenaResponse.Arena_RequestLobbyResponse] = function(host,data, guid)
    print("lobby response get !!!")

    -- print("data " .. data)
    local tTargetGUID, targetID, serverGUID , lobbyID = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|([^|]+)|$")

    print("tTargetGUID " .. tTargetGUID)
    print("targetID " .. targetID)
    print("serverGUID " .. serverGUID)
    print("lobbyID " .. lobbyID)


    local targetBattleServer = Arena_Ping_List[serverGUID] 
    if targetBattleServer == nil then
        print("Ke3 F3i117 exception (PacketChannel.ArenaChannel][ArenaResponse.Arena_RequestLobbyResponse) invalid server GUID")
        return
    end

    print(targetBattleServer.IP .. "|" .. targetBattleServer.port)
    Target_Lobby_ID = lobbyID
    ClientConnect2SV(host,targetBattleServer.IP,targetBattleServer.port)

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

    if currentServerGUID == "" then 
        print("no current server selected(this is OK) ")


        print("accepted by battle server ")
        local tGuid = Client_GetGUID_FromPacket(RakNetPacket)
        print("guid : " .. tGuid)
        cppSelecBattleServer(host,tGuid)
        local tIP = Client_GetIP_FromPacket(RakNetPacket)
        print("IP " .. tIP)
        currentServerGUID = cppGetCurrentBattleServerGUID(host)
        if currentServerGUID ~= tGuid then
            print(currentServerGUID .. "/" .. tGuid)
            print("multiple battle server selected, aborting ...")
            return
            -- cppSelecBattleServer(host,tGuid)
        -- elseif currentServerGUID == tGuid then 
        --     -- cppSelecBattleServer(host,tGuid) -- register to C++ side
        --     print("reconnect or reenter the server")
        --     -- cppSelecBattleServer(host,tGuid) -- register to C++ side
        else 
            if Target_Lobby_ID ~= "" then
                print("got lobby " .. Target_Lobby_ID)
                local tIP = cppGetCurrentBattleServerIP(host)

                SendBattleRequest(BattlePacketChannel.Lobby,CLobbyResponse.Lobby_Join_Request, {tGuid,currentServerGUID,Target_Lobby_ID },5,0.1,0.15)

                -- SendReliable2BattleServer(host, tIP, currentServerGUID,   )
                -- send request to join lobby to server
            end
        end
    else

            cppSelecBattleServer(host,tGuid) -- register to C++ side
            print("battle server registered to C++ side")
            if Target_Lobby_ID ~= "" then
                print("got lobby " .. Target_Lobby_ID)
            end

    end

end

HomeMain_HandleTask[PacketID.ID_DISCONNECTION_NOTIFICATION] = function(host,packet,RakNetPacket)
    local tGuid = Client_GetGUID_FromPacket(RakNetPacket)

    print("ID_DISCONNECTION_NOTIFICATION from " .. tGuid)
    cppSelecBattleServer(host,"")
    
end

--- MARK:Battle Server 



































