require "LobbyEP"

BSEP ={}
BSEP.__index = BSEP

function BSEP:new()
    local o =  setmetatable({}, self)

    ---@type RakNet_SystemAddress
    o.IP = nil
    o.GUID = ""
    o.name = ""
    o.port = 0
    ---@type pointer of ClientScriptingManager
    o.networkInstance = nil
    o.lobbyList = {}

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

-- function BSEP:addLobby(lID, lName, lPassword)
--     self.lobbyList[lID] = LobbyEP:new()
--     self.lobbyList[lID]:init(lID, lName, lPassword)
-- end

-- function BSEP:removeLobby(lID)
--     self.lobbyList[lID] = nil
-- end