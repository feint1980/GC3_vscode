package.path = package.path .. ';../../Lua/system/GUI/?/?.lua;' .. ';../../Lua/system/GUI/widgets/?.lua;' .. ';../../Lua/TouhouTB/Home/?.lua;'

require "TGUI_Label"
require "TGUI_Panel"
require "TGUI_RTLabel" 
require "TGUI_Editbox"
require "TGUI_Picture"
require "TGUI_TabContainer"
require "TGUI_ScrollablePanel"
require "TGUI_ListView"
require "TGUI_ComboBox"
require "homeGlobal"
require "CreateLobbyMenu"

MenuPanels = _G.MenuPanels

ArenaPanel = nil


--- @type ListView
BattleServerListView = nil

---@type ListView
RoomListView = nil

function InitArenaMenu(host)
    InitCreateLobbyMenu(host)
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
    refreshLabel:setPosStr("80%","37%")
    refreshLabel:setHoverable(0,255,0,255,255,255,255,255)
    refreshLabel:setOnClickCallback(function()
        print("refresh")
        Arena_RequestBattleServerList()
    end)


    BattleServerListView:setDoubleClickCallBack( function ()
        local target = BattleServerListView:getSelectItemValue(0)
        print("target is " .. target)
        for k ,v in pairs(Arena_Ping_List) do
            if(v.name == target)then
                print("connect to " .. v.name .. " " .. v.guid .. " " .. v.port)
                --ClientConnectToBattleServer(v.clientHost, v.guid) -- just a test connect
            end
        end
    end)

    RoomListView = ListView:new()
    RoomListView:init(host,50,50,500,400,{"Room","Opponent", "PW", "Ping"},{100,200,100,100},ArenaPanel.ptr)
    RoomListView:setPosStr("0%","5%")
    RoomListView:setSizeStr("40%","45%")
    RoomListView:setColumnSizeRatios({0.37,0.37,0.13,0.13})


    --- Create Room Button
    local createRoomLabel = Label:new()
    createRoomLabel:init(host,"Create Room",ArenaPanel.width/2,0,ArenaPanel.ptr)
    createRoomLabel:setScale(0.9)
    createRoomLabel:setAlignment(TextAlginment.Center)
    createRoomLabel:setPosStr("5%","50%")
    createRoomLabel:setHoverable(0,255,0,255,255,255,255,255)
    createRoomLabel:setOnClickCallback(function()
        MenuPanels["CreateLobby"](host)
    end)

    -- local rComboBox = ComboBox:new()
    -- rComboBox:init(host,400,200,200,50,ArenaPanel.ptr)

    -- rComboBox:setPosStr("70%","50%")
    -- rComboBox:setSizeStr("30%","5%")

    ArenaPanel:setVisible(false)

   
end

MenuPanels["Arena"] = function(host)
    ArenaPanel:showWithEffect(PanelShowType.Fade,250)
    Arena_RequestBattleServerList()
    Arena_RequestLobbyList()
end

function Arena_RequestBattleServerList()
    print("Arena_RequestBattleServerList called")
    SendRequest(PacketChannel.ArenaChannel, ArenaResponse.Arena_Request_GetServerList, {MainInfo.guid, "request"}, 5, 0.5,0.25)
    print("Arena_RequestBattleServerList sent ")
end

function Arena_RequestLobbyList()
    SendRequest(PacketChannel.ArenaChannel, ArenaResponse.Arena_RequestLobbyList, {MainInfo.guid, "request"}, 5, 0.5,0.25)
end

function Arena_ResetList()
    BattleServerListView:clearItems()
    print("Arena reset called ")
    CreateLobby_ClearServerList()
end

function Arena_UpdateServerPing(serverGUID, ping)

    local serverName = Arena_Ping_List[serverGUID].name

    Arena_Ping_List[serverGUID].ping = ping
    BattleServerListView:addItem({serverName,ping})

    CreateLobby_AddServerToList(serverGUID, serverName, ping)
end


function Arena_ServerList_DoubleClick()

end