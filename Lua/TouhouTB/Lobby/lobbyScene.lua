package.path = package.path .. ';../../Lua/system/GUI/?/?.lua;' .. ';../../Lua/system/GUI/widgets/?.lua;' .. ';../../Lua/system/Networking/?.lua;' .. ';../../Lua/TouhouTB/Lobby/?.lua;' .. ';../../Lua/system/event/?.lua;' .. ';../../Lua/TouhouTB/characters/?.lua;' .. ';../../Lua/?.lua;' .. './TouhouTB/characters/Common/?.lua;' .. './TouhouTB/characters/Patchy/?.lua;' .. ';../../Lua/TouhouTB/characters/Patchy/?.lua;' .. ';./TouhouTB/characters/Reimu/slots/?.lua;' .. ';../../Lua/TouhouTB/characters/Reimu/?.lua;' .. ';./TouhouTB/characters/Yukari/slots/?.lua;' .. ';../../Lua/TouhouTB/characters/Yukari/?.lua;' .. ';../../Lua/TouhouTB/?.lua' .. ';../../Lua/TouhouTB/characters/Meiling/?.lua;' .. ';../../Lua/TouhouTB/?.lua' 

require "TGUI_Label"
require "TGUI_Panel"
require "TGUI_RTLabel" 
require "TGUI_Editbox"
require "TGUI_Picture"

require "clientSide"
require "clientWrapper"
require "clientGlobal"
require "lobby_global"

require "lobbyFormationSelector"
require "Prompt"


LobbySceneHost = nil

---@type pointer TGUIScriptingPtr
Lobby_GUIScriptingPtr = nil

---@type pointer ClientScriptingPtr
Lobby_ClientScriptingPtr = nil

---@type pointer ClientCharacterHandler
Lobby_ClientCharacterHandlerPtr = nil

---@type pointer ControlHandlerPtr
Lobby_ControlHandlerPtr = nil

--@type pointer SkillHandler
Lobby_SkillHandlerPtr = nil

---@type RTLabel
LobbyTitleLabel = nil

---@type RTLabel
LobbyAccountID = nil

---@type RTLabel
LobbyIDLabel = nil

---@type Picture
Lobby_Picture = nil

---@type RTLabel
Lobby_ReadyLabel = nil

---@type RTLabel
LobbyOpponentID = nil

---@type Picture
Lobby_OpponentPicture = nil

---@type RTLabel
Lobby_OpponentReadyLabel = nil

---@type Label
Lobby_ReadyButton = nil

Lobby_Leave_Decision = false

Formation_Selector = nil

