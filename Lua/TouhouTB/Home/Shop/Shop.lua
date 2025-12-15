package.path = package.path .. ';../../Lua/system/GUI/?/?.lua;' .. ';../../Lua/system/GUI/widgets/?.lua;' .. ';../../Lua/TouhouTB/Home/?.lua;'

require "TGUI_Label"
require "TGUI_Panel"
require "TGUI_RTLabel" 
require "TGUI_Editbox"
require "TGUI_Picture"
require "TGUI_TabContainer"
require "TGUI_ScrollablePanel"
require "homeGlobal"
require "CharacterPanel"
require "CharacterShop"

Tag.icon_soul = "<img=\"./Assets/TB_GUI/icons/soul.png\">"


MenuPanels = _G.MenuPanels

---@type TabContainer
Shop = nil
ShopPanel = nil

Shop_CharacterShop = nil

---@Description : Init the Shop menu
---@Param host TGUIScripting host
function InitShop(host)
    if ShopPanel == nil then
        ShopPanel = Panel:new()
        ShopPanel:init(host,TGUI_ScreenWidth/2 - 300,TGUI_ScreenHeight/2 - 200,600,400)
        ShopPanel:setSizeStr("80%", "80%")
        ShopPanel:setAlignment(0.5, 0.5)
        ShopPanel:setPosStr("50%", "50%")
        local shopLabel = Label:new()
        shopLabel:init(host,"Shop",ShopPanel.width/2,0,ShopPanel.ptr)
        shopLabel:setAlignment(TextAlginment.Center)
        shopLabel:setPosStr("50%","1%")
        local closeLabel = Label:new()
        closeLabel:init(host,"X",ShopPanel.width - 20,0,ShopPanel.ptr)
        closeLabel:setPosStr("99%","1%")
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
            Shop:setAlignment(0.5,0.5)
        Shop:setPosStr("50%","50%")
            Shop:setSizeStr("94%","95%")
            Shop:setTabFixedSize(140)
            Shop:addTab("Characters",true)
            Shop:addTab("Tab2")
        end
        if Shop_CharacterShop == nil then
            Shop_CharacterShop = CharacterShop:new()
            Shop_CharacterShop:init(host,0,0,Shop.width,Shop.height,Shop.tabs["Characters"])
        end
        ShopPanel:setVisible(false)
        
        MenuMainPanels["Shop"] = ShopPanel
    end
end

MenuPanels["Shop"] = function (host)
    ShopPanel:showWithEffect(PanelShowType.Fade,250)
end
