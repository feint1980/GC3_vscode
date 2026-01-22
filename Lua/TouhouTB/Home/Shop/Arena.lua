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

Join_State = 0

Arena_selected_serverGUID = ""
Arena_selected_lobbyID = ""
Arena_joinLobbyPW = ""


BattleLobbyState = {
    CLOSED = 0,
    OPEN = 1,
    INGAME = 2,
    EXPIRED = 3,
    FULL = 4,
}

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
    RoomListView:init(host,50,50,600,400,{"Room","Opponent","PW", "Status", "Ping"},{100,200,100,150,100},ArenaPanel.ptr)
    RoomListView:setPosStr("0%","5%")
    RoomListView:setSizeStr("50%","45%")
    RoomListView:setColumnSizeRatios({0.26,0.26,0.12,0.2 ,0.16})

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

    local refreshLabel = Label:new()
    refreshLabel:init(host,"Refresh",ArenaPanel.width/2,0,ArenaPanel.ptr)
    refreshLabel:setScale(0.9)
    refreshLabel:setAlignment(TextAlginment.Center)
    refreshLabel:setPosStr("15%","50%")
    refreshLabel:setHoverable(0,255,0,255,255,255,255,255)
    refreshLabel:setOnClickCallback(function()
        print("refresh")
        Arena_RequestLobbyList()
    end)

    -- local rComboBox = ComboBox:new()
    -- rComboBox:init(host,400,200,200,50,ArenaPanel.ptr)

    -- rComboBox:setPosStr("70%","50%")
    -- rComboBox:setSizeStr("30%","5%")
    ArenaPanel:setVisible(false)

    RoomListView:setDoubleClickCallBack(
    function()
        print("press RoomListView:setDoubleClickCallBack")
        Arena_JoinLobby_Click()
    end
    )

    Prompt_UI_Table["Arena_Status"] = Prompt:new()
    Prompt_UI_Table["Arena_Status"]:init(host,"Arena_Status",false)

    MenuMainPanels["Arena"] = ArenaPanel

    Prompt_UI_Table["Arena_Join_no_pw"] = Prompt:new()
    Prompt_UI_Table["Arena_Join_no_pw"]:init(host,"Join this lobby ?",false)
    Prompt_UI_Table["Arena_Join_no_pw"]:addButton("Join", function()
        Arena_JoinLobby(false)
        Prompt_UI_Table["Arena_Join_no_pw"]:show(false)
    end
    )
    Prompt_UI_Table["Arena_Join_no_pw"]:addButton("Back", function()
        print("back")
        Prompt_UI_Table["Arena_Join_no_pw"]:show(false)
    end
    )


    Prompt_UI_Table["Arena_Join_with_pw"] = Prompt:new()
    Prompt_UI_Table["Arena_Join_with_pw"]:init(host,"This Lobby requires password",false)
    Prompt_UI_Table["Arena_Join_with_pw"]:addButton("Join", function()
        Arena_JoinLobby(true)
        Prompt_UI_Table["Arena_Join_with_pw"]:show(false)
    end
    )
    Prompt_UI_Table["Arena_Join_with_pw"]:addButton("Back", function()
        print("back")
        Prompt_UI_Table["Arena_Join_with_pw"]:show(false)
    end
    )
    Prompt_UI_Table["Arena_Join_with_pw"]:addInputBox("Password",100,100,300,40)

    Prompt_UI_Table["Arena_Noti"] = Prompt:new()
    Prompt_UI_Table["Arena_Noti"]:init(host,"Arena_Noti",true)

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

