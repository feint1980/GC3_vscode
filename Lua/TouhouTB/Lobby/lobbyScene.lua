package.path = package.path .. ';../../Lua/system/GUI/?/?.lua;' .. ';../../Lua/system/GUI/widgets/?.lua;' .. ';../../Lua/system/Networking/?.lua;' .. ';../../Lua/TouhouTB/Lobby/?.lua;' .. ';../../Lua/system/event/?.lua;' .. ';../../Lua/TouhouTB/characters/?.lua;' .. ';../../Lua/?.lua;' .. './TouhouTB/characters/Common/?.lua;' .. './TouhouTB/characters/Patchy/?.lua;' .. ';../../Lua/TouhouTB/characters/Patchy/?.lua;' .. ';./TouhouTB/characters/Reimu/slots/?.lua;' .. ';../../Lua/TouhouTB/characters/Reimu/?.lua;' .. ';./TouhouTB/characters/Yukari/slots/?.lua;' .. ';../../Lua/TouhouTB/characters/Yukari/?.lua;' .. ';../../Lua/TouhouTB/?.lua' .. ';../../Lua/TouhouTB/characters/Meiling/?.lua;' .. ';../../Lua/TouhouTB/?.lua' 

require "TGUI_Label"
require "TGUI_Panel"
require "TGUI_RTLabel" 
require "TGUI_Editbox"
require "TGUI_Picture"
require "clientSide"
require "clientWrapper"
require "clientGlobal"

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
LobbyIDLabel = nil


---@type Label
Lobby_ReadyLabel = nil

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

    local accountID = Label:new()
    accountID:init(Lobby_GUIScriptingPtr,"",0,0)
    accountID:setText(id)
    accountID:setPosStr("25%", "24%")
    accountID:setScale(.8)

    local picture = Picture:new()
    picture:init(Lobby_GUIScriptingPtr,"Assets/TB_GUI/faces/Reimu_face.png",0,0,100,100)
    picture:setPosStr("20%","24%")
    picture:setSize(75,75)


    
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


require "lobby_Input_control"

Lobby_HandleNetwork = {}

require "lobby_client_network"

function Lobby_RecieveData(host, ip, pID, RakNetPacket)

    if Lobby_HandleNetwork[pID] ~= nil then
        Lobby_HandleNetwork[pID](host,ip,pID,RakNetPacket)
    else
        print("(Lobby_RecieveData)no handler for packet " .. pID)
    end
end

-- HandlePacketTask["home_main"] = function(host,packet,RakNetPacket)
--     print("handle home packet task " .. packet.packetID)
--     if HomeMain_HandleTask[packet.packetID] ~= nil then
--         HomeMain_HandleTask[packet.packetID](host,packet,RakNetPacket)
--     end
-- end

