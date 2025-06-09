package.path = package.path .. ';../../Lua/system/GUI/?/?.lua;' .. ';../../Lua/system/GUI/widgets/?.lua;' .. ';../../Lua/system/Networking/?.lua;' .. ';../../Lua/TouhouTB/Home/?.lua;' .. ';../../Lua/system/event/?.lua;' .. ';../../Lua/TouhouTB/Home/Shop/?.lua;' .. ';../../Lua/TouhouTB/characters/?.lua;' .. ';../../Lua/?.lua;' .. './TouhouTB/characters/Common/?.lua;' .. './TouhouTB/characters/Patchy/?.lua;' .. ';../../Lua/TouhouTB/characters/Patchy/?.lua;' .. ';./TouhouTB/characters/Reimu/slots/?.lua;' .. ';../../Lua/TouhouTB/characters/Reimu/?.lua;' .. ';./TouhouTB/characters/Yukari/slots/?.lua;' .. ';../../Lua/TouhouTB/characters/Yukari/?.lua;' .. ';../../Lua/TouhouTB/?.lua' .. ';../../Lua/TouhouTB/characters/Meiling/?.lua;' .. ';../../Lua/TouhouTB/?.lua'

require "TGUI_Label"
require "TGUI_Panel"
require "TGUI_RTLabel" 
require "TGUI_Editbox"
require "TGUI_Picture"
require "clientSide"
require "clientWrapper"
require "homeOrderStrip"
require "LuaEventHandler"
require "Shop"
require "homeGlobal"

require "Reimu"
require "Patchouli"
require "Yukari"
require "Meiling"


HomeSceneHost = nil
-- HandlePacketTask = _G.HandlePacketTask

---@type pointer TGUIScriptingPtr
Home_GUIScriptingPtr = nil

---@type pointer ClientScriptingPtr
Home_ClientScriptingPtr = nil

---@type pointer ClientCharacterHandler
Home_ClientCharacterHandlerPtr = nil

---Notification
---@type Panel
Home_Noti_Panel = nil
---@type RTLabel
Home_Noti_Msg = nil
---@type Label
Home_Noti_Btn = nil

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

---@type Label
Main_ShopButton = nil

function HomeSceneInit(host,TGUIScriptingPtr,ClientScriptingPtr,ClientCharacterHandlerPtr)
    HomeSceneHost = host
    Home_GUIScriptingPtr = TGUIScriptingPtr
    Home_ClientScriptingPtr = ClientScriptingPtr
    Home_ClientCharacterHandlerPtr = ClientCharacterHandlerPtr

    if HomeSceneHost ~= nil then
        print("LoginHost is not nil")
    end
    if Home_GUIScriptingPtr ~= nil then
        print("Home_GUIScriptingPtr is not nil")
    end
    if Home_ClientScriptingPtr ~= nil then
        print("Home_ClientScriptingPtr is not nil")
    end

    --- Notification section ----
    Home_Noti_Panel = Panel:new()
    Home_Noti_Panel:init(Home_GUIScriptingPtr,TGUI_ScreenWidth/2 - 225,TGUI_ScreenHeight/2 -150,450, 300)
    print("init panel OK")
    Home_Noti_Panel:setAlignment(0.5,0.5)
    print("set aligment OK")
    Home_Noti_Panel:setSizeStr("30%", "25%")
    print("set size OK")
    Home_Noti_Panel:setPosStr("50%", "50%")
    print("set pos OK")
    Home_Noti_Panel:setVisible(false)
    print("set visible OK")
    Home_Noti_Msg = RTLabel:new()
    Home_Noti_Msg:init(Home_GUIScriptingPtr,"",0,0,Home_Noti_Panel.ptr)
    Home_Noti_Msg:setAlignment(TextAlginment.Center)
    Home_Noti_Msg:setPosStr("50%","20%")

    Home_Noti_Btn = Label:new()
    Home_Noti_Btn:init(Home_GUIScriptingPtr,"OK",0,0,Home_Noti_Panel.ptr)
    Home_Noti_Btn:setAlignment(TextAlginment.Center)
    Home_Noti_Btn:setPosStr("50%","75%")
    Home_Noti_Btn:setHoverable(0,255,0,255,255,255,255,255)
    Home_Noti_Btn:setOnClickCallback(function() 
        cpp_backToMenu(HomeSceneHost)    
    end)


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
    Main_SoulsLabel:setScale(0.9)
    Main_SoulsLabel:setPosStr("70%","5%")

    Main_SoulsValLabel = RTLabel:new()
    Main_SoulsValLabel:init(Home_GUIScriptingPtr,"?",0,0)
    Main_SoulsValLabel:setPosStr("78%","4.5%")
    Main_SoulsValLabel:setScale(0.9)
    Main_SoulsValLabel:setAlignment(TextAlginment.Right)

    Main_MonLabel = Label:new()
    Main_MonLabel:init(Home_GUIScriptingPtr,"Mon:",0,0)
    Main_MonLabel:setPosStr("85%","5%")

    Main_MonValLabel = Label:new()
    Main_MonValLabel:init(Home_GUIScriptingPtr,"?",0,0)
    Main_MonValLabel:setPosStr("93%","5%")
    Main_MonValLabel:setAlignment(TextAlginment.Right)

    Main_ShopButton = Label:new()
    Main_ShopButton:init(Home_GUIScriptingPtr,"Shop",0,0)
    Main_ShopButton:setPosStr("10%","80`%")
    Main_ShopButton:setAlignment(TextAlginment.Center)
    Main_ShopButton:setHoverable(0,255,0,255,255,255,255,255)
    InitShop(TGUIScriptingPtr)

    Main_ShopButton:setOnClickCallback(function()
        MenuPanels["Shop"](TGUIScriptingPtr)
        end)

    -- Tscheduler_addTask(5, function()
    --     Home_RequestUserlData()
    -- end)
    -- HomeMain_RequestDataLoop()
    Home_UpdateInfo()
