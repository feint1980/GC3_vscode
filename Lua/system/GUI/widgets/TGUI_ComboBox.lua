
---@class ComboBox
---@field host pointer
---@field ptr pointer
---@field posX number
---@field posY number
---@field width number
---@field height number
ComboBox = {}
ComboBox.__index = ComboBox

function ComboBox:new()

    local o = setmetatable({}, self)
    ---@type pointer
    o.host = nil
    ---@type pointer
    o.ptr = nil
    o.posX = 0
    o.posY = 0
    o.width = 0
    o.height = 0
    ---@type pointer?
    o.parent = nil

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

function ComboBox:remove()
    cpp_tgui_remove_widget(self.host, self.ptr)
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

function ComboBox:getSelectedItem()
    return TGUI_ComboBox_GetSelectedItem(self.ptr)
end

function ComboBox:getSelectedItemIndex()
    return TGUI_ComboBox_GetSelectedItemIndex(self.ptr)
end

function ComboBox:setOnSelectCallback(callBack)
    TGUI_ComboBox_OnSelectCallback(self.ptr, callBack)
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

function TGUI_ComboBox_GetSelectedItem(comboBox)
    return cpp_ComboBox_GetSelectedItem(comboBox)
end

function TGUI_ComboBox_GetSelectedItemIndex(comboBox)
    return cpp_ComboBox_GetSelectedItemIndex(comboBox)
end

function TGUI_ComboBox_OnSelectCallback(comboBox, callBack)
    cpp_ComboBox_RegisterOnSelectionChanged(comboBox, callBack)
end

