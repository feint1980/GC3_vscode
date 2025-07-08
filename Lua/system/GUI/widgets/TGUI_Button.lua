
---@class (exact) Button
---@field host pointer instance of TGUIScriptingManager
---@field ptr pointer instance of TGUI Button
---@field text string text to display
---@field posX number x position
---@field posY number y position
---@field width number width
---@field height number height
---@field parent pointer instance of parent, default nil (main)
Button = {
    ---@type pointer
    host = nil,
    ---@type pointer
    ptr = nil,
    text ="",
    posX = 0,
    posY = 0,
    width = 0,
    height = 0,
    ---@type pointer?
    parent = nil
}

---@Description create new instance of Button
---@return Button
function Button:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end


function Button:init(host,tText,tX,tY,tWidth,tHeight,tParent)
    self.host = host
    self.ptr = TGUI_Button_Create(host,tText,tX,tY,tWidth,tHeight,tParent)
    self.text = tText
    self.posX = tX
    self.posY = tY
    self.width = tWidth
    self.height = tHeight
    self.parent = tParent
end

function Button:setPos(tX,tY)
    self.posX = tX
    self.posY = tY
    TGUI_Button_SetPos(self.ptr,tX,tY)
end

function Button:setPosStr(tXStr,tYStr)
    self.posX = tXStr
    self.posY = tYStr
    TGUI_Button_SetPosStr(self.ptr,tXStr,tYStr)
end

function Button:setSize(tWidth,tHeight)
    self.width = tWidth
    self.height = tHeight
    TGUI_Button_SetSize(self.ptr,tWidth,tHeight)
end

function Button:setSizeStr(tWidthStr,tHeightStr)
    self.width = tWidthStr
    self.height = tHeightStr
    TGUI_Button_SetSizeStr(self.ptr,tWidthStr,tHeightStr)
end

function Button:setOnClickCallBack(tCallback)
    TGUI_Button_setOnClickCallBack(self.ptr,tCallback)
end

--- MARK: Wrapper
--- function wrapper of cpp_Button_Create
function TGUI_Button_Create(host, text, posX, posY, width, height, parent)
    parent = parent or nil
    return cpp_Button_Create(text, posX, posY, width, height, parent)
end


--- function wrapper of cpp_Button_SetPos
function TGUI_Button_SetPos(ptr, posX, posY)
    cpp_Button_SetPos(ptr, posX, posY)
end

function TGUI_Button_SetPosStr(ptr, posXStr, posYStr)
    cpp_Button_SetPosStr(ptr, posXStr, posYStr)
end

--- function wrapper of cpp_Button_SetSize
function TGUI_Button_SetSize(ptr, width, height)
    cpp_Button_SetSize(ptr, width, height)
end

function TGUI_Button_SetSizeStr(ptr, widthStr, heightStr)
    cpp_Button_SetSizeStr(ptr, widthStr, heightStr)
end

--- function wrapper of cpp_Button_setOnClickCallBack
--- param button pointer
--- param callback function
function TGUI_Button_setOnClickCallBack(ptr, callback)
    cpp_Button_setOnClickCallBack(ptr, callback)
end


-- 
-- --- function wrapper of cpp_Button_SetText
-- function TGUI_Button_SetText(ptr, text)
--     cpp_Button_SetText(ptr, text)
-- end

