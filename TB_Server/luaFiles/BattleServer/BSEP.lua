BSEP =
{
    IP = nil,
    GUID = "",
    name = "",
    port = 0,
    cppObj = nil,
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
end

--- register IP
function BSEP:registerIP(host)
    cpp_registerIP(host,self.GUID, self.IP)
end

function BSEP:getIP(host)
    self.IP = cpp_getRegisteredIP(host,self.GUID)
    return self.IP
end


