package.path = package.path .. ';../../Lua/system/GUI/?/?.lua;' .. ';../../Lua/system/GUI/widgets/?.lua;' .. ';../../Lua/TouhouTB/Home/?.lua;' .. ';../../Lua/system/event/?.lua;'

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
require "Prompt"
-- require "TaskManager"

MenuPanels = _G.MenuPanels

---@type Panel
CreateLobbyPanel = nil

---@type ComboBox
LobbyServerComboBox = nil


CreateLobbyServerList = {

}

---@type EditBox
LobbyNameInput = nil

---@type EditBox
LobbyPWInput = nil

Create_Lobby_State = 0

LobbyServer = {
    name = "",
    ping = 0,
    value = "",
    guid = "",
}

---@type LobbyServer
CL_SelectedServer = nil

function LobbyServer:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function InitCreateLobbyMenu(host)
    if CreateLobbyPanel == nil then
        CreateLobbyPanel = Panel:new()
        CreateLobbyPanel:init(host,TGUI_ScreenWidth/2 - 300,TGUI_ScreenHeight/2 - 200,400,300)
        CreateLobbyPanel:setSizeStr("60%", "50%")
        CreateLobbyPanel:setAlignment(0.5, 0.5)
        CreateLobbyPanel:setPosStr("50%", "50%")
    end

    local closeLabel = Label:new()
    closeLabel:init(host,"X",CreateLobbyPanel.width - 20,0,CreateLobbyPanel.ptr)
    closeLabel:setPosStr("99%","1%")
    closeLabel:setAlignment(TextAlginment.Center)
    closeLabel:setHoverable(0,255,0,255,255,255,255,255)
    closeLabel:setOnClickCallback(function()
        CreateLobbyPanel:hideWithEffect(PanelShowType.Fade,250)
    end)

    local tLobbyNameLabel = Label:new()
    tLobbyNameLabel:init(host,"Lobby Name",CreateLobbyPanel.width/2,0,CreateLobbyPanel.ptr)
    tLobbyNameLabel:setAlignment(TextAlginment.Left)
    tLobbyNameLabel:setPosStr("5%","10%")

    LobbyNameInput = EditBox:new()
    LobbyNameInput:init(host,1,1,1,1,CreateLobbyPanel.ptr)
    LobbyNameInput:setInputValidator("^[^$]*$")
    LobbyNameInput:setPosStr("20%","10%")
    LobbyNameInput:setSizeStr("30%","8%")
    LobbyNameInput:setText("test lobby")

    local tLobbyPWLabel = Label:new()
    tLobbyPWLabel:init(host,"Password",CreateLobbyPanel.width/2,0,CreateLobbyPanel.ptr)
    tLobbyPWLabel:setAlignment(TextAlginment.Left)
    tLobbyPWLabel:setPosStr("5%","20%")

    LobbyPWInput = EditBox:new()
    LobbyPWInput:init(host,1,1,1,1,CreateLobbyPanel.ptr)
    LobbyPWInput:setPWCharacter("*")
    LobbyPWInput:setInputValidator("^[^$]*$")
    LobbyPWInput:setPosStr("20%","20%")
    LobbyPWInput:setSizeStr("30%","8%")
    LobbyPWInput:setText("123456")

    local tServerListLabel = Label:new()
    tServerListLabel:init(host,"Server List",CreateLobbyPanel.width/2,0,CreateLobbyPanel.ptr)
    tServerListLabel:setAlignment(TextAlginment.Center)
    tServerListLabel:setPosStr("60%","10%")

    LobbyServerComboBox = ComboBox:new()
    LobbyServerComboBox:init(host,400,200,200,50,CreateLobbyPanel.ptr)

    LobbyServerComboBox:setPosStr("55%","20%")
    LobbyServerComboBox:setSizeStr("35%","10%")

    LobbyServerComboBox:setOnSelectCallback(function()
        local serverValue = LobbyServerComboBox:getSelectedItem()
        print("selected server " .. serverValue)
        CreateLobby_SetCurrentSelectedServer(serverValue)
        if CL_SelectedServer ~= nil then
            print("selected server " .. CL_SelectedServer.guid)
        end
    end)

    local tCreateLobbyButton = Label:new()
    tCreateLobbyButton:init(host,"Create Lobby",CreateLobbyPanel.width/2,0,CreateLobbyPanel.ptr)
    tCreateLobbyButton:setAlignment(TextAlginment.Center)
    tCreateLobbyButton:setPosStr("50%","80%")
    tCreateLobbyButton:setHoverable(0,255,0,255,255,255,255,255)
    tCreateLobbyButton:setOnClickCallback(function()
        CreateLobby_SendRequest()
    end)

    print("current seelection is " .. LobbyServerComboBox:getSelectedItemIndex())

    Prompt_UI_Table["CreateLobby_Noti"] = Prompt:new()
    Prompt_UI_Table["CreateLobby_Noti"]:init(host,"Notification",true)

    Prompt_UI_Table["CreateLobby_Status"] = Prompt:new()
    Prompt_UI_Table["CreateLobby_Status"]:init(host,"Status",true)

    CreateLobbyPanel:setVisible(false)

