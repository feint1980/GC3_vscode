
---@class TabContainer
TabContainer = {
    ---@type pointer
    host = nil,
    ---@type pointer
    ptr = nil,
    posX = 0,
    posY = 0,
    width = 0,
    height = 0,
    ---@type pointer?
    parent = nil,
    ---@type table
    tabs = {}
}

---@Description create new instance of TabContainer
---@return TabContainer
function TabContainer:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

---@Description Init TabContainer
---@param host pointer instance of TGUIScriptingManager
---@param tPosX number x position
---@param tPosY number y position
---@param tWidth number width
---@param tHeight number height
---@param parent? pointer instance parent, default nil (main)
function TabContainer:init(host,tPosX,tPosY,
    tWidth,tHeight,parent)
    parent =  parent or nil
    self.host = host
    self.ptr = TGUI_TabContainer_Create(host,tPosX,
    tPosY,tWidth,tHeight,parent)
    self.posX = tPosX
    self.posY = tPosY
    self.width = tWidth
    self.height = tHeight
end

function TabContainer:setPos(x,y)
    self.posX = x
    self.posY = y
    TGUI_TabContainer_SetPos(self.ptr,x,y)
end

function TabContainer:setPosStr(x,y)
    TGUI_TabContainer_SetPosStr(self.ptr,x,y)
end

function TabContainer:setSize(width,height)
    self.width = width
    self.height = height
    TGUI_TabContainer_SetSize(self.ptr,width,height)
end

function TabContainer:setSizeStr(width,height)
    TGUI_TabContainer_SetSizeStr(self.ptr,width,height)
end

function TabContainer:addTab(name)
    self.tabs[name] = TGUI_TabContainer_AddTab(self.ptr,name)
end

--- MARK: Wrapper
--- wrapper of cpp_TabContainer_Create
---@Description create new tgui TabContainer object in cpp
---@param host pointer instance of TGUIScriptingManager
---@param tPosX number x position
---@param tPosY number y position
---@param tWidth number width
---@param tHeight number height
---@param parent? pointer instance parent, default nil (main)
---@return pointer instance of TGUI TabContainer
function TGUI_TabContainer_Create(host, tPosX, tPosY,
    tWidth, tHeight, parent)
    parent = parent or nil
    return cpp_TabContainer_Create(host, tPosX, tPosY, tWidth, tHeight, parent)
end

---@Desctiption set the position of the TabContainer
---@param tabContainer pointer instance of TabContainer
---@param x number x position
---@param y number y position
function TGUI_TabContainer_SetPos(tabContainer, x, y)
    cpp_TabContainer_SetPos(tabContainer, x, y)
end

---@Description set the position of the TabContainer
---@param tabContainer pointer instance of TabContainer
---@param x string x position
---@param y string y position
function TGUI_TabContainer_SetPosStr(tabContainer, x, y)
    cpp_TabContainer_SetPosStr(tabContainer, x, y)
end

---@Description set the size of the TabContainer
---@param tabContainer pointer instance of TabContainer
---@param width number width
---@param height number height
function TGUI_TabContainer_SetSize(tabContainer, width, height)
    cpp_TabContainer_SetSize(tabContainer, width, height)
end

---@Description set the size of the TabContainer
---@param tabContainer pointer instance of TabContainer
---@param width string width
---@param height string height
function TGUI_TabContainer_SetSizeStr(tabContainer, width, height)
    cpp_TabContainer_SetSizeStr(tabContainer, width, height)
end

--- wrapper of cpp_TabContainer_AddTab
---@param tabContainer pointer instance of TabContainer
---@param text string text
---@param isSelected boolean is selected
function TGUI_TabContainer_AddTab(tabContainer, text)
    return cpp_TabContainer_AddTab(tabContainer, text)
end