function LobbySceneInit(host,TGUIScriptingPtr,ClientScriptingPtr,ClientCharacterHandlerPtr, SkillHandlerPtr, ControlHandlerPtr)

    print("LobbySceneInit called")
    LobbySceneHost = host
    Lobby_GUIScriptingPtr = TGUIScriptingPtr
    Lobby_ClientScriptingPtr = ClientScriptingPtr
    Lobby_ClientCharacterHandlerPtr = ClientCharacterHandlerPtr
    Lobby_SkillHandlerPtr = SkillHandlerPtr
    Lobby_ControlHandlerPtr = ControlHandlerPtr

    LobbyIDLabel = Label:new()
    LobbyIDLabel:init(Lobby_GUIScriptingPtr,"",0,0)
    LobbyIDLabel:setText("ID : " .. InfoHolder_getStrVal("Target_Lobby_ID"))
    LobbyIDLabel:setPosStr("10%", "10%")
    LobbyIDLabel:setScale(.8)

    LobbyTitleLabel = Label:new()
    LobbyTitleLabel:init(Lobby_GUIScriptingPtr,"",0,0)
    LobbyTitleLabel:setText(InfoHolder_getStrVal("LobbyName"))
    LobbyTitleLabel:setPosStr("50%", "15%")

    local id,pw,guid = cpp_lobby_getInfo(3)

    print("id " .. id)
    print("pw " .. pw)
    print("guid " .. guid)

    LobbyAccountID = RTLabel:new()
    LobbyAccountID:init(Lobby_GUIScriptingPtr,"",0,0)
    LobbyAccountID:setText(id)
    -- LobbyAccountID:setColor(45,209,255,255)
    LobbyAccountID:setPosStr("25%", "24%")
    LobbyAccountID:setScale(.8)

    LobbyOpponentID = RTLabel:new()
    LobbyOpponentID:init(Lobby_GUIScriptingPtr,"",0,0)
    LobbyOpponentID:setText("")
    -- LobbyOpponentID:setColor(255,81,100,255)
    LobbyOpponentID:setPosStr("75%", "24%")
    LobbyOpponentID:setScale(.9)

    Lobby_Picture = Picture:new()
    Lobby_Picture:init(Lobby_GUIScriptingPtr,"Assets/TB_GUI/faces/Reimu_face.png",0,0,100,100)
    Lobby_Picture:setPosStr("20%","24%")
    Lobby_Picture:setSize(75,75)

    Lobby_OpponentPicture = Picture:new()
    Lobby_OpponentPicture:init(Lobby_GUIScriptingPtr,"Assets/TB_GUI/faces/nothing.png",0,0,100,100)
    Lobby_OpponentPicture:setPosStr("70%","24%")
    Lobby_OpponentPicture:setSize(75,75)

    Lobby_ReadyButton = RTLabel:new()
    Lobby_ReadyButton:init(Lobby_GUIScriptingPtr,"Ready",0,0)
    Lobby_ReadyButton:setAlignment(TextAlginment.Center)
    Lobby_ReadyButton:setPosStr("25%", "70%")
    Lobby_ReadyButton:setText("Ready")
    Lobby_ReadyButton:setScale(.8)
    Lobby_ReadyButton:setHoverable(0,255,0,255,255,255,255,255)
    Lobby_ReadyButton:setOnClickCallback(function()
        print("toggle readiness")
        LobbyScene_ToggleReady()
        end)

    Lobby_ReadyLabel = RTLabel:new()
    Lobby_ReadyLabel:init(Lobby_GUIScriptingPtr,"",0,0)
    Lobby_ReadyLabel:setText(Tag.iRed .. "<Not Ready>" .. Tag.iClose)
    Lobby_ReadyLabel:setPosStr("33%", "22%")
    Lobby_ReadyLabel:setScale(.75)
    -- Lobby_ReadyLabel:setColor(255,0,0,255)

    Lobby_OpponentReadyLabel = RTLabel:new()
    Lobby_OpponentReadyLabel:init(Lobby_GUIScriptingPtr,"",0,0)
    -- Lobby_OpponentReadyLabel:setText(Tag.color_red "Not Ready" .. Tag.color_close)
    Lobby_OpponentReadyLabel:setPosStr("33%", "22%")
    Lobby_OpponentReadyLabel:setScale(.8)
    Lobby_OpponentReadyLabel:setColor(255,0,0,255)

    Prompt_UI_Table["Back_to_Home_Noti"] = Prompt:new()
    Prompt_UI_Table["Back_to_Home_Noti"]:init(Lobby_GUIScriptingPtr,"Notification",false)

    Prompt_UI_Table["Back_to_Home_Noti"]:addButton("OK", function()
        -- print("daaataaaa")
        -- cpp_backToHomeMenu(host)
        cpp_lobby_changeScene(SceneIndex.Home)
        Prompt_UI_Table["Back_to_Home_Noti"]:show(false)
    end
    )

    Prompt_UI_Table["Leave_Lobby_Noti"] = Prompt:new()
    Prompt_UI_Table["Leave_Lobby_Noti"]:init(Lobby_GUIScriptingPtr,"Leave Lobby ?",false)
    Prompt_UI_Table["Leave_Lobby_Noti"]:addButton("Leave", function()
        -- cpp_lobby_leaveLobby()
        -- Prompt_UI_Table["Leave_Lobby_Noti"]:show(false)


        -- Lobby_Leave_Decision =true
        print("ClientDisconnectFromCurrentBattleServer !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")
        ClientDisconnectFromCurrentBattleServer(ClientScriptingPtr)

        -- cppSelecBattleServer(ClientScriptingPtr,"")
        Prompt_UI_Table["Leave_Lobby_Noti"]:show(false)
        TM_addTask(function()
            print("Leave lobby")
            -- cpp_backToHomeMenu(host)
            -- Lobby_Leave_Decision = false
            -- cpp_lobby_changeScene(SceneIndex.Home)
        end,
        10)
    end
    )
    Prompt_UI_Table["Leave_Lobby_Noti"]:addButton("Back", function()
        print("back")
        Prompt_UI_Table["Leave_Lobby_Noti"]:show(false)
    end
    )

    local leaveLobby = Label:new()
    leaveLobby:init(Lobby_GUIScriptingPtr,"Leave Lobby",0,0)
    leaveLobby:setAlignment(TextAlginment.Left)
    leaveLobby:setPosStr("10%","85%")
    leaveLobby:setScale(1.1)
    leaveLobby:setHoverable(255,0,0,255,255,255,255,255)
    leaveLobby:setOnClickCallback(function()
        Prompt_UI_Table["Leave_Lobby_Noti"]:show(true)
        end
    )

    local tBattleServerGUID = InfoHolder_getStrVal("Target_BattleServer_GUID")

    if Formation_Selector == nil then
        Formation_Selector = Lobby_Formation_Selector:new()
    end

    Formation_Selector:init(host,TGUIScriptingPtr,ClientScriptingPtr,nil,1)
    -- Formation_Selector:setVisible(false)

    print("tBattleServerGUID " .. tBattleServerGUID)

    cppSelecBattleServer(ClientScriptingPtr,tBattleServerGUID)


    print("Init end ")
    TM_addTask(function()
        print("TM called")
        -- Client_Lobby_SendSyncRequest()
        -- Formation_Selector:setVisible(false)
        Lobby_UpdateInfo()
        Client_Lobby_Request_Formations()
    end
    ,10
    )

    print("Task set ")
    -- TM_addTask
