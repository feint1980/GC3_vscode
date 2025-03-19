package.path = package.path .. ';./Assets/Lua/system/GUI/?/?.lua;' .. ';./Assets/Lua/system/GUI/widgets/?.lua;' .. ';./Assets/Lua/system/Networking/?.lua;' .. ';./Assets/Lua/Login/?.lua;'

-- require "tguiScript"

require "TGUI_Label"
require "TGUI_Panel"
require "TGUI_RTLabel" 
require "TGUI_Editbox"
require "TGUI_Picture"
require "clientSide"
require "clientWrapper"
require "loginStripOrder"



HomeSceneHost = nil

---@type pointer TGUIScriptingPtr
Home_GUIScriptingPtr = nil

---@type pointer ClientScriptingPtr
Home_ClientScriptingPtr = nil


--- Main 
---@type Label
Main_NameLabel = nil

---@type Label
Main_SoulsLabel = nil
---@type Label
Main_SoulsValLabel = nil

---@type Label
Main_MonLabel = nil
---@type Label
Main_MonValLabel = nil



function HomeSceneInit(host,TGUIScriptingPtr,ClientScriptingPtr)
    HomeSceneHost = host
    Home_GUIScriptingPtr = TGUIScriptingPtr
    Home_ClientScriptingPtr = ClientScriptingPtr

    if HomeSceneHost ~= nil then
        print("LoginHost is not nil")
    end

    if Home_GUIScriptingPtr ~= nil then
        print("Home_GUIScriptingPtr is not nil")
    end

    ---- GUI section ----
    Main_NameLabel = Label:new()
    Main_NameLabel:init(Home_GUIScriptingPtr,"",0,0)

    local id,pw, guid = Home_GetInfo(3)

    Main_NameLabel:setText(id)
    Main_NameLabel:setPosStr("10%", "10%")

    local picture = Picture:new()
    picture:init(Home_GUIScriptingPtr,"Assets/TB_GUI/faces/Reimu_face.png",0,0,100,100)
    picture:setPosStr("5%","5%")
    picture:setSize(75,75)


    Main_SoulsLabel = Label:new()
    Main_SoulsLabel:init(Home_GUIScriptingPtr,"Souls:",0,0)
    Main_SoulsLabel:setPosStr("70%","5%")

    Main_SoulsValLabel = Label:new()
    Main_SoulsValLabel:init(Home_GUIScriptingPtr,"?",0,0)
    Main_SoulsValLabel:setPosStr("75%","5%")
    Main_SoulsValLabel:setAlignment(TextAlginment.Right)


    Main_MonLabel = Label:new()
    Main_MonLabel:init(Home_GUIScriptingPtr,"Mon:",0,0)
    Main_MonLabel:setPosStr("80%","5%")

    Main_MonValLabel = Label:new()
    Main_MonValLabel:init(Home_GUIScriptingPtr,"?",0,0)
    Main_MonValLabel:setPosStr("85%","5%")
    Main_MonValLabel:setAlignment(TextAlginment.Right)

    Home_RequestUserlData()

end



function Home_RequestUserlData()

    local id,pw, guid = Home_GetInfo(3)

    Client_SendData( Home_ClientScriptingPtr,CombinePackage("USERDATA", {id, pw, guid}))
end 


---function wrapper of cpp_getInfo
---@param no number
---@return string multiple strings ( up to 3)
function Home_GetInfo(no)
    return cpp_getInfo(no)
end

