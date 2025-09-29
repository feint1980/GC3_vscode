package.path = package.path .. ';../../Lua/system/GUI/?/?.lua;' .. ';../../Lua/system/GUI/widgets/?.lua;' .. ';../../Lua/TouhouTB/Home/?.lua;'

require "TGUI_Label"
require "TGUI_Panel"
require "TGUI_RTLabel" 
require "TGUI_Editbox"
require "TGUI_Picture"
require "TGUI_TabContainer"
require "TGUI_ScrollablePanel"
require "homeGlobal"
require "Formation_Preview_Panel"
require "Prompt"
require "Formation_CharInfo"

---@class Formation_Slot
Formation_Slot = {
    ---@type pointer instance of Panel 
    parentPanel = nil,
    ---@type Panel
    mainPanel = nil,
    ---@type Picture
    picture = nil,
    isSelected = false
}

function Formation_Slot:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

---@Description create a new instance of Formation_Slot
---@param host pointer instance of TGUIScriptingManager 
---@param parentPanel pointer instance of Panel
---@param posX number
---@param posY number
---@param width number
---@param height number
---@param picturePath string path to the image file
function Formation_Slot:init(host, parentPanel, posX,
    posY, width, height,picturePath)

    self.parentPanel = parentPanel
    self.mainPanel = Panel:new()
    self.mainPanel:init(host,posX,posY,width,height,self.parentPanel)
    self.mainPanel:setAlignment(0.5,0.5)

    self.picture = Picture:new()
    self.picture:init(host, picturePath, posX, posY, width * 0.98,  height * 0.98  , self.mainPanel.ptr)
    self.picture:setPosStr("0%","0%")
    self.picture:setSizeStr("98%","98%")

    self.mainPanel:setHoverable(0,255,0,255,125,125,125,125)

    self.mainPanel:setOnClickCallback(function()

        _G.Formation_Edit_Instance:resetSelections()
        -- if self.isSelected == true then
        --     self.isSelected = false
        -- end

        self.isSelected = not self.isSelected
        self:setSelected(self.isSelected)
        Formation_MainUpdate(host)
    end)
end

---@Description set the selected state of the slot
---@param value boolean
function Formation_Slot:setSelected(value)
    if value == true then
        self.mainPanel:setHoverableStop()
        self.mainPanel:setBorderColor(255,255,0,255)
    else
        self.mainPanel:setHoverable(0,255,0,255,125,125,125,125)
        self.mainPanel:setBorderColor(125,125,125,125)
    end
end

function Formation_Slot:getIsSelected()
    return self.isSelected
end