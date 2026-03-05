package.path = package.path .. ';../../Lua/system/GUI/?/?.lua;' .. ';../../Lua/system/GUI/widgets/?.lua;' .. ';../../Lua/system/Networking/?.lua;' .. ';../../Lua/TouhouTB/Combat/?.lua;' .. ';../../Lua/system/event/?.lua;' .. ';../../Lua/TouhouTB/characters/?.lua;' .. ';../../Lua/?.lua;' .. './TouhouTB/characters/Common/?.lua;' .. './TouhouTB/characters/Patchy/?.lua;' .. ';../../Lua/TouhouTB/characters/Patchy/?.lua;' .. ';./TouhouTB/characters/Reimu/slots/?.lua;' .. ';../../Lua/TouhouTB/characters/Reimu/?.lua;' .. ';./TouhouTB/characters/Yukari/slots/?.lua;' .. ';../../Lua/TouhouTB/characters/Yukari/?.lua;' .. ';../../Lua/TouhouTB/?.lua' .. ';../../Lua/TouhouTB/characters/Meiling/?.lua;' .. ';../../Lua/TouhouTB/?.lua'

require "TGUI_Label"
require "TGUI_Panel"
require "TGUI_RTLabel" 
require "TGUI_Editbox"
require "TGUI_Picture"

require "clientSide"
require "clientWrapper"
require "clientGlobal"
require "combat_global"

-- require "lobbyFormationSelector"
require "Prompt"

CombatSceneHost = nil

---@type pointer TGUIScriptingPtr
Combat_GUIScriptingPtr = nil

---@type pointer ClientScriptingPtr
Combat_ClientScriptingPtr = nil

---@type pointer ClientCharacterHandler
Combat_ClientCharacterHandlerPtr = nil

---@type pointer ControlHandlerPtr
Combat_ControlHandlerPtr = nil

--@type pointer SkillHandler
Combat_SkillHandlerPtr = nil


function CombatSceneInit(host,TGUIScriptingPtr,ClientScriptingPtr,ClientCharacterHandlerPtr, SkillHandlerPtr, ControlHandlerPtr)

    print("CombatSceneInit called")
    CombatSceneHost = host
    Combat_GUIScriptingPtr = TGUIScriptingPtr
    Combat_ClientScriptingPtr = ClientScriptingPtr
    Combat_ClientCharacterHandlerPtr = ClientCharacterHandlerPtr
    Combat_SkillHandlerPtr = SkillHandlerPtr
    Combat_ControlHandlerPtr = ControlHandlerPtr



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

    SendBattleRequest(BattlePacketChannel.Combat,CCombatResponse.Combat_ReadyStatus, {tGUID,tID,tLobbyID,tPlayerIndex,"Ready"},5,0.1,0.15)

end

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
