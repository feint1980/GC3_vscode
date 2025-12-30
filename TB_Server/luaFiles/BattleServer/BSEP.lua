require "LobbyEP"

BSEP =
{
    ---@type RakNet_SystemAddress
    IP = nil,
    GUID = "",
    name = "",
    port = 0,
    ---@type pointer of ClientScriptingManager
    networkInstance = nil,
    lobbyList = {}
}

function BSEP:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function BSEP:init(host,tIP, guid, name,port)
    self.IP = tIP
    self.GUID = guid
    self.name = name
    self.port = port
    self:registerIP(host)
    self.networkInstance = host
    self.lobbyList = {}
end

--- register IP
function BSEP:registerIP(host)
    cpp_registerIP(host,self.GUID, self.IP)
end

function BSEP:getIP()
    self.IP = cpp_getRegisteredIP(self.networkInstance,self.GUID)
    return self.IP
end

function BSEP:addLobby(lID, lName, lPassword)
    self.lobbyList[lID] = LobbyEP:new()
    self.lobbyList[lID]:init(lID, lName, lPassword)
end

function BSEP:removeLobby(lID)
    self.lobbyList[lID] = nil
end