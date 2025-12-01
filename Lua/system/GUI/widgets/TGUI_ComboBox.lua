

ComboBox = {
    ---@type pointer
    host = nil,
    ---@type pointer
    ptr = nil,
    posX = 0,
    posY = 0,
    width = 0,
    height = 0,
    ---@type pointer?
    parent = nil
}


function ComboBox:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end


function ComboBox:init(host, x, y, width, height, parent)
    self.host = host
    self.ptr = TGUI_ComboBox_Create(x, y, width, height, parent)
end


function TGUI_ComboBox_Create(host, x, y, width, height, parent)
    parent = parent or nil
    return cpp_ComboBox_Create(host, x, y, width, height, parent)
    
end