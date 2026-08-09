---@class (exact) ClientEP
---@field IP? pointer instance of IP
---@field GUID string
---@field name string
---@field cppObj? pointer instance of ClientEP in C++
ClientEP = 
{
    -- IP = nil,
    -- GUID = "",
    -- name = "",
    -- cppObj = nil,
}

--- Constructor
--- @return ClientEP
function ClientEP:new()
    local o = setmetatable({}, self)
    o.IP = nil
    o.GUID = ""
    o.name = ""
    o.cppObj = nil
    
    self.__index = self
    return o
end

--- initialize ClientEP
---@param tIP pointer instance of IP
---@param guid string guid of the client
---@param name string name of the client
function ClientEP:init(tIP, guid, name)
    self.IP = tIP
    self.GUID = guid
    self.name = name
    --- add in C++
    self.cppObj = CH_cpp_addClientEP( tIP, guid, name)

end

function ClientEP:getIP() 
    return SV_getClientIPByGUID_CPP(self.GUID)
end


