package.path = package.path .. ';../../Lua/system/GUI/?/?.lua;' .. ';../../Lua/system/GUI/widgets/?.lua;' .. ';../../Lua/TouhouTB/Home/?.lua;'

require "TGUI_Label"
require "TGUI_Panel"
require "TGUI_RTLabel" 
require "TGUI_Editbox"
require "TGUI_Picture"
require "TGUI_TabContainer"
require "TGUI_ScrollablePanel"
require "homeGlobal"


MenuPanels = _G.MenuPanels

ArenaPanel = nil


function InitArenaMenu(host)
    if ArenaPanel == nil then
        ArenaPanel = Panel:new()
        ArenaPanel:init(host,TGUI_ScreenWidth/2 - 300,TGUI_ScreenHeight/2 - 200,600,400)
        ArenaPanel:setSizeStr("80%", "80%")
        ArenaPanel:setAlignment(0.5, 0.5)
        ArenaPanel:setPosStr("50%", "50%")
    end
    local closeLabel = Label:new()
        closeLabel:init(host,"X",ArenaPanel.width - 20,0,ArenaPanel.ptr)
        closeLabel:setPosStr("99%","1%")
        closeLabel:setAlignment(TextAlginment.Center)
        closeLabel:setHoverable(0,255,0,255,255,255,255,255)
        closeLabel:setOnClickCallback(function()
            ArenaPanel:hideWithEffect(PanelShowType.Fade,250)
        end)

    ArenaPanel:setVisible(false)
end


MenuPanels["Arena"] = function(host)

    ArenaPanel:showWithEffect(PanelShowType.Fade,250)
end
