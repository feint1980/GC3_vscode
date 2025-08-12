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

---@type Panel
FormationPanel = nil

---@type number
Formation_Page = 1

Formation_PageCap = 1

---@type Label
Formation_page_label = nil


function InitFormationMenu(host)
    if FormationPanel == nil then 
        FormationPanel = Panel:new() 
        FormationPanel:init(host,TGUI_ScreenWidth/2 - 300,TGUI_ScreenHeight/2 - 200,600,400)
        FormationPanel:setSizeStr("80%", "80%")
        FormationPanel:setAlignment(0.5, 0.5)
        FormationPanel:setPosStr("50%", "50%")
        local closeLabel = Label:new()
        closeLabel:init(host,"X",FormationPanel.width - 20,0,FormationPanel.ptr)
        closeLabel:setPosStr("99%","1%")
        closeLabel:setAlignment(TextAlginment.Center)
        closeLabel:setHoverable(0,255,0,255,255,255,255,255)
        closeLabel:setOnClickCallback(function()
            FormationPanel:hideWithEffect(PanelShowType.Fade,250)
        end)

        local nextPageButton = Label:new()
        nextPageButton:init(host,">>",FormationPanel.width/2,0,FormationPanel.ptr)
        nextPageButton:setAlignment(TextAlginment.Center)
        nextPageButton:setPosStr("94%","5%")
        nextPageButton:setHoverable(0,255,0,255,255,255,255,255)
        nextPageButton:setOnClickCallback(function()
            FormationUpdatePage(1)
        end)

        local prevPageButton = Label:new()
        prevPageButton:init(host,"<<",FormationPanel.width/2,0,FormationPanel.ptr)
        prevPageButton:setAlignment(TextAlginment.Center)
        prevPageButton:setPosStr("6%","5%")
        prevPageButton:setHoverable(0,255,0,255,255,255,255,255)
        prevPageButton:setOnClickCallback(function()
            FormationUpdatePage(-1)
        end)


    end
    if Formation_page_label == nil then
        Formation_page_label = Label:new()
        Formation_page_label:init(host,"",FormationPanel.width/2,0,FormationPanel.ptr)
        Formation_page_label:setAlignment(TextAlginment.Center)
        Formation_page_label:setPosStr("50%","1%")
        FormationUpdatePage(0)
    end

    FormationPanel:setVisible(false)
end

function FormationUpdatePage(value)
    Formation_Page = Formation_Page + value
    if(Formation_Page > Formation_PageCap) then
        Formation_Page = 1
    end
    if (Formation_Page < 1) then
        Formation_Page = Formation_PageCap
    end
    
    Formation_page_label:setText("Page " .. Formation_Page .. "/" .. Formation_PageCap)
end

function FormationSetPageCap(value)
    Formation_PageCap = value
end

MenuPanels["Formation"] = function(host)
    -- NexusCharacterTab:updateCharacters()
    FormationPanel:showWithEffect(PanelShowType.Fade,250)
end


