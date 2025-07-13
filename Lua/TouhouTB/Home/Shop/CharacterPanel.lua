package.path = package.path .. ';../../Lua/system/GUI/?/?.lua;' .. ';../../Lua/system/GUI/widgets/?.lua;' .. ';../../Lua/TouhouTB/Home/?.lua;'

require "TGUI_Label"
require "TGUI_Panel"
require "TGUI_RTLabel" 
require "TGUI_Editbox"
require "TGUI_Picture"
require "TGUI_TabContainer"
require "TGUI_ScrollablePanel"
require "TGUI_Button"

---@class (exact) CharacterPanel
---@field panel Panel
---@field picture Picture
---@field displayNameLabel Label
---@field priceLabel RTLabel
---@field buyButton Button
---@field parent ScrollablePanel
---@field detailPanel ScrollablePanel
CharacterPanel = {
    ---@type Panel
    panel = nil,
    ---@type Picture
    picture = nil,
    ---@type Label
    displayNameLabel = nil,
    ---@type RTLabel
    priceLabel = nil,
    ---@type Button
    buyButton = nil,
    ---@type ScrollablePanel
    parent = nil,
    ---@type ScrollablePanel
    detailPanel = nil
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
---@param detailPanel pointer instance of ScrollablePanel
function CharacterPanel:init(host,parent,x,y,
width,height,path,name,price,detailPanel)
    self.parent = parent
    -- print("Init called !!!!!!!! ")
    if self.panel == nil then
        self.panel = Panel:new()
        self.panel:init(host,x,y,width,height,parent)
        self.panel:setBorderColor(125,125,125,255)
        self.panel:setHoverable(0,255,0,255,125,125,125,255)
    else
        self.panel:setPos(x,y)
        self.panel:setSize(width,height)
    end

    if self.picture == nil then
        self.picture = Picture:new()
        self.picture:init(host,path,x,y,width,height,self.panel.ptr)
        self.picture:setPosStr("5%","10%")
        self.picture:setSizeStr("85%","76%")
    else
        -- self.picture:setPos(x,y)
        -- self.picture:setSize(width,height)
        self.picture:setTexture(path)
    end

    if self.displayNameLabel == nil then
        self.displayNameLabel = Label:new()
        self.displayNameLabel:init(host,name,x,y,self.panel.ptr)
        self.displayNameLabel:setAlignment(TextAlginment.Center)
        self.displayNameLabel:setPosStr("50%","-1%")
        self.displayNameLabel:setScale(0.92)
    else
        -- self.displayNameLabel:setPos(x,y)
        self.displayNameLabel:setPosStr("50%","-1%")
        self.displayNameLabel:setText(name)
    end

    if self.priceLabel == nil then
        self.priceLabel = RTLabel:new()
        self.priceLabel:init(host,Tag.color_TB_title .. price .. " " ..Tag.icon_soul .. Tag.color_close,x,y,self.panel.ptr)
        self.priceLabel:setScale(0.8)
        self.priceLabel:setAlignment(TextAlginment.Center)
        self.priceLabel:setPosStr("50%","90%")
    else
        -- self.priceLabel:setPos(x,y)
        self.priceLabel:setPosStr("50%","90%")
        self.priceLabel:setText(Tag.color_TB_title .. price .. Tag.color_close)
    end

    if detailPanel ~= nil then
        
    end

    -- self.panel:setHoverOnCallBack(function()
    --     print("data ")
    -- end)
end