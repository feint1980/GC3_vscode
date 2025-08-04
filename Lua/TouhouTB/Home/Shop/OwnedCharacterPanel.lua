package.path = package.path .. ';../../Lua/system/GUI/?/?.lua;' .. ';../../Lua/system/GUI/widgets/?.lua;' .. ';../../Lua/TouhouTB/Home/?.lua;'

require "TGUI_Label"
require "TGUI_Panel"
require "TGUI_RTLabel" 
require "TGUI_Editbox"
require "TGUI_Picture"
require "TGUI_TabContainer"
require "TGUI_ScrollablePanel"
require "homeGlobal"

OwnedCharacterPanel = {
    ---@type ScrollablePanel
    parent = nil,
    ---@type Panel
    mainPanel = nil,
    ---@type Picture
    picture = nil,
    ---@type RTLabel
    displayNameLabel = nil,
    ---@type RTLabel 
    lvlLabel = nil,
    ---@type RTLabel
    expLabel = nil,

    characterID = nil
}

function OwnedCharacterPanel:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function OwnedCharacterPanel:init(GUI_host, parent, posX, posY, width, height, tCharacterID)
    self.parent = parent
    self.characterID = tCharacterID
    self.mainPanel = Panel:new()
    self.mainPanel:init(GUI_host,posX,posY,width,height,self.parent.ptr)

    self.picture = Picture:new()
    self.picture:init(GUI_host,Owned_CharacterTable[self.characterID].portraitPath,posX,posY,width,height,self.mainPanel.ptr)
    self.picture:setPosStr("0%","0%")
    local t_height = height - 2
    self.picture:setSize(t_height,t_height)
    self.displayNameLabel = RTLabel:new()
    self.displayNameLabel:init(GUI_host,Tag.color_TB_title .. Owned_CharacterTable[self.characterID].lastName .. " " .. Owned_CharacterTable[self.characterID].name .. Tag.color_close,posX,posY,self.mainPanel.ptr)
    self.displayNameLabel:setPosStr("14%","35%")
    self.displayNameLabel:setAlignment(TextAlginment.Left)
    self.displayNameLabel:setScale(1.1)

    self.lvlLabel = RTLabel:new()
    self.lvlLabel:init(GUI_host, "Level :" .. Tag.color_red.. Owned_CharacterTable[self.characterID].level .. Tag.color_close,posX,posY,self.mainPanel.ptr)
    self.lvlLabel:setPosStr("99%","15%")
    self.lvlLabel:setAlignment(TextAlginment.Right)
    self.lvlLabel:setScale(0.9)

    self.expLabel = RTLabel:new()
    local xpCap = Owned_CharacterTable[self.characterID].level * 125
    self.expLabel:init(GUI_host, "EXP :" .. Tag.color_blue .. Owned_CharacterTable[self.characterID].xp .. Tag.color_close .. "/"  .. tostring(xpCap),posX,posY,self.mainPanel.ptr)
    self.expLabel:setPosStr("99%","55%")
    self.expLabel:setAlignment(TextAlginment.Right)
    self.expLabel:setScale(0.9)
    return self


end