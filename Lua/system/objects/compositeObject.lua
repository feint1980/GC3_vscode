

L_compositeObject = {

    host = nil, 
    posX = 0,
    posY = 0,
    width = 0,
    height = 0,
    depth = 0,
    angle = 0,

}

function L_compositeObject:new (o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function L_compositeObject:init (F_LuaRendererContext_ptr, t_posX, t_posY, t_width, t_height, t_depth, t_angle)

    self.posX = t_posX
    self.posY = t_posY
    self.width = t_width
    self.height = t_height
    self.depth = t_depth
    self.angle = t_angle

    self.host = LRC_CreateCompositeObject(F_LuaRendererContext_ptr, self.posX, self.posY, self.width, self.height, self.angle, self.depth)
end
