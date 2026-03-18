package.path = package.path .. ';../../Lua/system/GUI/?/?.lua;' .. ';../../Lua/system/GUI/widgets/?.lua;' .. ';../../Lua/system/Networking/?.lua;' .. ';../../Lua/TouhouTB/Combat/?.lua;' .. ';../../Lua/system/event/?.lua;' .. ';../../Lua/TouhouTB/characters/?.lua;' .. ';../../Lua/?.lua;' .. './TouhouTB/characters/Common/?.lua;' .. './TouhouTB/characters/Patchy/?.lua;' .. ';../../Lua/TouhouTB/characters/Patchy/?.lua;' .. ';./TouhouTB/characters/Reimu/slots/?.lua;' .. ';../../Lua/TouhouTB/characters/Reimu/?.lua;' .. ';./TouhouTB/characters/Yukari/slots/?.lua;' .. ';../../Lua/TouhouTB/characters/Yukari/?.lua;' .. ';../../Lua/TouhouTB/?.lua' .. ';../../Lua/TouhouTB/characters/Meiling/?.lua;' .. ';../../Lua/TouhouTB/?.lua'

require "TGUI_Label"
require "TGUI_Panel"
require "TGUI_RTLabel" 
require "TGUI_Editbox"
require "TGUI_Picture"

require "clientSide"
require "clientWrapper"
require "clientGlobal"


-- require "lobbyFormationSelector"
require "Prompt"
-- require "combatField"

CombatSceneHost = nil

---@type pointer TGUIScriptingPtr
Combat_GUIScriptingPtr = nil

---@type pointer ClientScriptingPtr
Combat_ClientScriptingPtr = nil

---@type pointer ClientCharacterHandler
Combat_ClientCharacterHandlerPtr = nil

---@type pointer ControlHandlerPtr
Combat_ControlHandlerPtr = nil

---@type pointer SkillHandler
Combat_SkillHandlerPtr = nil

---@type pointer CombatField instance
CombatField_instance = nil

function CombatSceneInit(host,TGUIScriptingPtr,ClientScriptingPtr,ClientCharacterHandlerPtr, SkillHandlerPtr, ControlHandlerPtr, CombatFieldPtr)

    print("CombatSceneInit called")
    CombatSceneHost = host
    Combat_GUIScriptingPtr = TGUIScriptingPtr
    Combat_ClientScriptingPtr = ClientScriptingPtr
    Combat_ClientCharacterHandlerPtr = ClientCharacterHandlerPtr
    Combat_SkillHandlerPtr = SkillHandlerPtr
    Combat_ControlHandlerPtr = ControlHandlerPtr
    CombatField_instance = CombatField:new()
    CombatField_instance:init(CombatFieldPtr,3,3)

    -- SetBattleSer
    print("loading data ...")
    local battleServerGUID =  InfoHolder_getStrVal("BattleServerGUID")
    print("battle server GUID " .. battleServerGUID)
    -- get the battle server GUID to send 
    cppSelecBattleServer(Combat_ClientScriptingPtr, battleServerGUID)

    local tGUID = InfoHolder_getStrVal("MainInfo.guid")
    local tID = InfoHolder_getStrVal("MainInfo.id")
    local tLobbyID = InfoHolder_getStrVal("CurrentLobbyID")
    local tPlayerIndex = InfoHolder_getNumberVal("Player_Index")

    print("data check " .. tGUID .. " " .. tID .. " " .. tLobbyID .. " " .. tPlayerIndex)

    SendBattleRequest(BattlePacketChannel.Combat,CCombatResponse.Combat_ReadyStatus, {tGUID,tID,tLobbyID,tPlayerIndex,"Ready"},5,
    0.1,0.15)

end

require "combat_global"
-- require "combat_network"

function Combat_RecieveData(host,msg, ip, pID, RakNetPacket)

    local tPacket = Client_Packet:new()
    tPacket.data = msg
    tPacket.ipAddr = ip
    tPacket.packetID = pID
    Combat_HandlePacket(host,tPacket,RakNetPacket)
end

function Combat_HandlePacket(host, packet, RakNetPacket)
    for k,v in pairs(Combat_HandleNetwork) do
        -- print(k)
        if Combat_HandleNetwork[k] ~= nil then
            Combat_HandleNetwork[k](host,packet,RakNetPacket)
        end
    end
end

function CombatScene_SetSceneReady()
    print("CombatScene_SetSceneReady called")
    cpp_combat_sceneReady(CombatSceneHost,true)
end
