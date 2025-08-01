package.path = package.path .. ';../../Lua/system/GUI/?/?.lua;' .. ';../../Lua/system/GUI/widgets/?.lua;' .. ';../../Lua/TouhouTB/Home/?.lua;'

require "TGUI_Label"
require "TGUI_Panel"
require "TGUI_RTLabel" 
require "TGUI_Editbox"
require "TGUI_Picture"
require "TGUI_TabContainer"
require "TGUI_ScrollablePanel"
require "homeGlobal"



---@class (exact) CharacterNexus
---@field parentPanel pointer instance of Panel
---@field mainPanel ScrollablePanel instance of ScrollablePanel
---@field ownedCharacterPanels table
---@field t_characters table
---@field itemCount number
CharacterNexus = {
    ---@type Panel 
    parentPanel = nil,
    ---@type ScrollablePanel
    mainPanel = nil,
    ---@type table of OwnedCharacterPanel
    ownedCharacterPanels = {},
    t_characters = {},
    itemCount = 0
}

function CharacterNexus:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function CharacterNexus:init( GUI_host,parent )
    self.parentPanel = parent
    self.mainPanel = ScrollablePanel:new()
    self.mainPanel:init(GUI_host,0,0,0,0,self.parentPanel.ptr)
    self.mainPanel:setAlignment(0.5,0.5)
    self.mainPanel:setPosStr("50%","50%")
    self.mainPanel:setSizeStr("99%","99%")

end

function CharacterNexus:addCharPanel(GUI_host,x,y,width,height)
    local panelHeight = 140
    local pWidth, pHeight = self.parentPanel:getSize()
    local onwedCharacter

end