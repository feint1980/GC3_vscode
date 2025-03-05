
package.path = package.path .. ';./Assets/Lua/system/GUI/?/?.lua;' .. ';./Assets/Lua/system/GUI/widgets/?.lua;' .. ';./Assets/Lua/system/Networking/?.lua;'

-- require "tguiScript"

require "TGUI_Label"
require "TGUI_Panel"
require "TGUI_RTLabel" 
require "TGUI_Editbox"
require "clientSide"

print("login scene run\n")

---@class TGUIScriptingPtr
---@class ClientScriptingPtr

--- Global variables section start ----

LoginHost = nil

---@type TGUIScriptingPtr
Login_GUIScriptingPtr = nil

---@type ClientScriptingPtr
Login_ClientScriptingPtr = nil

---@type Label
Login_PlayOfflineBtn = nil
---@type Label
Login_PlayOnlineBtn = nil
---@type Label
Login_ExitBtn = nil

---@type Panel
Login_Noti_Panel = nil
---@type RTLabel
Login_Noti_Msg = nil
---@type Label
Login_Noti_Btn = nil


--- Global variables section end ----

function LoginSceneInit(host,TGUIScriptingPtr,ClientScriptingPtr)

    LoginHost = host
    Login_GUIScriptingPtr = TGUIScriptingPtr
    Login_ClientScriptingPtr = ClientScriptingPtr
    if LoginHost ~= nil then
        print("LoginHost is not nil")
    end

    if Login_GUIScriptingPtr ~= nil then
        print("Login_GUIScriptingPtr is not nil")
    end


        --- Notification section ----
        Login_Noti_Panel = Panel:new()
        Login_Noti_Panel:init(Login_GUIScriptingPtr,TGUI_ScreenWidth/2 - 225,TGUI_ScreenHeight/2 -150,450, 300)
        Login_Noti_Panel:setAligment(0.5,0,5)
        Login_Noti_Panel:setSizeStr("25%", "20%")
        Login_Noti_Panel:setPosStr("50%", "50%")
        Login_Noti_Panel:setVisible(false)
    
        Login_Noti_Msg = RTLabel:new()
        Login_Noti_Msg:init(Login_GUIScriptingPtr,"",0,0,Login_Noti_Panel.ptr)
        Login_Noti_Msg:setAlignment(TextAlginment.Center)
        Login_Noti_Msg:setPosStr("50%","20%")
    
        Login_Noti_Btn = Label:new()
        Login_Noti_Btn:init(Login_GUIScriptingPtr,"OK",0,0,Login_Noti_Panel.ptr)
        Login_Noti_Btn:setAlignment(TextAlginment.Center)
        Login_Noti_Btn:setPosStr("50%","75%")
        Login_Noti_Btn:setHoverable(0,255,0,255,255,255,255,255)
        Login_Noti_Btn:setOnClickCallback(function() Login_Noti_Panel:hideWithEffect(PanelShowType.Fade,250) end)

    --- Main Menu section ----
    
    Login_PlayOfflineBtn = Label:new()
    Login_PlayOfflineBtn:init(Login_GUIScriptingPtr,"Play Offline",0,0)
    Login_PlayOfflineBtn:setAlignment(TextAlginment.Center)
    Login_PlayOfflineBtn:setPos(TGUI_ScreenWidth/2 ,TGUI_ScreenHeight/2 - 50)
    Login_PlayOfflineBtn:setHoverable(0,255,0,255,255,255,255,255)
    Login_PlayOfflineBtn:setOnClickCallback(function()
        Login_showNotification("Play Offline is not supported yet !\nWill be implemented in the future ...","OK")
        end)

    Login_PlayOnlineBtn = Label:new()
    Login_PlayOnlineBtn:init(Login_GUIScriptingPtr,"Play Online",TGUI_ScreenWidth/2 ,TGUI_ScreenHeight/2 )
    Login_PlayOnlineBtn:setAlignment(TextAlginment.Center)
    Login_PlayOnlineBtn:setHoverable(0,255,0,255,255,255,255,255)
    Login_PlayOnlineBtn:setOnClickCallback(function() Client_Connect(ClientScriptingPtr) end)

    Login_ExitBtn = Label:new()
    Login_ExitBtn:init(Login_GUIScriptingPtr,"Exit",TGUI_ScreenWidth/2 ,TGUI_ScreenHeight/2 + 50)
    Login_ExitBtn:setAlignment(TextAlginment.Center)
    Login_ExitBtn:setHoverable(0,255,0,255,255,255,255,255)
    Login_ExitBtn:setOnClickCallback(function() os.exit() end)

    ---- TOS section -----
    local tosPanel = Panel:new()
    tosPanel:init(Login_GUIScriptingPtr,TGUI_ScreenWidth/2 - 225,TGUI_ScreenHeight/2 -150,450, 300)
    tosPanel:setAligment(0.5,0,5)
    tosPanel:setSizeStr("30%", "30%")
    tosPanel:setPosStr("50%", "50%")
    tosPanel:setVisible(false)

    local tosText = RTLabel:new()
    tosText:init(Login_GUIScriptingPtr,"This is a fan-made game based on \nTouhou project,many assets from other \ngames as concepts/placeholder,if you are \nOK with this prototype then hit \"Agree\" ",0,TGUI_ScreenHeight/2,tosPanel.ptr)
    tosText:setAlignment(TextAlginment.Center)
    tosText:setPosStr("50%","15%")

    local tosAgree = Label:new()
    tosAgree:init(Login_GUIScriptingPtr,"Agree",0,0,tosPanel.ptr)

    tosAgree:setPosStr("50%","80%")
    tosAgree:setAlignment(TextAlginment.Center)
    tosAgree:setHoverable(0,255,0,255,255,255,255,255)
    tosAgree:setOnClickCallback(function() tosPanel:hideWithEffect(PanelShowType.Fade,250)  end)

    tosPanel:showWithEffect(PanelShowType.Fade,250)

    ---- TOS section end

    -- local testEditBox = EditBox:new()
    -- testEditBox:init(Login_GUIScriptingPtr,200,50,200,50)

end

---@Description show Notification box
---@param msg string message
---@param btnText string
function Login_showNotification(msg,btnText)
    Login_Noti_Panel:showWithEffect(PanelShowType.Fade,250)
    Login_Noti_Msg:setText(msg)
    Login_Noti_Btn:setText(btnText)
    -- Login_Noti_Btn:setOnClickCallback(function()
    --     print("call back end ")
    --     Login_Noti_Panel:hideWithEffect(PanelShowType.Fade,2500)
    --     end)

end



print("kinda OK")