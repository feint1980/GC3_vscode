
require "clientGlobal"

--- Arena Server

MenuPanels = {}

Arena_Ping_List = {

}

ArenaServer = {}
ArenaServer.__index = ArenaServer

function ArenaServer:new()

    local o = setmetatable({}, self)
    o.clientHost = nil
    o.guid = ""
    o.name = ""
    o.port = 0
    o.ping = 0
    o.IP = nil
    o.lobbyList = {}

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
