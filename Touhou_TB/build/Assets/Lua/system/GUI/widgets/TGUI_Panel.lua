
---@class TextAlginment
TextAlginment = {
    Left = 0,
    Center = 1,
    Right = 2
}

---@class PanelShowType
PanelShowType = {
    Fade = 0,
    Scale = 1,
    SlideToRight = 2,
    SlideToleft = 3,
    SlideToBottom = 4,
    SlideToTop = 5,
    SlideFromLeft = 2,
    SlideFromRight = 3,
    SlideFromTop = 4,
    SlideFromBottom = 5,

}


--- @class (exact) Panel
--- @field host pointer instance of TGUIScriptingManager
--- @field ptr pointer instance of TGUI Panel
--- @field posX number x position
--- @field posY number y position
--- @field width number width
--- @field height number height
--- @field parent? pointer instance of parent, default nil (main)
Panel = {
    host = nil,
    ptr = nil,
    posX = 0,
    posY = 0,
    width = 0,
    height = 0,
    parent = nil
}


---@Description create new instance of Panel
---@return Panel
function Panel:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end


---@Description create new instance of Panel
---@param host pointer instance of TGUIScriptingManager
---@param posX number x position
---@param posY number y position
---@param width number width
---@param height number height
---@param parent? pointer instance of parent, default nil (main)
function Panel:init(host, posX, posY, width, height, parent)
    parent = parent or nil

    self.host = host
    self.ptr = TGUI_Panel_Create(host, posX, posY, width, height, parent)
    self.posX = posX
    self.posY = posY
    self.width = width
    self.height = height
    self.parent = parent
end

---@Description set the position of the panel
---@param posX number x position
---@param posY number y position
function Panel:setPos(posX, posY)
    TGUI_Panel_SetPos(self.ptr, posX, posY)
    self.posX = posX
    self.posY = posY
end

---@Description set the position of the panel (string version)
---@param posXStr string x position
---@param posYStr string y position
function Panel:setPosStr(posXStr, posYStr)
    TGUI_Panel_SetPosStr(self.ptr, posXStr, posYStr)
end

---@Description set the size of the panel
---@param width number width
---@param height number height
function Panel:setSize(width, height)
    self.width = width
    self.height = height    
    TGUI_Panel_SetSize(self.ptr, width, height)
end

---@Description set the size of the panel (string version)
---@param width string width
---@param height string height
function Panel:setSizeStr(width, height)
    TGUI_Panel_SetSizeStr(self.ptr, width, height)
end


---@Description hide panel with effect
---@param type number type
---@param time number time to disappear
function Panel:hideWithEffect(type,time)
    TGUI_Panel_HideWithEffect(self.ptr, type,time)
end

---@Description show panel with effect
---@param type number type
---@param time number time to appear
function Panel:showWithEffect(type,time)
    TGUI_Panel_ShowWithEffect(self.ptr, type,time)
end

---@Description set Alignment of Panel
---@param originX number
---@param originY number
function Panel:setAligment(originX,originY)
    TGUI_Panel_SetAlignment(self.ptr, originX,originY)
end


---@Description set the visibility of the panel
---@param visible boolean
function Panel:setVisible(visible)
    TGUI_Panel_SetVisible(self.ptr, visible)
end

---- MARK: Wrapper

--- wrapper of cpp_Panel_Create
---@param host pointer instance of TGUIScriptingManager
---@param posX number x position
---@param posY number y position
---@param width number width
---@param height number height
---@param parent? pointer instance of parent, default nil (main)
---@return pointer instance of TGUI Panel
function TGUI_Panel_Create(host, posX, posY, width, height, parent)
    return cpp_Panel_Create(host, posX, posY, width, height, parent)
end


--- wrapper of cpp_Panel_SetPos
---@param panel pointer instance of TGUI Panel
---@param posX number x position
---@param posY number y position
function TGUI_Panel_SetPos(panel, posX, posY)
    cpp_Panel_SetPos(panel, posX, posY)
end

--- wrapper of cpp_Panel_SetPosStr
---@param panel pointer instance of TGUI Panel
---@param posXStr string x position
---@param posYStr string y position
function TGUI_Panel_SetPosStr(panel, posXStr, posYStr)
    cpp_Panel_SetPosStr(panel, posXStr, posYStr)
end


--- wrapper of cpp_Panel_SetSize
---@param panel pointer instance of TGUI Panel
---@param width number width
---@param height number height
function TGUI_Panel_SetSize(panel, width, height)
    cpp_Panel_SetSize(panel, width, height)
end

--- wrapper of cpp_Panel_SetSizeStr
---@param panel pointer instance of TGUI Panel
---@param width string width
---@param height string height
function TGUI_Panel_SetSizeStr(panel, width, height)
    cpp_Panel_SetSizeStr(panel, width, height)
end


--- wrapper of cpp_Panel_HideWithEffect
---@param panel pointer instance of TGUI Panel
---@param type number
---@param time number
function TGUI_Panel_HideWithEffect(panel,type, time)
    cpp_Panel_HideWithEffect(panel,type, time)
end

--- wrapper of cpp_Panel_HideWithEffect
---@param panel pointer instance of TGUI Panel
---@param type number
---@param time number
function TGUI_Panel_ShowWithEffect(panel,type, time)
    cpp_Panel_ShowWithEffect(panel, type,time)
end


--- wrapper of cpp_Panel_setVisible
---@param panel pointer instance of TGUI Panel
---@param visible boolean
function TGUI_Panel_SetVisible(panel, visible)
    cpp_Panel_SetVisible(panel, visible)
end

--- wrapper of cpp_Panel_setAlginmen
---@param panel pointer instance of TGUI Panel
---@param originX number
---@param originY number
function TGUI_Panel_SetAlignment(panel,originX,originY)
    cpp_Panel_SetAlignment(panel, originX,originY)
end