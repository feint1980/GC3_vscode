package.path = package.path .. ';../../Lua/system/GUI/?/?.lua;' .. ';../../Lua/system/GUI/widgets/?.lua;' .. ';../../Lua/system/Networking/?.lua;' .. ';../../Lua/TouhouTB/Home/?.lua;' .. ';../../Lua/system/event/?.lua;' .. ';../../Lua/TouhouTB/Home/Shop/?.lua;' .. ';../../Lua/TouhouTB/characters/?.lua;' .. ';../../Lua/?.lua;' .. './TouhouTB/characters/Common/?.lua;' .. './TouhouTB/characters/Patchy/?.lua;' .. ';../../Lua/TouhouTB/characters/Patchy/?.lua;' .. ';./TouhouTB/characters/Reimu/slots/?.lua;' .. ';../../Lua/TouhouTB/characters/Reimu/?.lua;' .. ';./TouhouTB/characters/Yukari/slots/?.lua;' .. ';../../Lua/TouhouTB/characters/Yukari/?.lua;' .. ';../../Lua/TouhouTB/?.lua' .. ';../../Lua/TouhouTB/characters/Meiling/?.lua;' .. ';../../Lua/TouhouTB/?.lua' 

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

end