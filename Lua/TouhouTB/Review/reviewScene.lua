package.path = package.path .. ';../../Lua/system/GUI/?/?.lua;' .. ';../../Lua/system/GUI/widgets/?.lua;' .. ';../../Lua/system/Networking/?.lua;' .. ';../../Lua/TouhouTB/Combat/?.lua;' .. ';../../Lua/system/event/?.lua;' .. ';../../Lua/TouhouTB/characters/?.lua;' .. ';../../Lua/?.lua;' .. './TouhouTB/characters/Common/?.lua;' .. './TouhouTB/characters/Patchy/?.lua;' .. ';../../Lua/TouhouTB/characters/Patchy/?.lua;' .. ';./TouhouTB/characters/Reimu/slots/?.lua;' .. ';../../Lua/TouhouTB/characters/Reimu/?.lua;' .. ';./TouhouTB/characters/Yukari/slots/?.lua;' .. ';../../Lua/TouhouTB/characters/Yukari/?.lua;' .. ';../../Lua/TouhouTB/?.lua' .. ';../../Lua/TouhouTB/characters/Meiling/?.lua;' .. ';../../Lua/TouhouTB/?.lua' .. ';../../Lua/system/objects/?.lua;' .. ';../../Lua/TouhouTB/Combat/UI/?.lua;'

require "TGUI_Label"
require "TGUI_Panel"
require "TGUI_RTLabel" 
require "TGUI_Editbox"
require "TGUI_Picture"

require "compositeObject"

-- require "lobbyFormationSelector"
require "Prompt"
-- require "combatField"

require "combat_dock"

CombatSceneHost = nil

---@type pointer TGUIScriptingPtr
Combat_GUIScriptingPtr = nil


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

function ReviewSceneInit(host,TGUIScriptingPtr,ClientCharacterHandlerPtr, SkillHandlerPtr, ControlHandlerPtr, CombatFieldPtr, RenderContextPtr)

    print("ReviewSceneInit called")
    CombatSceneHost = host
    Combat_GUIScriptingPtr = TGUIScriptingPtr

    Combat_ClientCharacterHandlerPtr = ClientCharacterHandlerPtr
    Combat_SkillHandlerPtr = SkillHandlerPtr
    Combat_ControlHandlerPtr = ControlHandlerPtr
    Combat_RenderContext = RenderContextPtr

    CombatField_instance = CombatField:new()
    CombatField_instance:init(CombatFieldPtr,3,3)

    Combat_Dock = Combat_dock:new()
    local resoX, resoY = 1600, 900 --cpp_combat_getSceneResolution(host)
    Combat_Dock:init(Combat_RenderContext, resoX, resoY)

    -- SetBattleSer

    -- get the battle server GUID to send 

end



