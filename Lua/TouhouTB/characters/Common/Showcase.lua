package.path = package.path .. ';../../Lua/system/GUI/?/?.lua;' .. ';../../Lua/system/GUI/widgets/?.lua;' .. ';../../Lua/TouhouTB/Home/?.lua;'

require "TGUI_Label"
require "TGUI_Panel"
require "TGUI_RTLabel" 
require "TGUI_Editbox"
require "TGUI_Picture"
require "TGUI_TabContainer"
require "TGUI_ScrollablePanel"

Showcase = {
    ---@type pointer
    parentPanel = nil,
    ---@type Picture
    iconPicture = nil,
    ---@type RTLabel
    displayNameLabel = nil,
    ---@type RTLabel
    descriptionLabel = nil
}