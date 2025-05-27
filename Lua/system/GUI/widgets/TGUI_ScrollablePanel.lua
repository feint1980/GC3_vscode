
---@class PanelShowType
ScrollablePanelShowType = {
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

--- @class (exact) ScrollablePanel
--- @field host pointer instance of TGUIScriptingManager
--- @field ptr pointer instance of TGUI Panel
--- @field posX number x position
--- @field posY number y position
--- @field width number width
--- @field height number height
--- @field parent pointer instance of parent, default nil (main)
--- @field visible boolean default true
ScrollablePanel = {
    ---@type pointer
    host = nil,
    ---@type pointer
    ptr = nil,
    posX = 0,
    posY = 0,
    width = 0,
    height = 0,
    ---@type pointer
    parent = nil,
    ---@type boolean
    visible = true
}

---@Description create new instance of Panel
---@return Panel
function ScrollablePanel:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

---@Description create new instance of ScrollablePanel
---@param host pointer instance of TGUIScriptingManager
---@param posX number x position
---@param posY number y position
---@param width number width
---@param height number height
---@param parent? pointer instance of parent, default nil (main)
function ScrollablePanel:init(host, posX, posY, 
    width, height, parent)

    print("ScrollablePanel init")
    parent = parent or nil
    self.parent = parent
    self.host = host
    self.ptr = TGUI_ScrollablePanel_Create(host, posX, posY, width, height, self.parent)
    self.posX = posX
    self.posY = posY
    self.width = width
    self.height = height
    if self.parent ~= nil then
        print("parent is not nil")
        print(self.parent)
    else
        print("parent is nil")
    end
end

---@Description set the position of the Scrollablepanel
---@param posX number x position
---@param posY number y position
function ScrollablePanel:setPos(posX, posY)
    TGUI_ScrollablePanel_SetPos(self.ptr, posX, posY)
    self.posX = posX
    self.posY = posY
end

---@Description set the position of the Scrollablepanel (string version)
---@param posXStr string x position
---@param posYStr string y position
function ScrollablePanel:setPosStr(posXStr, posYStr)
    TGUI_ScrollablePanel_SetPosStr(self.ptr, posXStr, posYStr)
end

---@Description set the size of the Scrollablepanel
---@param width number width
---@param height number height
function ScrollablePanel:setSize(width, height)
    self.width = width
    self.height = height    
    TGUI_ScrollablePanel_SetSize(self.ptr, width, height)
end

---@Description set the size of the Scrollablepanel (string version)
---@param width string width
---@param height string height
function ScrollablePanel:setSizeStr(width, height)
    TGUI_ScrollablePanel_SetSizeStr(self.ptr, width, height)
end

---@Description hide Scrollablepanel with effect
---@param type number type
---@param time number time to disappear
function ScrollablePanel:hideWithEffect(type,time)
    TGUI_ScrollablePanel_HideWithEffect(self.ptr, type,time)
    self.visible = false
end

---@Description show Scrollablepanel with effect
---@param type number type
---@param time number time to appear
function ScrollablePanel:showWithEffect(type,time)
    TGUI_ScrollablePanel_ShowWithEffect(self.ptr, type,time)
    self.visible = true
end

---@Description set Alignment of ScrollablePanel
---@param originX number
---@param originY number
function ScrollablePanel:setAlignment(originX,originY)
    TGUI_ScrollablePanel_SetAlignment(self.ptr, originX,originY)
end

---@Description set the visibility of the Scrollablepanel
---@param visible boolean
function ScrollablePanel:setVisible(visible)
    TGUI_ScrollablePanel_SetVisible(self.ptr, visible)
    self.visible = visible
end

function ScrollablePanel:clearItems()
    TGUI_ScrollablePanel_ClearItems(self.ptr)
end

---@Description get the size of the Scrollablepanel
---@return number width, number height
function ScrollablePanel:getSize()
    return TGUI_ScrollablePanel_GetSize(self.ptr)
end

---- MARK: Wrapper

--- wrapper of cpp_ScrollablePanel_Create
---@param host pointer instance of TGUIScriptingManager
---@param posX number x position
---@param posY number y position
---@param width number width
---@param height number height
---@param parent? pointer instance of parent, default nil (main)
---@return pointer instance of TGUI Panel
function TGUI_ScrollablePanel_Create(host, posX, posY, width, height, parent)
    return cpp_ScrollablePanel_Create(host, posX, posY, width, height, parent)
end

--- wrapper of cpp_ScrollablePanel_SetPos
---@param panel pointer instance of TGUI Panel
---@param posX number x position
---@param posY number y position
function TGUI_ScrollablePanel_SetPos(panel, posX, posY)
    cpp_ScrollablePanel_SetPos(panel, posX, posY)
end

--- wrapper of cpp_ScrollablePanel_SetPosStr
---@param panel pointer instance of TGUI Panel
---@param posXStr string x position
---@param posYStr string y position
function TGUI_ScrollablePanel_SetPosStr(panel, posXStr, posYStr)
    cpp_ScrollablePanel_SetPosStr(panel, posXStr, posYStr)
end

--- wrapper of cpp_ScrollablePanel_SetSize
---@param panel pointer instance of TGUI Panel
---@param width number width
---@param height number height
function TGUI_ScrollablePanel_SetSize(panel, width, height)
    cpp_ScrollablePanel_SetSize(panel, width, height)
end

--- wrapper of cpp_ScrollablePanel_SetSizeStr
---@param panel pointer instance of TGUI Panel
---@param width string width
---@param height string height
function TGUI_ScrollablePanel_SetSizeStr(panel, width, height)
    cpp_ScrollablePanel_SetSizeStr(panel, width, height)
end

--- wrapper of cpp_ScrollablePanel_HideWithEffect
---@param panel pointer instance of TGUI Panel
---@param type number
---@param time number
function TGUI_ScrollablePanel_HideWithEffect(panel,type, time)
    cpp_ScrollablePanel_HideWithEffect(panel,type, time)
end

--- wrapper of cpp_ScrollablePanel_HideWithEffect
---@param panel pointer instance of TGUI Panel
---@param type number
---@param time number
function TGUI_ScrollablePanel_ShowWithEffect(panel,type, time)
    cpp_ScrollablePanel_ShowWithEffect(panel, type,time)
end

--- wrapper of cpp_ScrollablePanel_setVisible
---@param panel pointer instance of TGUI Panel
---@param visible boolean
function TGUI_ScrollablePanel_SetVisible(panel, visible)
    cpp_ScrollablePanel_SetVisible(panel, visible)
end

--- wrapper of cpp_ScrollablePanel_setAlginmen
---@param panel pointer instance of TGUI Panel
---@param originX number
---@param originY number
function TGUI_ScrollablePanel_SetAlignment(panel,originX,originY)
    cpp_ScrollablePanel_SetAlignment(panel, originX,originY)
end

--- wrapper of cpp_ScrollablePanel_GetSize
---@param panel pointer instance of TGUI Panel
---@return number width, number height
function TGUI_ScrollablePanel_GetSize(panel)
    return cpp_ScrollablePanel_GetSize(panel)
end

--- wrapper fo cpp_ScrollablePanel_ClearItems
---@param panel pointer instance of TGUI Panel
function TGUI_ScrollablePanel_ClearItems(panel)
    cpp_ScrollablePanel_ClearItems(panel)
end