end


---@Description request update money data
function Home_RequestUserlData()
end

function Home_UpdateInfo()
    Tscheduler_addTask(50, function()

        local id,pw, guid = Home_GetInfo(3)
        local tResp = -1 
        tResp = Client_SendData( Home_ClientScriptingPtr,CombinePackage("USERDATA", {id, pw, guid}))
        if tResp == 0 then
            Home_UpdateInfo()
            print("tResp " .. tResp)
        end
    end)
end

HomeMain_HandleTask = {}

---@Description get the code of other special ID
---@param packet Client_Packet
---@return number 
function HomeMain_GetOtherID(packet)
    local msg = packet.data
    -- print("msg is :" .. msg)
    for k,v in pairs(Home_OrderList) do
        if string.match(msg,v.firstStr) then
            if string.match(msg,v.secondStr) then
                return k
            end
        end
    end
    return Packet_OtherID.ID_INVALID
end

---@Description handle Non special packet
---@param host pointer instance of ClientScriptingManager
---@param packet Client_Packet
function HomeMain_HandleTask_OtherID(host, packet)
    local otherID = HomeMain_GetOtherID(packet)
    -- local msg = Login_StripMSG(packet.data,otherID)
    print("other id " .. otherID)
    if HomeMain_HandleStep2[otherID] ~= nil then
        HomeMain_HandleStep2[otherID](host,packet)
    end
end

---@Description loop for Client script
---@param host pointer instance of ClientScriptingManager
---@param packet Client_Packet
HandlePacketTask["home_main"] = function(host,packet)
    print("handle home packet task " .. packet.packetID)
    if HomeMain_HandleTask[packet.packetID] ~= nil then
        HomeMain_HandleTask[packet.packetID](ClientSide_Host,packet)
    else
        HomeMain_HandleTask_OtherID(host,packet)
    end
end

HomeMain_HandleStep2 = {}

---@Description handle USER_DATA_POS
---@param host pointer instance of ClientScriptingManager
---@param packet Client_Packet
HomeMain_HandleStep2[Packet_OtherID.USER_DATA_POS] = function(host,packet)
    local tData = Home_StripMSG(packet.data,Packet_OtherID.USER_DATA_POS)
    -- print(packet.data)

    local tD = SplitMessgae(tData,"|",3)
    local t_id,t_pw , t_guid = Home_GetInfo(3)
    -- print("td " .. tD[1])
    -- print("td " .. tD[2])
    -- print("td " .. tD[3])
    Main_MonValLabel:setText(tD[2])
    Main_SoulsValLabel:setText(Tag.color_TB_title .. tD[3] .. " " .. Tag.icon_soul .. Tag.color_close)
    -- print("HomeMain_HandleStep2 " .. Packet_OtherID.USER_DATA_POS)
end

---@Description handle USER_DATA_POS
---@param host pointer instance of ClientScriptingManager
---@param packet Client_Packet
HomeMain_HandleStep2[Packet_OtherID.USER_DATA_NEG] = function(host,packet)
    Main_MonValLabel:setText("!!!!!")
    Main_SoulsValLabel:setText("!!!!!")
end

