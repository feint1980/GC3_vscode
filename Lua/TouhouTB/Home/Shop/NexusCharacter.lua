package.path = package.path .. ';../../Lua/system/GUI/?/?.lua;' .. ';../../Lua/system/GUI/widgets/?.lua;' .. ';../../Lua/TouhouTB/Home/?.lua;'

require "TGUI_Label"
require "TGUI_Panel"
require "TGUI_RTLabel" 
require "TGUI_Editbox"
require "TGUI_Picture"
require "TGUI_TabContainer"
require "TGUI_ScrollablePanel"
require "homeGlobal"

CharacterNexus = {
    ---@pointer 
    mainPanel = nil,
    ---@type ScrollablePanel
    charactersPanel = nil,
    ---@type CharacterDetailPanel
    characterDetailPanel = nil,
    ---@type Panel
    characterPanels = {},

    t_characters = {}
}

function CharacterNexus:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function CharacterNexus:addCharPanel(GUI_host,x,y,width,height)

end