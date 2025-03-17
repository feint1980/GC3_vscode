
package.path = package.path .. ';./Assets/Lua/system/GUI/?/?.lua;' .. ';./Assets/Lua/system/GUI/widgets/?.lua;' .. ';./Assets/Lua/system/Networking/?.lua;' .. ';./Assets/Lua/Login/?.lua;'

-- require "tguiScript"

require "TGUI_Label"
require "TGUI_Panel"
require "TGUI_RTLabel" 
require "TGUI_Editbox"
require "clientSide"
require "loginStripOrder"
require "clientWrapper"

print("login scene run\n")

---@class TGUIScriptingPtr
---@class ClientScriptingPtr

--- Global variables section start ----

LoginHost = nil

---@type pointer TGUIScriptingPtr
Login_GUIScriptingPtr = nil

---@type pointer ClientScriptingPtr
Login_ClientScriptingPtr = nil


--- Main Menu
---@type Label
Login_PlayOfflineBtn = nil
---@type Label
Login_PlayOnlineBtn = nil
---@type Label
Login_ExitBtn = nil


---Notification
---@type Panel
Login_Noti_Panel = nil
---@type RTLabel
Login_Noti_Msg = nil
---@type Label
Login_Noti_Btn = nil

---Login Panel
---@type Panel
Login_LoginPanel = nil
---@type Label
Login_IDLabel = nil
---@type EditBox
Login_IDEditBox = nil
---@type Label
Login_PWLabel = nil
---@type EditBox
Login_PWEditBox = nil
---@type Label
Login_LoginBtn = nil
---@type Label
Login_CancelBtn = nil
---@type Label
Login_LGRegisterBtn = nil

---Register Panel
---@type Panel
Login_RegisterPanel = nil
---@type Label
Login_RegisterIDLabel = nil
---@type EditBox
Login_RegisterIDEditBox = nil
---@type Label
Login_RegisterPWLabel = nil
---@type EditBox
Login_RegisterPWEditBox = nil
---@type Label
Login_RegisterPW2Label = nil
---@type EditBox
Login_RegisterPW2EditBox = nil
---@type Label
Login_RegisterKeyLabel = nil
---@type EditBox
Login_RegisterKeyEditBox = nil
---@type Label
Login_RegisterBtn = nil
---@type Label
Login_RegisterCancelBtn = nil


--- Global variables section end ----

---@Description combines packet
---@param type string type of packet to wrap
---@param list table data to wrap
function Login_CombinePackage(type,list)
    ----
    local returnValue = "|"
    returnValue = returnValue .. type .. "_REQUEST|" 
    for i = 1, #list do
        returnValue = returnValue .. list[i] .. "|"
    end
    returnValue = returnValue .. type .. "_END_REQUEST|"
    return returnValue
