
---@class ComboBox
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
    self.parent = parent
    self.x = x
    self.y = y
    self.width = width
    self.height = height
    self.ptr = TGUI_ComboBox_Create(host, x, y, width, height, parent)
end

function ComboBox:setPos(x, y)
    TGUI_ComboBox_SetPos(self.ptr, x, y)
    self.x = x
    self.y = y
end

function ComboBox:setPosStr(x, y)
    TGUI_ComboBox_SetPosStr(self.ptr, x, y)
    self.x = x
    self.y = y
end

function ComboBox:setSize(width, height)
    TGUI_ComboBox_SetSize(self.ptr, width, height)
    self.width = width
    self.height = height
end

function ComboBox:setSizeStr(width, height)
    TGUI_ComboBox_SetSizeStr(self.ptr, width, height)
    self.width = width
    self.height = height
end

function ComboBox:addItem(itemStr)
    TGUI_ComboBox_AddItem(self.ptr, itemStr)
end

function ComboBox:clearItems()
    TGUI_ComboBox_ClearItems(self.ptr)
end


function TGUI_ComboBox_Create(host, x, y, width, height, parent)
    parent = parent or nil
    return cpp_ComboBox_Create(host, x, y, width, height, parent)
end

function TGUI_ComboBox_SetPos(comboBox, x, y)
    cpp_ComboBox_SetPos(comboBox, x, y)
end

function TGUI_ComboBox_SetPosStr(comboBox, x, y)
    cpp_ComboBox_SetPosStr(comboBox, x, y)
end

function TGUI_ComboBox_SetSize(comboBox, width, height)
    cpp_ComboBox_SetSize(comboBox, width, height)
end

function TGUI_ComboBox_SetSizeStr(comboBox, width, height)
    cpp_ComboBox_SetSizeStr(comboBox, width, height)
end

function TGUI_ComboBox_AddItem(comboBox,itemStr)

    cpp_ComboBox_AddItems(comboBox, itemStr)
end

function TGUI_ComboBox_ClearItems(comboBox)
    cpp_ComboBox_ClearItems(comboBox)
end