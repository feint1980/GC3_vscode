package.path = package.path .. ';../../Lua/system/GUI/?/?.lua;' .. ';../../Lua/system/GUI/widgets/?.lua;' .. ';../../Lua/system/Networking/?.lua;' .. ';../../Lua/TouhouTB/Home/?.lua;' .. ';../../Lua/system/event/?.lua;' .. ';../../Lua/TouhouTB/Home/Shop/?.lua;' .. ';../../Lua/TouhouTB/characters/?.lua;' .. ';../../Lua/?.lua;' .. './TouhouTB/characters/Common/?.lua;' .. './TouhouTB/characters/Patchy/?.lua;' .. ';../../Lua/TouhouTB/characters/Patchy/?.lua;' .. ';./TouhouTB/characters/Reimu/slots/?.lua;' .. ';../../Lua/TouhouTB/characters/Reimu/?.lua;' .. ';./TouhouTB/characters/Yukari/slots/?.lua;' .. ';../../Lua/TouhouTB/characters/Yukari/?.lua;' .. ';../../Lua/TouhouTB/?.lua' .. ';../../Lua/TouhouTB/characters/Meiling/?.lua;' .. ';../../Lua/TouhouTB/?.lua' 

require "TGUI_Label"
require "TGUI_Panel"
require "TGUI_RTLabel" 
require "TGUI_Editbox"
require "TGUI_Picture"
require "clientSide"
require "clientWrapper"


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
LobbyTitle = nil

function LobbySceneInit(host,TGUIScriptingPtr,ClientScriptingPtr,ClientCharacterHandlerPtr, SkillHandlerPtr, ControlHandlerPtr)


    print("LobbySceneInit called")
    LobbySceneHost = host
    Lobby_GUIScriptingPtr = TGUIScriptingPtr
    Lobby_ClientScriptingPtr = ClientScriptingPtr
    Lobby_ClientCharacterHandlerPtr = ClientCharacterHandlerPtr
    Lobby_SkillHandlerPtr = SkillHandlerPtr
    Lobby_ControlHandlerPtr = ControlHandlerPtr


    LobbyTitle = Label:new()
    LobbyTitle:init(Lobby_GUIScriptingPtr,"",0,0)
    LobbyTitle:setText("Lobby name")
    LobbyTitle:setPosStr("50%", "10%")
    

    local id,pw,guid = cpp_lobby_getInfo(3)

    print("id " .. id)
    print("pw " .. pw)
    print("guid " .. guid)
end