end



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
    Login_PlayOnlineBtn:setOnClickCallback(
        function()
        if Client_Connected == false then
            Client_Connect(ClientScriptingPtr)
            Login_showNotification("Connecting ...","")
        else
            Login_LoginPanel:showWithEffect(PanelShowType.Fade,250)
        end

        end)

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


    --- Login Panel section
    Login_LoginPanel = Panel:new()
    Login_LoginPanel:init(Login_GUIScriptingPtr,0,0,600,400)
    Login_LoginPanel:setAligment(0.5,0.5)
    Login_LoginPanel:setSizeStr("30%", "30%")
    Login_LoginPanel:setPosStr("50%", "50%")
    Login_LoginPanel:setVisible(false)

    local login_title = Label:new()
    login_title:init(Login_GUIScriptingPtr,"Login",0,0,Login_LoginPanel.ptr)
    login_title:setAlignment(TextAlginment.Center)
    login_title:setPosStr("50%","10%")
    
    Login_IDLabel = Label:new()
    Login_IDLabel:init(Login_GUIScriptingPtr,"ID",0,0,Login_LoginPanel.ptr)
    Login_IDLabel:setPosStr("7%","30%")

    Login_IDEditBox = EditBox:new()
    Login_IDEditBox:init(Login_GUIScriptingPtr,0,0,200,40,Login_LoginPanel.ptr)
    Login_IDEditBox:setPosStr("30%","30%")
    Login_IDEditBox:setSizeStr("60%","10%")

    Login_PWLabel = Label:new()
    Login_PWLabel:init(Login_GUIScriptingPtr,"Password",0,0,Login_LoginPanel.ptr)
    Login_PWLabel:setPosStr("7%","50%")

    Login_PWEditBox = EditBox:new()
    Login_PWEditBox:init(Login_GUIScriptingPtr,0,0,200,40,Login_LoginPanel.ptr)
    Login_PWEditBox:setPWCharacter("*")
    Login_PWEditBox:setPosStr("30%","50%")
    Login_PWEditBox:setSizeStr("60%","10%")

    Login_LoginBtn = Label:new()
    Login_LoginBtn:init(Login_GUIScriptingPtr,"Login",0,0,Login_LoginPanel.ptr)
    Login_LoginBtn:setPosStr("25%","75%")
    Login_LoginBtn:setAlignment(TextAlginment.Center)
    Login_LoginBtn:setHoverable(0,255,0,255,255,255,255,255)
    Login_LoginBtn:setOnClickCallback(function()
        
        if Client_Connected == true then
            Client_SendData(Login_ClientScriptingPtr, Login_CombinePackage("LOGIN", { Login_IDEditBox:getText(), Login_PWEditBox:getText()}))
        end

        print("setOnClickCallback send data : ")
        print(Login_CombinePackage("LOGIN", { Login_IDEditBox:getText(), Login_PWEditBox:getText()}))
    end)


    Login_LGRegisterBtn = Label:new()
    Login_LGRegisterBtn:init(Login_GUIScriptingPtr,"Register",0,0,Login_LoginPanel.ptr)
    Login_LGRegisterBtn:setPosStr("50%","75%")
    Login_LGRegisterBtn:setAlignment(TextAlginment.Center)
    Login_LGRegisterBtn:setHoverable(0,255,0,255,255,255,255,255)
    Login_LGRegisterBtn:setOnClickCallback(function()
        Login_LoginPanel:hideWithEffect(PanelShowType.Fade,250)
        Login_RegisterPanel:showWithEffect(PanelShowType.Fade,250)

    end)

    Login_CancelBtn = Label:new()
    Login_CancelBtn:init(Login_GUIScriptingPtr,"Cancel",0,0,Login_LoginPanel.ptr)
    Login_CancelBtn:setPosStr("75%","75%")
    Login_CancelBtn:setAlignment(TextAlginment.Center)
    Login_CancelBtn:setHoverable(0,255,0,255,255,255,255,255)
    Login_CancelBtn:setOnClickCallback(function()
        Login_LoginPanel:hideWithEffect(PanelShowType.Fade,250)
    end)

    --- Register Panel section
    Login_RegisterPanel = Panel:new()
    Login_RegisterPanel:init(Login_GUIScriptingPtr,0,0,600,400)
    Login_RegisterPanel:setAligment(0.5,0.5)
    Login_RegisterPanel:setSizeStr("30%", "35%")
    Login_RegisterPanel:setPosStr("50%", "50%")
    Login_RegisterPanel:setVisible(false)

    local register_title = Label:new()
    register_title:init(Login_GUIScriptingPtr,"Register Account",0,0,Login_RegisterPanel.ptr)
    register_title:setAlignment(TextAlginment.Center)
    register_title:setPosStr("50%","5%")

    Login_RegisterIDLabel = Label:new()
    Login_RegisterIDLabel:init(Login_GUIScriptingPtr,"ID",0,0,Login_RegisterPanel.ptr)
    Login_RegisterIDLabel:setPosStr("6%","20%")

    Login_RegisterIDEditBox = EditBox:new()
    Login_RegisterIDEditBox:init(Login_GUIScriptingPtr,0,0,200,40,Login_RegisterPanel.ptr)
    Login_RegisterIDEditBox:setPosStr("30%","20%")
    Login_RegisterIDEditBox:setSizeStr("60%","10%")

    Login_PWLabel = Label:new()
    Login_PWLabel:init(Login_GUIScriptingPtr,"Password",0,0,Login_RegisterPanel.ptr)
    Login_PWLabel:setPosStr("6%","35%")

    Login_RegisterPWEditBox = EditBox:new()
    Login_RegisterPWEditBox:init(Login_GUIScriptingPtr,0,0,200,40,Login_RegisterPanel.ptr)
    Login_RegisterPWEditBox:setPWCharacter("*")
    Login_RegisterPWEditBox:setPosStr("30%","35%")
    Login_RegisterPWEditBox:setSizeStr("60%","10%")

    Login_RegisterPW2Label = Label:new()
    Login_RegisterPW2Label:init(Login_GUIScriptingPtr,"Confirm PW",0,0,Login_RegisterPanel.ptr)
    Login_RegisterPW2Label:setPosStr("6%","50%")

    Login_RegisterPW2EditBox = EditBox:new()
    Login_RegisterPW2EditBox:init(Login_GUIScriptingPtr,0,0,200,40,Login_RegisterPanel.ptr)
    Login_RegisterPW2EditBox:setPWCharacter("*")
    Login_RegisterPW2EditBox:setPosStr("30%","50%")
    Login_RegisterPW2EditBox:setSizeStr("60%","10%")

    Login_RegisterKeyLabel = Label:new()
    Login_RegisterKeyLabel:init(Login_GUIScriptingPtr,"Key",0,0,Login_RegisterPanel.ptr)
    Login_RegisterKeyLabel:setPosStr("6%","65%")

    Login_RegisterKeyEditBox = EditBox:new()
    Login_RegisterKeyEditBox:init(Login_GUIScriptingPtr,0,0,200,40,Login_RegisterPanel.ptr)    -- TODO: implement key input for registration
    Login_RegisterKeyEditBox:setPosStr("30%","65%")
    Login_RegisterKeyEditBox:setSizeStr("60%","10%")


    Login_RegisterBtn = Label:new()
    Login_RegisterBtn:init(Login_GUIScriptingPtr,"Register",0,0,Login_RegisterPanel.ptr)
    Login_RegisterBtn:setPosStr("25%","85%")
    Login_RegisterBtn:setAlignment(TextAlginment.Center)
    Login_RegisterBtn:setHoverable(0,255,0,255,255,255,255,255)
    Login_RegisterBtn:setOnClickCallback(function()
        Login_RegisterCall(host)
    end)


    Login_RegisterCancelBtn = Label:new()
    Login_RegisterCancelBtn:init(Login_GUIScriptingPtr,"Cancel",0,0,Login_RegisterPanel.ptr)
    Login_RegisterCancelBtn:setPosStr("75%","85%")
    Login_RegisterCancelBtn:setAlignment(TextAlginment.Center)
    Login_RegisterCancelBtn:setHoverable(0,255,0,255,255,255,255,255)
    Login_RegisterCancelBtn:setOnClickCallback(function()
        Login_RegisterPanel:hideWithEffect(PanelShowType.Fade,250)
    end)


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



