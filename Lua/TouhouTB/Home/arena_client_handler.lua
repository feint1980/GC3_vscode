package.path = package.path .. ';../../Lua/TouhouTB/skills/?.lua;'

require "homeGlobal"

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
        -- Arena_AddServer(v.name,v.ping)
    end

end