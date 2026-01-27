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

---@type Label
LobbyTitleLabel = nil

---@type Label
LobbyAccountID = nil

---@type Label
LobbyIDLabel = nil

---@type Picture
Lobby_Picture = nil

---@type Label
Lobby_ReadyLabel = nil

---@type Label
LobbyOpponentID = nil

---@type Picture
Lobby_OpponentPicture = nil

---@type Label
Lobby_OpponentReadyLabel = nil



---@type Label
Lobby_ReadyButton = nil

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

    LobbyAccountID = Label:new()
    LobbyAccountID:init(Lobby_GUIScriptingPtr,"",0,0)
    LobbyAccountID:setText(id)
    LobbyAccountID:setPosStr("25%", "24%")
    LobbyAccountID:setScale(.8)

    LobbyOpponentID = Label:new()
    LobbyOpponentID:init(Lobby_GUIScriptingPtr,"",0,0)
    LobbyOpponentID:setText("")
    LobbyOpponentID:setPosStr("75%", "24%")
    LobbyOpponentID:setScale(.8)

    Lobby_Picture = Picture:new()
    Lobby_Picture:init(Lobby_GUIScriptingPtr,"Assets/TB_GUI/faces/Reimu_face.png",0,0,100,100)
    Lobby_Picture:setPosStr("20%","24%")
    Lobby_Picture:setSize(75,75)

    Lobby_OpponentPicture = Picture:new()
    Lobby_OpponentPicture:init(Lobby_GUIScriptingPtr,"Assets/TB_GUI/faces/missing.png",0,0,100,100)
    Lobby_OpponentPicture:setPosStr("70%","24%")
    Lobby_OpponentPicture:setSize(75,75)

    Lobby_ReadyButton = Label:new()
    Lobby_ReadyButton:init(Lobby_GUIScriptingPtr,"Ready",0,0)
    Lobby_ReadyButton:setAlignment(TextAlginment.Center)
    Lobby_ReadyButton:setPosStr("30%", "70%")
    Lobby_ReadyButton:setScale(.8)
    Lobby_ReadyButton:setHoverable(0,255,0,255,255,255,255,255)
    Lobby_ReadyButton:setOnClickCallback(function()
        print("toggle readiness")
        LobbyScene_ToggleReady()
        end)

    Lobby_ReadyLabel = Label:new()
    Lobby_ReadyLabel:init(Lobby_GUIScriptingPtr,"",0,0)
    Lobby_ReadyLabel:setText("Not Ready")
    Lobby_ReadyLabel:setPosStr("30%", "24%")
    Lobby_ReadyLabel:setScale(.8)
    Lobby_ReadyLabel:setColor(255,0,0,255)

    Lobby_OpponentReadyLabel = Label:new()
    Lobby_OpponentReadyLabel:init(Lobby_GUIScriptingPtr,"",0,0)
    Lobby_OpponentReadyLabel:setText("Not Ready")
    Lobby_OpponentReadyLabel:setPosStr("30%", "24%")
    Lobby_OpponentReadyLabel:setScale(.8)
    Lobby_OpponentReadyLabel:setColor(255,0,0,255)

    Prompt_UI_Table["Back_to_Home_Noti"] = Prompt:new()
    Prompt_UI_Table["Back_to_Home_Noti"]:init(Lobby_GUIScriptingPtr,"Notification",false)

    Prompt_UI_Table["Back_to_Home_Noti"]:addButton("OK", function()
        -- print("daaataaaa")
        cpp_lobby_changeScene(SceneIndex.Home)
    end
    )

    local tBattleServerGUID = InfoHolder_getStrVal("Target_BattleServer_GUID")

    cppSelecBattleServer(ClientScriptingPtr,tBattleServerGUID)
    
    print("Init end ")
    TM_addTask(function()
        print("TM called")
        Client_Lobby_SendSyncRequest() 
    end
    ,10
    )

    print("Task set ")
    -- TM_addTask

end

function LobbyScene_ToggleReady()
    LobbyScene_isReady = not LobbyScene_isReady

    if LobbyScene_isReady == true then
        Lobby_ReadyButton:setText("Not Ready")
        -- Lobby_ReadyButton:setHoverable(255,0,0,255,255,255,255,255)
        Lobby_ReadyLabel:setText("Ready")
        Lobby_ReadyLabel:setColor(0,255,0,255)
    else
        Lobby_ReadyButton:setText("Ready")
        -- Lobby_ReadyButton:setHoverable(0,255,0,255,255,255,255,255)
        Lobby_ReadyLabel:setText("Not Ready")
        Lobby_ReadyLabel:setColor(255,0,0,255)
    end
end

function LobbyScene_ChangeHandleSync(clientList)

    local idLabelX = 25
    local idLabelY = 24

    local picX = 20
    local picY = 24

    local readyButtonX = 30
    local readyButtonY = 70

    local readyLabelX = 30
    local readyLabelY = 24

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

    

    local myIndex = tonumber(myInfo.index) -1

    LobbyAccountID:setPosStr(  tostring(idLabelX + (myIndex * additionalPos)) .. "%", "24%")
    Lobby_Picture:setPosStr(tostring(picX + (myIndex * additionalPos)) .. "%","24%")
    Lobby_ReadyButton:setPosStr(tostring(readyButtonX + (myIndex * additionalPos)) .. "%", "70%")
    Lobby_ReadyLabel:setPosStr(tostring(readyLabelX + (myIndex * additionalPos)) .. "%", "24%")

    ---- calculated based on myIndex
    if next(tClientList) == nil then
        print("tClientList is empty")

        Lobby_OpponentPicture:setTexture("Assets/TB_GUI/faces/missing.png")
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

