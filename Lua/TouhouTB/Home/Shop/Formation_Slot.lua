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
    isSelected = false,
    isAssigned = false,
    assignedCharacterID = "x",
    picturePath = "",
    defaultPath = "./Assets/TB_GUI/slide/plus.png",
    row = 0,
    col = 0
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
---@param r number row
---@param c number collum
function Formation_Slot:init(host, parentPanel, posX,
    posY, width, height,picturePath,r,c)

    self.parentPanel = parentPanel
    self.mainPanel = Panel:new()
    self.mainPanel:init(host,posX,posY,width,height,self.parentPanel)
    self.mainPanel:setAlignment(0.5,0.5)

    self.picture = Picture:new()
    self.picturePath = picturePath
    self.picture:init(host, picturePath, posX, posY, width * 0.98,  height * 0.98  , self.mainPanel.ptr)
    self.picture:setPosStr("0%","0%")
    self.picture:setSizeStr("98%","98%")

    self.mainPanel:setHoverable(0,255,0,255,125,125,125,125)

    self.row = r
    self.col = c

    self.mainPanel:setOnClickCallback(function()

        local t = not self.isSelected
        _G.Formation_Edit_Instance:resetSelections()
        -- if self.isSelected == true then
        --     self.isSelected = false
        -- end

        self:setSelected(t)
        Formation_MainUpdate(host)
    end)

    self.mainPanel:setOnRightClickCallback(function()
        if self.isAssigned == true then
            self:removeAssignment()
        end
    end)

end

---@Description set the selected state of the slot
---@param value boolean
function Formation_Slot:setSelected(value)
    self.isSelected = value
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

function Formation_Slot:setCharacterID(id)
    self.assignedCharacterID = id
    local tPath = Owned_CharacterTable[self.assignedCharacterID].portraitPath
    -- print("set " .. tPath)
    self.picturePath = tPath
    self.picture:setTexture(tPath)
    self.isAssigned = true
end

function Formation_Slot:getIsAssigned()
    return self.isAssigned
end

function Formation_Slot:removeAssignment()
    self.picture:setTexture(self.defaultPath)
    self.isAssigned = false
end
