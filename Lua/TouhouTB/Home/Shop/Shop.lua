package.path = package.path .. ';../../Lua/system/GUI/?/?.lua;' .. ';../../Lua/system/GUI/widgets/?.lua;' .. ';../../Lua/TouhouTB/Home/?.lua;'

require "TGUI_Label"
require "TGUI_Panel"
require "TGUI_RTLabel" 
require "TGUI_Editbox"
require "TGUI_Picture"
require "TGUI_TabContainer"
require "homeGlobal"

MenuPanels = _G.MenuPanels

---@type TabContainer
Shop = nil
ShopPanel = nil
MenuPanels["Shop"] = function (host)

    if ShopPanel == nil then
        ShopPanel = Panel:new()
        ShopPanel:init(host,TGUI_ScreenWidth/2 - 300,TGUI_ScreenHeight/2 - 200,600,400)
        local shopLabel = Label:new()
        shopLabel:init(host,"Shop",ShopPanel.width/2,0,ShopPanel.ptr)
        shopLabel:setAlignment(TextAlginment.Center)
        local closeLabel = Label:new()
        closeLabel:init(host,"X",ShopPanel.width - 20,0,ShopPanel.ptr)
        closeLabel:setAlignment(TextAlginment.Center)
        closeLabel:setHoverable(0,255,0,255,255,255,255,255)
        closeLabel:setOnClickCallback(function()
            ShopPanel:hideWithEffect(PanelShowType.Fade,250)
        end)
        if Shop == nil then
            Shop = TabContainer:new()
            -- Shop:init(host,"Dataaaa",0,0)
            Shop:init(host,50,40,500,350,ShopPanel.ptr)
            print("Init done")
            Shop:addTab("Tab1",true)
            local tab1_ee = Label:new()
            tab1_ee:init(host,"ddde",0,0,Shop.tabs["Tab1"])
            Shop:addTab("Tab2")
        end
        ShopPanel:setVisible(false)
        -- ShopPanel:hideWithEffect(PanelShowType.Fade,250)
    end

    ShopPanel:showWithEffect(PanelShowType.Fade,250)
end

