
Combat_dock_left = {

    host = nil,

}



function Combat_dock_left:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end