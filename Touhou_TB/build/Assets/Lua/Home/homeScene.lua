package.path = package.path .. ';./Assets/Lua/system/GUI/?/?.lua;' .. ';./Assets/Lua/system/GUI/widgets/?.lua;' .. ';./Assets/Lua/system/Networking/?.lua;' .. ';./Assets/Lua/Login/?.lua;'

-- require "tguiScript"

require "TGUI_Label"
require "TGUI_Panel"
require "TGUI_RTLabel" 
require "TGUI_Editbox"
require "clientSide"


LoginHost = nil

---@type pointer TGUIScriptingPtr
Login_GUIScriptingPtr = nil

---@type pointer ClientScriptingPtr
Login_ClientScriptingPtr = nil
