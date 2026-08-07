BS_Fate_Favor = {}

BS_Fate_Favor.__index = BS_Fate_Favor

function BS_Fate_Favor:new()
    local o = setmetatable({}, self)



    self.__index = self
    return o
end