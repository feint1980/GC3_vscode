package.path = package.path .. ';../../Lua/system/GUI/?/?.lua;' .. ';../../Lua/system/GUI/widgets/?.lua;' .. ';../../Lua/system/Networking/?.lua;' .. ';../../Lua/TouhouTB/Combat/?.lua;' .. ';../../Lua/system/event/?.lua;' .. ';../../Lua/TouhouTB/characters/?.lua;' .. ';../../Lua/?.lua;' .. './TouhouTB/characters/Common/?.lua;' .. './TouhouTB/characters/Patchy/?.lua;' .. ';../../Lua/TouhouTB/characters/Patchy/?.lua;' .. ';./TouhouTB/characters/Reimu/slots/?.lua;' .. ';../../Lua/TouhouTB/characters/Reimu/?.lua;' .. ';./TouhouTB/characters/Yukari/slots/?.lua;' .. ';../../Lua/TouhouTB/characters/Yukari/?.lua;' .. ';../../Lua/TouhouTB/?.lua' .. ';../../Lua/TouhouTB/characters/Meiling/?.lua;' .. ';../../Lua/TouhouTB/?.lua' .. ';../../Lua/system/objects/?.lua;'

require "TGUI_Label"
require "TGUI_Panel"
require "TGUI_RTLabel" 
require "TGUI_Editbox"
require "TGUI_Picture"

require "compositeObject"

require "clientSide"
require "clientWrapper"
require "clientGlobal"

-- require "lobbyFormationSelector"
require "Prompt"
-- require "combatField"

require "combat_dock"

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


--@type pointer CombatField
Combat_RenderContext = nil

---@type Combat_dock 
Combat_Dock = nil

function CombatSceneInit(host,TGUIScriptingPtr,ClientScriptingPtr,ClientCharacterHandlerPtr, SkillHandlerPtr, ControlHandlerPtr, CombatFieldPtr, TurnDisplayerPtr, RenderContextPtr)

    print("CombatSceneInit called")
    CombatSceneHost = host
    Combat_GUIScriptingPtr = TGUIScriptingPtr
    Combat_ClientScriptingPtr = ClientScriptingPtr
    Combat_ClientCharacterHandlerPtr = ClientCharacterHandlerPtr
    Combat_SkillHandlerPtr = SkillHandlerPtr
    Combat_ControlHandlerPtr = ControlHandlerPtr
    Combat_RenderContext = RenderContextPtr


    CombatField_instance = CombatField:new()
    CombatField_instance:init(CombatFieldPtr,3,3)

    TurnDisplayer_instance = CombatTurnDisplayer:new()
    TurnDisplayer_instance:init(TurnDisplayerPtr)

    Combat_Dock = Combat_dock:new()
    local resoX, resoY = cpp_combat_getSceneResolution(host)
    Combat_Dock:init(Combat_RenderContext, resoX, resoY)


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

    -- local tA = L_compositeObject:new()
    -- tA:init(Combat_RenderContext, 0, 0, 250, 250, 0, 5)
    -- tA:addAnimatedObject("./Assets/F_AObjects/meiling_tb.xml", "idle", 0, 0, 1, 1, 255, 255, 255, 255, 0, 0)

    -- tA:addPanel("Basic_border", 0.25)
    -- tA:addEmblem(0,"emblem_pack.xml/corner_c_25.png", 15,0, 0, 
    --     10, 0.5)
    
    -- tA:addEmblem(1,"emblem_pack.xml/corner_a_07_2.png", 15,0, 8, 
    --     -10, 0.25)

    -- -- tA:setAngle(45.0)

    -- tA:addText("ekwes", 0,10, 1,0.5, 255,255,255,255,0)

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
