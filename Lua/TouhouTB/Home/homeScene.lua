package.path = package.path .. ';../../Lua/system/GUI/?/?.lua;' .. ';../../Lua/system/GUI/widgets/?.lua;' .. ';../../Lua/system/Networking/?.lua;' .. ';../../Lua/TouhouTB/Home/?.lua;' .. ';../../Lua/system/event/?.lua;' .. ';../../Lua/TouhouTB/Shop/?.lua;'

require "TGUI_Label"
require "TGUI_Panel"
require "TGUI_RTLabel" 
require "TGUI_Editbox"
require "TGUI_Picture"
require "clientSide"
require "clientWrapper"
require "homeOrderStrip"
require "LuaEventHandler"

HomeSceneHost = nil

-- HandlePacketTask = _G.HandlePacketTask

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

---@type Label
Main_ShopButton = nil

MenuPanels = {}

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
    if Home_ClientScriptingPtr ~= nil then
        print("Home_ClientScriptingPtr is not nil")
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
    Main_SoulsValLabel:setPosStr("78%","5%")
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
    Main_ShopButton:setOnClickCallback(function() print("dadata") end)

    Tscheduler_addTask(5, function()
        Home_RequestUserlData()
    end)
    HomeMain_RequestDataLoop()
end

HomeMain_HandleTask = {}

---@Description get the code of other special ID
---@param packet Client_Packet
---@return number 
function HomeMain_GetOtherID(packet)
    local msg = packet.data
    print("msg is :" .. msg)
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
    print("td " .. tD[1])
    print("td " .. tD[2])
    print("td " .. tD[3])
    Main_MonValLabel:setText(tD[2])
    Main_SoulsValLabel:setText(tD[3])
    print("HomeMain_HandleStep2 " .. Packet_OtherID.USER_DATA_POS)
end

---@Description handle USER_DATA_POS
---@param host pointer instance of ClientScriptingManager
---@param packet Client_Packet
HomeMain_HandleStep2[Packet_OtherID.USER_DATA_NEG] = function(host,packet)
    Main_MonValLabel:setText("!!!!!")
    Main_SoulsValLabel:setText("!!!!!")
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
    print("at least it here " .. otherID)
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