end

MenuPanels["CreateLobby"] = function(host)
    CreateLobbyPanel:showWithEffect(PanelShowType.Fade,250)
end

function CreateLobby_ClearServerList()
    LobbyServerComboBox:clearItems()
end

function CreateLobby_AddServerToList(serverGUID, serverName, ping)

    local serverValue =  serverName .. "  (" .. ping .. "ms)"
    if CreateLobbyServerList[serverGUID] == nil then
        CreateLobbyServerList[serverGUID] = LobbyServer:new({name = serverName, ping = ping, value = serverValue, guid = serverGUID})
    else
        CreateLobbyServerList[serverGUID].name = serverName
        CreateLobbyServerList[serverGUID].ping = ping
    end

    LobbyServerComboBox:addItem(serverValue)
end

function CreateLobby_SetCurrentSelectedServer(serverValue)
    CL_SelectedServer = nil -- reset
    for key, value in pairs(CreateLobbyServerList) do
        if value.value == serverValue then
            CL_SelectedServer = value
            break
        end
    end
end

function CreateLobby_SendRequest()
    if CL_SelectedServer == nil and LobbyServerComboBox:getSelectedItemIndex() == -1 then
        -- no selection was made, get the lowest ping server
        print("no server selected, getting lowest ping server")
        for key, value in pairs(CreateLobbyServerList) do
            if CL_SelectedServer == nil then
                CL_SelectedServer = value
            else
                if value.ping < CL_SelectedServer.ping then
                    CL_SelectedServer = value
                end
            end
        end

        if CL_SelectedServer == nil then

            print("no server avaiable")
            Prompt_UI_Table["CreateLobby_Noti"]:setMsg("No server avaiable !")
            Prompt_UI_Table["CreateLobby_Noti"]:show(true)
            return
        print("selected server " .. CL_SelectedServer.guid .. " ping " .. CL_SelectedServer.ping)
        end
    end

        if LobbyNameInput:getText() == "" then
            Prompt_UI_Table["CreateLobby_Noti"]:showMsg("Lobby name not set !")
            return
        end

        local tCombine = "{" .. LobbyNameInput:getText() .. "$" .. LobbyPWInput:getText() .. "}"

        print("param check ") 
        print(MainInfo.guid)
        print(MainInfo.id)
        print(CL_SelectedServer.guid)
        print(tCombine)

        SendRequest(PacketChannel.ArenaChannel, ArenaResponse.Arena_RequestLobby_Create, {MainInfo.guid, MainInfo.id,CL_SelectedServer.guid, tCombine }, 5, 0.5,0.25)

        Prompt_UI_Table["CreateLobby_Status"]:showMsg("Requesting ...")

        Create_Lobby_State = 1
        TM_addTask(
        function()
            if Create_Lobby_State == 1 then
                Prompt_UI_Table["CreateLobby_Status"]:show(false)
                Prompt_UI_Table["CreateLobby_Noti"]:showMsg("Request timeout !")
                Create_Lobby_State = 0
            end
        end,
        500
        )
end

