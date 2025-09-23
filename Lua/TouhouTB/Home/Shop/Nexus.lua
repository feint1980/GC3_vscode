package.path = package.path .. ';../../Lua/system/GUI/?/?.lua;' .. ';../../Lua/system/GUI/widgets/?.lua;' .. ';../../Lua/TouhouTB/Home/?.lua;'

require "TGUI_Label"
require "TGUI_Panel"
require "TGUI_RTLabel" 
require "TGUI_Editbox"
require "TGUI_Picture"
require "TGUI_TabContainer"
require "TGUI_ScrollablePanel"
require "homeGlobal"
require "NexusCharacter"


MenuPanels = _G.MenuPanels

---@type TabContainer
NexusMenu = nil

---@type Panel
NexusPanel = nil

---@type Nexu
NexusCharacterTab = nil


---@Description : Init the Roster menu
---@Param host TGUIScripting host
function InitNexus(host)
    if NexusPanel == nil then 
        NexusPanel = Panel:new()
        NexusPanel:init(host,TGUI_ScreenWidth/2 - 300,TGUI_ScreenHeight/2 - 200,600,400)
        NexusPanel:setSizeStr("80%", "80%")
        NexusPanel:setAlignment(0.5, 0.5)
        NexusPanel:setPosStr("50%", "50%")
        local nexusLabel = Label:new()
        nexusLabel:init(host,"Spirit Nexus",NexusPanel.width/2,0,NexusPanel.ptr)
        nexusLabel:setAlignment(TextAlginment.Center)
        nexusLabel:setPosStr("50%","1%")
        local closeLabel = Label:new()
        closeLabel:init(host,"X",NexusPanel.width - 20,0,NexusPanel.ptr)
        closeLabel:setPosStr("99%","1%")
        closeLabel:setAlignment(TextAlginment.Center)
        closeLabel:setHoverable(0,255,0,255,255,255,255,255)
        closeLabel:setOnClickCallback(function()
            NexusPanel:hideWithEffect(PanelShowType.Fade,250)
        end)
        if NexusMenu == nil then
            NexusMenu = TabContainer:new()
            -- Shop:init(host,"Dataaaa",0,0)
            NexusMenu:init(host,50,40,500,350,NexusPanel.ptr)
            NexusMenu:setAlignment(0.5,0.5)
            NexusMenu:setPosStr("50%","50%")
            NexusMenu:setSizeStr("94%","95%")
            NexusMenu:setTabFixedSize(140)
            NexusMenu:addTab("Characters",true)
            NexusMenu:addTab("Charms")
            NexusMenu:addTab("Items")
        end
        -- NexusPanel:setVisible(false)
    end
    NexusPanel:setVisible(false)

    NexusCharacterTab = CharacterNexus:new()
    NexusCharacterTab:init(host,NexusMenu.tabs["Characters"])

end

MenuPanels["Nexus"] = function(host)
    NexusCharacterTab:updateCharacters()
    NexusPanel:showWithEffect(PanelShowType.Fade,250)
end

function NexusRequestUserCharacterList(id,guid)
    SendRequest(PacketChannel.UserChannel, UserResponse.OwnedCharacter_Request, {id,guid, "request"}, 5, 0.5,0.25)
end