HomeMain_HandleStep2[Packet_OtherID.CHARACTER_RES] = function(host,packet)
    print("HomeMain_HandleStep2[Packet_OtherID.CHARACTER_RES] called ")
    local tData = Home_StripMSG(packet.data,Packet_OtherID.CHARACTER_RES)
    -- print("get data" .. tData)
    local tD = SplitMessgae(tData,"|",1)
    S_Characters_Info[tD[1]] = tD[2]

    -- table.insert(S_Characters_Info,tD[1],tD[2])
    local t_charStats =  Client_ParseCharacterFromJson(host, tD[2])
    ClientCharacterHandler_fillData(Home_ClientCharacterHandlerPtr,tD[1],t_charStats)

    print("recieve " .. tD[1] .. " !!!!!!!!!!!!!!!!?????????????" )
    -- print("number of S_Characters_Info |ASSIGN| " .. #S_Characters_Info)
end

HomeMain_HandleStep2[Packet_OtherID.CHARACTER_RES_DONE] = function(host,packet)
    print("character res done")
    print("check Data")
    local tData = Home_StripMSG(packet.data,Packet_OtherID.CHARACTER_RES_DONE)

    local tD = SplitMessgae(tData,"|",1)
    local totalNum = tonumber(tD[1])

    print("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<totalNum " .. totalNum .. "/" .. GetTableSize(S_Characters_Info))
    while GetTableSize(S_Characters_Info) ~= totalNum do
        local  tResp = Client_SendData(Home_ClientScriptingPtr,"|REQUEST_CHARACTERLIST|")
        while tResp == 0 do
            tResp = Client_SendData(Home_ClientScriptingPtr,"|REQUEST_CHARACTERLIST|")
        end
    end

    -- print("number of S_Characters_Info " .. #S_Characters_Info)

    Shop_CharacterShop = _G.Shop_CharacterShop
    ClientCharacterHandler_Host = _G.ClientCharacterHandler_Host

    for k,v in pairs(S_Characters_Info) do
        if k == "S_Reimu" then
            print("found Reimu")
            Shop_CharacterTable["Reimu"] = Reimu:new()
            local t = ClientCharacterHandler_getCharacterData(Home_ClientCharacterHandlerPtr,k)
            Shop_CharacterTable["Reimu"]:initNonCB(ClientCharacterHandler_Host,"Reimu",t)

        elseif k == "S_Patchouli" then
            print("found Patchouli")
            Shop_CharacterTable["Patchouli"] = Patchouli:new()
            local t = ClientCharacterHandler_getCharacterData(Home_ClientCharacterHandlerPtr,k)
            Shop_CharacterTable["Patchouli"]:initNonCB(ClientCharacterHandler_Host,"Patchouli",t)
        elseif k == "S_Yukari" then
            print("found Yukari")
            Shop_CharacterTable["Yukari"] = Yukari:new()
            local t = ClientCharacterHandler_getCharacterData(Home_ClientCharacterHandlerPtr,k)
            Shop_CharacterTable["Yukari"]:initNonCB(ClientCharacterHandler_Host,"Yukari",t)

        elseif k == "S_Meiling" then
            print("found Meiling")
            Shop_CharacterTable["Meiling"] = Meiling:new()
            local t = ClientCharacterHandler_getCharacterData(Home_ClientCharacterHandlerPtr,k)
            Shop_CharacterTable["Meiling"]:initNonCB(ClientCharacterHandler_Host,"Meiling",t)
        end
    end

    -- table.sort(Shop_CharacterTable)
    local x_offset = 130
    local count = 0

    table.sort(Shop_CharacterTable, function(a,b) 
        return a.name < b.name 
        end)

    for k,v in pairs(Shop_CharacterTable) do
        print(k,v.dyobj)
    end

    for k,v in pairs(Shop_CharacterTable) do
        Shop_CharacterShop:addCharPanel(Home_GUIScriptingPtr, count * x_offset, 10, 125,250, v.panelPath,v.name,v.price)
        count = count + 1
    end

    -- print("check end ")

end

---@Description request update money data
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

---@Description extract the message from the packet
---@param msg string data want to extract
---@param otherID number ( to select which part need to be strip)
function Home_StripMSG(msg,otherID)
    -- print("at least it here " .. otherID)
    return string.sub(msg,string.len(Home_OrderList[otherID].firstStr) + 1,string.len(msg) - string.len(Home_OrderList[otherID].secondStr))
end

HomeMain_Tasks = {}

---@Description Backup update function
function HomeMain_RequestDataLoop()
    Tscheduler_addTask(300, function()
        Home_RequestUserlData()
        HomeMain_RequestDataLoop()
    end)
end

---- basic network handling 
Network_CommonTask = {}
---@Description handle packet when connected
---@param host pointer instance of ClientScriptingManager
---@param packet Client_Packets
HandlePacketTask["common"] = function(host,packet)
    -- print("recive packet  >>>> " .. packet.packetID)
    if Network_CommonTask[packet.packetID] ~= nil then
        Network_CommonTask[packet.packetID](ClientSide_Host,packet)
    end
end

Network_CommonTask[PacketID.ID_CONNECTION_ATTEMPT_FAILED] = function(host,packet)
    print("ID_CONNECTION_ATTEMPT_FAILED")
    -- Client_Connected = false
    Home_showNotification("Failed to connect !!!!","OK")
end

Network_CommonTask[PacketID.ID_DISCONNECTION_NOTIFICATION] = function(host,packet)
    Home_showNotification("Disconnection from server !","OK")
    -- Client_Connected = false
end

Network_CommonTask[PacketID.ID_CONNECTION_LOST] = function(host,packet)
    Home_showNotification("Connection lost !","OK")
    Client_Connected = false
end

function Home_showNotification(msg,btnText)
    Home_Noti_Panel:showWithEffect(PanelShowType.Fade,250)
    Home_Noti_Msg:setText(msg)
    Home_Noti_Btn:setText(btnText)
    Home_Noti_Panel.visible = true
end