Login_HandleTask = {}
---@Description handle packet when connected
---@param host pointer instance of ClientScriptingManager
---@param packet Client_Packet


HandlePacketTask["main"] = function(host,packet)

    if Login_HandleTask[packet.packetID] ~= nil then
        Login_HandleTask[packet.packetID](ClientSide_Host,packet)
    else
        Login_HandleTask_OtherID(host,packet)
    end
end

Login_HandleTask[PacketID.ID_CONNECTION_REQUEST_ACCEPTED] = function(host,packet)
    print("ID_CONNECTION_REQUEST_ACCEPTED riu ko bro ?")

    Login_Noti_Panel:hideWithEffect(PanelShowType.Fade,100)
    Client_Connected = true

    Login_LoginPanel:showWithEffect(PanelShowType.Fade,250)
end

Login_HandleTask[PacketID.ID_CONNECTION_ATTEMPT_FAILED] = function(host,packet)
    print("ID_CONNECTION_ATTEMPT_FAILED")
    Client_Connected = false
    Login_Noti_Msg:setText("Failed to connect !!!!")
    Login_Noti_Btn:setText("OK")

    -- Login_Noti_Btn:setOnClickCallback(function() Login_Noti_Panel:hideWithEffect(PanelShowType.Fade,250) end)
end


Login_HandleTask[PacketID.ID_DISCONNECTION_NOTIFICATION] = function(host,packet)
    print("ID_DISCONNECTION_NOTIFICATION")
    Client_Connected = false

end

