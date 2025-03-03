
package.path = package.path .. ';./Assets/Lua/system/GUI/?/?.lua;' .. ';./Assets/Lua/system/GUI/widgets/?.lua;' 

require "TGUI_Label"

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

    local testLabel = Label:new()
    testLabel:init(Login_GUIScriptingPtr,"testdsadasdsadsadsad",0,TGUI_ScreenHeight/2)
    testLabel:setAlignment(TextAlginment.Center)
    testLabel:setPosStr("50%",TGUI_ScreenHeight/2)

    -- local testLabel = Label:new()

    -- testLabel:init(Login_GUIScriptingPtr,"test",0,0)

end







print("kinda OK")