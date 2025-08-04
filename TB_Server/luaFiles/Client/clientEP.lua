

---@class (exact) ClientEP
---@field systemAddress? pointer instance of systemAddress
---@field GUID string
---@field IP? pointer instance of RakNet::SystemAddress IP
---@field name string
ClientEP = 
{
    systemAddress = nil,
    GUID = "",
    name = "",
    IP = nil
}

--- Constructor
--- @return ClientEP
function ClientEP:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

--- initialize ClientEP
---@param tSystemAddress pointer instance of systemAddress
---@param guid string guid of the client
---@param name string name of the client
function ClientEP:init(tSystemAddress, guid, name)
    self.systemAddress = tSystemAddress
    self.GUID = guid
    self.name = name
end