end

function Lobby_setup()

end

function LobbyScene_ToggleReady()
    LobbyScene_isReady = not LobbyScene_isReady
    ---@diagnostic disable-next-line: param-type-mismatch
    InfoHolder_setNumberVal("LobbyScene_isReady", LobbyScene_isReady)
    Client_Lobby_SendSyncRequest()
    -- LobbyScene_ReadyStateUpdate()
end

function Lobby_UpdateInfo()
    Client_Lobby_SendSyncRequest()
    -- local id =InfoHolder_getStrVal("MainInfo.id")
    -- local pw = InfoHolder_getStrVal("MainInfo.pw")
    -- local guid = InfoHolder_getStrVal("MainInfo.guid")

    -- print("Lobby_UpdateInfo called " .. id .. " " .. pw .. " " .. guid)

    -- SendRequest(PacketChannel.UserChannel, UserResponse.MainInfo, {id, pw, guid}, 5, 0.25)

end

function LobbyScene_ReadyStateUpdate()
    if LobbyScene_isReady == true then
        Lobby_ReadyButton:setText("Not Ready")
        -- Lobby_ReadyButton:setHoverable(255,0,0,255,255,255,255,255)
        Lobby_ReadyLabel:setText(Tag.iGreen .. "<Ready>" .. Tag.iClose)
        -- Lobby_ReadyLabel:setColor(0,255,0,255)
    else
        Lobby_ReadyButton:setText("Ready")
        -- Lobby_ReadyButton:setHoverable(0,255,0,255,255,255,255,255)
        Lobby_ReadyLabel:setText(Tag.iRed .. "<Not Ready>" .. Tag.iClose)
        -- Lobby_ReadyLabel:setColor(255,0,0,255)
    end
end

