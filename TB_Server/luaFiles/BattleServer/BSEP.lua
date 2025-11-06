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

function BSEP:init(tIP, guid, name,port)
    self.IP = tIP
    self.GUID = guid
    self.name = name
    self.port = port
end

function BSEP:getSlot()

end

