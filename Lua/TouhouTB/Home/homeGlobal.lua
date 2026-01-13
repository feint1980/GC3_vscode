
require "clientGlobal"

--- Arena Server

Arena_Ping_List = {

}

ArenaServer = {
    clientHost = nil,
    guid = "",
    name = "",
    port = 0,
    ping = 0,
    IP = nil,
    lobbyList = {},
}

function ArenaServer:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function ArenaServer:init(tClientHost,tGuid, tName, tPort, tPing, tIP)
    self.clientHost = tClientHost
    self.guid = tGuid
    self.name = tName
    self.port = tPort
    self.ping = tPing
    self.IP = tIP
    
end

function ArenaServer:setPing(ping)
    self.ping = ping
end
