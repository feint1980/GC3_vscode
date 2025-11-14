package.path = package.path .. ';../../Lua/system/GUI/?/?.lua;' .. ';../../Lua/system/GUI/widgets/?.lua;' .. ';../../Lua/TouhouTB/Home/?.lua;'

require "TGUI_Label"
require "TGUI_Panel"
require "TGUI_RTLabel" 
require "TGUI_Editbox"
require "TGUI_Picture"
require "TGUI_TabContainer"
require "TGUI_ScrollablePanel"
require "TGUI_ListView"
require "homeGlobal"

MenuPanels = _G.MenuPanels

ArenaPanel = nil

BattleServerListView = nil

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

    BattleServerListView = ListView:new()
    BattleServerListView:init(host,50,50,400,400,{"Server","Ping"} ,{300,100},ArenaPanel.ptr)

    BattleServerListView:setPosStr("65%","5%")
    BattleServerListView:setSizeStr("30%","30%")
    BattleServerListView:setColumnSizeRatios({0.75,0.25})

    local refreshLabel = Label:new()
    refreshLabel:init(host,"Refresh",ArenaPanel.width/2,0,ArenaPanel.ptr)
    refreshLabel:setScale(0.9)
    refreshLabel:setAlignment(TextAlginment.Center)
    refreshLabel:setPosStr("75%","57%")
    refreshLabel:setHoverable(0,255,0,255,255,255,255,255)
    refreshLabel:setOnClickCallback(function()
        Arena_RequestBattleServerList()
    end)


    ArenaPanel:setVisible(false)
end

MenuPanels["Arena"] = function(host)
    ArenaPanel:showWithEffect(PanelShowType.Fade,250)
    Arena_RequestBattleServerList()
end

function Arena_RequestBattleServerList()
    SendRequest(PacketChannel.ArenaChannel, ArenaResponse.Arena_Request_GetServerList, {MainInfo.guid, "request"}, 5, 0.5,0.25)
end

function Arena_ResetList()
    BattleServerListView:clearItems()
end

function Arena_AddServer(serverName, ping)
    BattleServerListView:addItem({serverName,ping})
end

function Arena_UpdateList()
    -- Arena_ResetList()
    
end