function Arena_JoinLobby_Click()

    print("Join Lobby called")
    local index = RoomListView:getSelectedItemIndex()
    if index == -1 then
        print("no room selected")
        return
    end
    print("index is " .. index)

    local tData = RoomListView:getItemDataStr(index)
    -- split between the character "serverGUID_lobbyID"
    local serverGUID, lobbyID = string.match(tData, "^([^_]+)_([^_]+)$")
    print("serverGUID is " .. serverGUID)
    print("lobbyID is " .. lobbyID)

    print("Check Arena Ping List data")
    for k,v in pairs(Arena_Ping_List) do
        print("key is " .. k)
        print(v.name)
        print(v.guid)
        print(v.port)
        print("room list ")
        for n,m in pairs(v.lobbyList) do
            print(m.name)
        end
    end

    if Arena_Ping_List[serverGUID] == nil then
        Prompt_UI_Table["Arena_Noti"]:setMsg("Server not found")
        return
    end

    Arena_selected_serverGUID = serverGUID
    Arena_selected_lobbyID = lobbyID
    if Arena_Ping_List[serverGUID].lobbyList[lobbyID] == nil then
        Prompt_UI_Table["Arena_Noti"]:setMsg("Lobby not found")
        return
    end

    if Arena_Ping_List[serverGUID].lobbyList[lobbyID].password ~= "" then
        Prompt_UI_Table["Arena_Join_with_pw"]:show(true)
        return
    else
        Prompt_UI_Table["Arena_Join_no_pw"]:show(true)
        return
    end

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

    if Arena_Ping_List[serverGUID] == nil then
        return
    end
    local serverName = Arena_Ping_List[serverGUID].name
    Arena_Ping_List[serverGUID].ping = ping
    BattleServerListView:addItem({serverName,ping})

    CreateLobby_AddServerToList(serverGUID, serverName, ping)

end

function Arena_JoinLobby(hasPassword)
    local tPassword = ""
    if hasPassword == true then
        tPassword = Prompt_UI_Table["Arena_Join_with_pw"]:getInputBox("Password"):getText()
    end
    print("join server with data" )
    print("server GUID " .. Arena_selected_serverGUID)
    print("lobby ID " .. Arena_selected_lobbyID)
    print("password " .. tPassword)
    Arena_Send_Join_Lobby_Request(Arena_selected_serverGUID, Arena_selected_lobbyID, tPassword)

    Prompt_UI_Table["Arena_Status"]:showMsg("Joining Lobby ...")
    Join_State = 1
    TM_addTask(
function()
            if Join_State == 1 then
                Prompt_UI_Table["Arena_Status"]:show(false)
                Prompt_UI_Table["Arena_Noti"]:showMsg("Join timeout !")
                Join_State = 0
            end
        end,
        500
    )
end

function Arena_Send_Join_Lobby_Request(serverGUID, lobbyID,password)

    local comineData = "{" .. lobbyID .. "$" .. password .. "}"
    SendRequest(PacketChannel.ArenaChannel, ArenaResponse.Arena_RequestJoinLobby_WithBSGUID_LobbyID, {serverGUID, MainInfo.guid, MainInfo.id, comineData}, 5, 0.5,0.25)

end

---@param serverList table
function Arena_UpdateLobbies(serverList)
    RoomListView:clearItems()
    for k ,v in pairs(serverList) do
        if Arena_Ping_List[k] == nil then
            print("mismatch battle server ID found" .. k)
            break
        end
        print ("Arena_UpdateLobbies " .. k)
        for n,m in pairs(v.lobbyList) do
            local hasPassword = "x"
            if m.password ~= "" then
                hasPassword = "v"
            end
            local state = "TK2"
            if m.lobbyState == 0 then
                state= "Waiting"
            elseif m.lobbyState == 2 then
                state = "In Game"
            end
            if #m.battleClientEP_List > 0 then 
                RoomListView:addItemWithDataStr({m.name, m.battleClientEP_List[1].id, 
                hasPassword, state ,Arena_Ping_List[k].ping}, k .. "_" .. m.id)
            end
        end
        -- RoomListView:addItem({arenaList[k].name,arenaList[k].name,arenaList[k].name,arenaList[k].name})
        -- for n,m in pairs(Arena_Ping_List[k].lobbyList) do
            
        --     print("found lobby list for battle server " .. k .. "|" .. n)
        --     -- local hasPassword = "x"
        --     -- if m.password == "" then
        --     --     hasPassword = "v"
        --     -- end
        --     -- RoomListView:addItem({m.name,m.battleClientEP_List[1].id,hasPassword,v.ping})
        -- end
    end

end

