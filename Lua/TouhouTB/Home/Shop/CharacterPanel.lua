package.path = package.path .. ';../../Lua/system/GUI/?/?.lua;' .. ';../../Lua/system/GUI/widgets/?.lua;' .. ';../../Lua/TouhouTB/Home/?.lua;'

require "TGUI_Label"
require "TGUI_Panel"
require "TGUI_RTLabel" 
require "TGUI_Editbox"
require "TGUI_Picture"
require "TGUI_TabContainer"
require "TGUI_ScrollablePanel"


---@class (exact) CharacterPanel
---@field panel Panel
---@field picture Picture
---@field displayNameLabel Label
---@field priceLabel Label
---@field parent ScrollablePanel
CharacterPanel = {
    ---@type Panel
    panel = nil,
    ---@type Picture
    picture = nil,
    ---@type Label
    displayNameLabel = nil,
    ---@type Label
    priceLabel = nil,
    ---@type ScrollablePanel
    parent = nil
}

---@Description create new instance of CharacterPanel
---@return CharacterPanel
function CharacterPanel:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

---@Description init CharacterPanel
---@param host pointer instance of TGUIScriptingManager
---@param parent pointer instance of ScrollablePanel, default nil (main)
---@param x number x position
---@param y number y position
---@param width number width
---@param height number height
---@param path string path to image
---@param name string name
---@param price string price
function CharacterPanel:init(host,parent,x,y,width,height,path,name,price)
    self.parent = parent
    print("Init called !!!!!!!! ")
    if self.panel == nil then
        self.panel = Panel:new()
        self.panel:init(host,x,y,width,height,parent)
    else
        self.panel:setPos(x,y)
        self.panel:setSize(width,height)
    end

    if self.picture == nil then
        self.picture = Picture:new()
        self.picture:init(host,path,x,y,width,height,self.panel)
        -- self.picture:setPosStr("50%","10%")
    else
        self.picture:setPos(x,y)
        self.picture:setSize(width,height)
        self.picture:setTexture(path)
    end

    if self.displayNameLabel == nil then
        self.displayNameLabel = Label:new()
        self.displayNameLabel:init(host,name,x,y,self.parent)
    else
        self.displayNameLabel:setPos(x,y)
        self.displayNameLabel:setText(name)
    end

    if self.priceLabel == nil then
        self.priceLabel = Label:new()
        self.priceLabel:init(host,price,x,y,self.parent)
    else
        self.priceLabel:setPos(x,y)
        self.priceLabel:setText(price)
    end
end