function LobbyScene_ChangeHandleSync(clientList)

    local idLabelX = 25
    local idLabelY = 24

    local picX = 20
    local picY = 24

    local readyButtonX = 25
    local readyButtonY = 70

    local readyLabelX = 33
    local readyLabelY = 22

    local additionalPos = 50

    local myGUID = InfoHolder_getStrVal("MainInfo.guid")
    
    local myInfo = {}

    local tClientList = Table_DeepCopy(clientList)

    for k,v in pairs(tClientList) do
        print("k " .. k)
        if k == myGUID then
            myInfo = v
            -- table.remove(tClientList,k)
            tClientList[myGUID] = nil
        end
    end

    if(myInfo == nil) then
        print("myInfo not found")
        return
    end
    -- print("myInfo.readyState :" .. myInfo.readyState)
    LobbyScene_isReady = myInfo.readyState
    -- if myInfo.readyState == "true" then -- man, better if we use number, this is 1 off, to learn lesson
    --     LobbyScene_isReady = true
    -- else
    --     LobbyScene_isReady = false
    -- end

    LobbyScene_ReadyStateUpdate()

    local myIndex = tonumber(myInfo.index) -1

    LobbyAccountID:setPosStr(  tostring(idLabelX + (myIndex * additionalPos)) .. "%", "24%")
    Lobby_Picture:setPosStr(tostring(picX + (myIndex * additionalPos)) .. "%","24%")
    Lobby_ReadyButton:setPosStr(tostring(readyButtonX + (myIndex * additionalPos)) .. "%", "70%")
    Lobby_ReadyLabel:setPosStr(tostring(readyLabelX + (myIndex * additionalPos)) .. "%", "24%")

    ---- calculated based on myIndex
    if next(tClientList) == nil then
        print("tClientList is empty")

        Lobby_OpponentPicture:setTexture("Assets/TB_GUI/faces/nothing.png")
        Lobby_OpponentReadyLabel:setText("")
        LobbyOpponentID:setText("")
        return
    end

    print("table still has data " )

    for k,v in pairs(tClientList) do ---- remaining client
        print("remaing client check " .. k )
        local index = tonumber(v.index)
        LobbyOpponentID:setText(v.id)
        LobbyOpponentID:setPosStr(  tostring(idLabelX + (index - 1) * additionalPos) .. "%", "24%")
        Lobby_OpponentPicture:setPosStr(tostring(picX + (index - 1) * additionalPos) .. "%","24%")
        Lobby_OpponentReadyLabel:setPosStr(tostring(readyLabelX + (index - 1) * additionalPos) .. "%", "24%")
        Lobby_OpponentPicture:setTexture("Assets/TB_GUI/faces/Reimu_face.png")
        if v.readyState == true then
            Lobby_OpponentReadyLabel:setText(Tag.iGreen .. "<Ready>" .. Tag.iClose)
            -- Lobby_OpponentReadyLabel:setColor(0,255,0,255)
        else
            Lobby_OpponentReadyLabel:setText(Tag.iRed .. "<Not Ready>" .. Tag.iClose)
            -- Lobby_OpponentReadyLabel:setColor(255,0,0,255)
        end
    end
    if Formation_Selector ~= nil then
        Formation_Selector:setIndex(tonumber(myInfo.index))
        -- Formation_Selector:setVisible(true)
    else
    

    end
    
end

require "lobby_Input_control"


function Lobby_RecieveData(host,msg, ip, pID, RakNetPacket)

    local tPacket = Client_Packet:new()
    tPacket.data = msg
    tPacket.ipAddr = ip
    tPacket.packetID = pID
    Lobby_HandlePacket(host,tPacket,RakNetPacket)
    -- if Lobby_HandleNetwork[pID] ~= nil then
    --     Lobby_HandleNetwork[pID](host,ip,pID,RakNetPacket)
    -- else
    --     print("(Lobby_RecieveData)no handler for packet " .. pID)
    -- end
end 

function Lobby_HandlePacket(host, packet, RakNetPacket)
    for k,v in pairs(Lobby_HandleNetwork) do
        -- print(k)
        if Lobby_HandleNetwork[k] ~= nil then
            Lobby_HandleNetwork[k](host,packet,RakNetPacket)
        end
    end
end



-- HandlePacketTask["home_main"] = function(host,packet,RakNetPacket)
--     print("handle home packet task " .. packet.packetID)
--     if HomeMain_HandleTask[packet.packetID] ~= nil then
--         HomeMain_HandleTask[packet.packetID](host,packet,RakNetPacket)
--     end
-- end

