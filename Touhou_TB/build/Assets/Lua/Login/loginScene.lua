
package.path = package.path .. ';./Assets/Lua/system/GUI/?/?.lua;' .. ';./Assets/Lua/system/GUI/widgets/?.lua;' 

-- require "tguiScript"

require "TGUI_Label"
require "TGUI_Panel"
require "TGUI_RTLabel" 
require "TGUI_Editbox"

print("login scene run\n")

LoginHost = nil
Login_GUIScriptingPtr = nil


-- TestLabel = nil

function LoginSceneInit(host,TGUIScriptingPtr)

    LoginHost = host
    Login_GUIScriptingPtr = TGUIScriptingPtr
    if LoginHost ~= nil then
        print("LoginHost is not nil")
    end

    if Login_GUIScriptingPtr ~= nil then
        print("Login_GUIScriptingPtr is not nil")
    end



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

    local testEditBox = EditBox:new()
    testEditBox:init(Login_GUIScriptingPtr,200,50,200,50)

end


print("kinda OK")