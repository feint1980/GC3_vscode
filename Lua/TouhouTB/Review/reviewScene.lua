package.path = package.path .. ';../../Lua/system/GUI/?/?.lua;' .. ';../../Lua/system/GUI/widgets/?.lua;' .. ';../../Lua/system/Networking/?.lua;' .. ';../../Lua/TouhouTB/Combat/?.lua;' .. ';../../Lua/system/event/?.lua;' .. ';../../Lua/TouhouTB/characters/?.lua;' .. ';../../Lua/?.lua;' .. './TouhouTB/characters/Common/?.lua;' .. './TouhouTB/characters/Patchy/?.lua;' .. ';../../Lua/TouhouTB/characters/Patchy/?.lua;' .. ';./TouhouTB/characters/Reimu/slots/?.lua;' .. ';../../Lua/TouhouTB/characters/Reimu/?.lua;' .. ';./TouhouTB/characters/Yukari/slots/?.lua;' .. ';../../Lua/TouhouTB/characters/Yukari/?.lua;' .. ';../../Lua/TouhouTB/?.lua' .. ';../../Lua/TouhouTB/characters/Meiling/?.lua;' .. ';../../Lua/TouhouTB/?.lua' .. ';../../Lua/system/objects/?.lua;' .. ';../../Lua/TouhouTB/Combat/UI/?.lua;' .. ';../../Lua/TouhouTB/Review/?.lua;'

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

ReviewSceneHost = nil

---@type pointer TGUIScriptingPtr
Review_GUIScriptingPtr = nil


---@type pointer ClientCharacterHandler
Review_ClientCharacterHandlerPtr = nil

---@type pointer ControlHandlerPtr
Review_ControlHandlerPtr = nil

---@type pointer SkillHandler
Review_SkillHandlerPtr = nil

--@type pointer CombatField
Review_RenderContext = nil

---@type Combat_dock 
Review_Dock = nil

function ReviewSceneInit(host,TGUIScriptingPtr,ClientCharacterHandlerPtr, SkillHandlerPtr, ControlHandlerPtr, CombatFieldPtr, RenderContextPtr)

    print("ReviewSceneInit called")
    ReviewSceneHost = host
    Review_GUIScriptingPtr = TGUIScriptingPtr

    Review_ClientCharacterHandlerPtr = ClientCharacterHandlerPtr
    Review_SkillHandlerPtr = SkillHandlerPtr
    Review_ControlHandlerPtr = ControlHandlerPtr
    Review_RenderContext = RenderContextPtr

    
    -- CombatField_instance = CombatField:new()
    -- CombatField_instance:init(CombatFieldPtr,3,3)

    Review_Dock = Combat_dock:new()
    local resoX, resoY = 1600, 900 --cpp_combat_getSceneResolution(host)
    Review_Dock:init(Review_RenderContext, resoX, resoY)

    -- SetBattleSer

    -- local loginDecorateFrame = L_compositeObject:new()
    -- loginDecorateFrame:init(Review_RenderContext, 0, -10, 500, 270, 0, 5)

    -- loginDecorateFrame:addPanel("Simple_border", 0.25)

    -- loginDecorateFrame:addEmblem(0,"emblem_pack.xml/corner_c_25.png", 15,0, 0,
    --     10, 0.5)
    -- loginDecorateFrame:addText("東方黄昏結界", 610,-400, 3,1.0, 255,255,255,255,0)
    -- loginDecorateFrame:addLine(610, -420, 165, 5)

    -- get the battle server GUID to send 

end

---- Input control 
require "reviewScene_input_control"