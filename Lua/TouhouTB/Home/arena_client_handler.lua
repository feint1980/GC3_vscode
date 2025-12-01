package.path = package.path .. ';../../Lua/TouhouTB/skills/?.lua;'

require "homeGlobal"


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
        Arena_Ping_List[k]:init(host,k,v.name,v.port,0)

    end

end

ClientMessageHandling[PacketChannel.ArenaChannel][ArenaResponse.Arena_RequestLobby_Create] = function(host,data, guid)
    print("request to create lobby get")

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

    print("accepted by battle server ")
    local tGuid = Client_GetGUID_FromPacket(RakNetPacket)
    print("guid : " .. tGuid)
    local tIP = Client_GetIP_FromPacket(RakNetPacket)
    print("IP " .. tIP)
    cppSelecBattleServer(host,tGuid)
    -- Client_AddCryptor(host,tGuid)

end

--- MARK:Battle Server 



