Login_HandleTask[PacketID.ID_CONNECTION_LOST] = function(host,packet)
    print("ID_CONNECTION_LOST")
    Client_Connected = false
end

Login_HandleStep2 = {}



function Login_HandleTask_OtherID(host, packet)
    local otherID = Login_GetOtherID(packet)
    -- local msg = Login_StripMSG(packet.data,otherID)
    print("other id " .. otherID)
    if Login_HandleStep2[otherID] ~= nil then
        Login_HandleStep2[otherID](host,packet)
    end
    -- print("msg stripped: "..msg)
end

--- Handle msg when login failed
Login_HandleStep2[Packet_OtherID.ID_LOGIN_NEG] = function(host,packet)
    print("ID_LOGIN_NEG")
    Login_Noti_Msg:setText( StripMSG(packet.data,Packet_OtherID.ID_LOGIN_NEG))
    Login_Noti_Btn:setText("OK")
    Login_Noti_Panel:showWithEffect(PanelShowType.Fade,250)
    
end

--- Handle msg when login OK
Login_HandleStep2[Packet_OtherID.ID_LOGIN_POS] = function(host,packet)
    print("ID_LOGIN_POS")
    local tData = StripMSG(packet.data,Packet_OtherID.ID_LOGIN_POS)

    local tD = SplitMessgae(tData,"|",2)
    -- for i,v in ipairs(tD) do
    --     print(tD[i])
    -- end

    cpp_switchScene(LoginHost,tD[1],tD[2],tD[3])
    
end

Login_HandleStep2[Packet_OtherID.ID_REGISTER_NEG] = function(host,packet)
    print("ID_REGISTER_NEG")
    Login_Noti_Msg:setText( StripMSG(packet.data,Packet_OtherID.ID_REGISTER_NEG))
    Login_Noti_Btn:setText("OK")
    Login_Noti_Panel:showWithEffect(PanelShowType.Fade,250)
    
end


Login_HandleStep2[Packet_OtherID.ID_REGISTER_POS] = function(host,packet)
    print("ID_REGISTER_POS")
    Login_Noti_Msg:setText( StripMSG(packet.data,Packet_OtherID.ID_REGISTER_POS))
    Login_Noti_Btn:setText("OK")
    Login_RegisterPanel:hideWithEffect(PanelShowType.Fade,250)
    Login_Noti_Panel:showWithEffect(PanelShowType.Fade,250)

end


function Login_CheckValid(info)
    local size = string.len(info)
    if size  < 6  or size > 32 then
        return false
    end
end

function Login_RegisterCall(host)
    local id = Login_RegisterIDEditBox:getText()
    local pw = Login_RegisterPWEditBox:getText()
    local pw2 = Login_RegisterPW2EditBox:getText()
    local tKey = Login_RegisterKeyEditBox:getText()

    if Login_CheckValid(id) == false then
        Login_showNotification("Invalid ID","OK")
        return
    end

    if Login_CheckValid(pw) == false then
        Login_showNotification("Invalid Password","OK")
        return
    else 
        if pw ~= pw2 then
            Login_showNotification("Password not match","OK")
            return
        end
    end

    if string.len(tKey) ~= 12 then
        Login_showNotification("Invalid Key Format !","OK")
        return
    end

    Client_SendData(Login_ClientScriptingPtr,Login_CombinePackage("REGISTER",{id,pw,tKey}))
end

---@Description get the code of other special ID
---@param packet Client_Packet
---@return number 
function Login_GetOtherID(packet)
    local msg = packet.data
    print("msg is :" .. msg)

    for k,v in pairs(OrderList) do
        if string.match(msg,v.firstStr) then
            if string.match(msg,v.secondStr) then
                return k
            end
        end
    end
    
    return Packet_OtherID.ID_INVALID
end


---@Description extract the message from the packet
---@param msg string data want to extract
---@param otherID number ( to select which part need to be strip)
function StripMSG(msg,otherID)

    print("at least it here " .. otherID)

    -- print( OrderList[Packet_OtherID.ID_LOGIN_NEG].firstStr)
    return string.sub(msg,string.len(OrderList[otherID].firstStr) + 1,string.len(msg) - string.len(OrderList[otherID].secondStr))

end





print("kinda OK")