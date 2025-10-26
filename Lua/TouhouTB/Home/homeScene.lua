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
require "Nexus"
require "Formation"
require "homeGlobal"
require "Arena"

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

---@type pointer ControlHandlerPtr
Home_ControlHandlerPtr = nil

--@type pointer SkillHandler
Home_SkillHandlerPtr = nil

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

---@type Label
Main_NexusButton = nil

---@type Label
Main_FormationButton = nil

---@type Label
Main_ArenaButton = nil


local h_id = ""
local h_pw = ""
local h_guid = ""


function HomeSceneInit(host,TGUIScriptingPtr,ClientScriptingPtr,ClientCharacterHandlerPtr, SkillHandlerPtr, ControlHandlerPtr)
    HomeSceneHost = host
    Home_GUIScriptingPtr = TGUIScriptingPtr
    Home_ClientScriptingPtr = ClientScriptingPtr
    Home_ClientCharacterHandlerPtr = ClientCharacterHandlerPtr
    Home_SkillHandlerPtr = SkillHandlerPtr
    Home_ControlHandlerPtr = ControlHandlerPtr


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
    Home_Noti_Panel:setAlignment(0.5,0.5)
    Home_Noti_Panel:setSizeStr("30%", "25%")
    Home_Noti_Panel:setPosStr("50%", "50%")
    Home_Noti_Panel:setVisible(false)
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
        Home_Noti_Panel:hideWithEffect(PanelShowType.Fade,250)
        --cpp_backToMenu(HomeSceneHost)    
    end)

    Home_Noti_Panel:hideWithEffect(PanelShowType.Fade,250)

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

    --- Shop Init
    Main_ShopButton = Label:new()
    Main_ShopButton:init(Home_GUIScriptingPtr,"Shop",0,0)
    Main_ShopButton:setPosStr("10%","80`%")
    Main_ShopButton:setAlignment(TextAlginment.Center)
    Main_ShopButton:setHoverable(0,255,0,255,255,255,255,255)
    InitShop(TGUIScriptingPtr)

    Main_ShopButton:setOnClickCallback(function()
        MenuPanels["Shop"](TGUIScriptingPtr)
        end)

    --- Nexus Init
    Main_NexusButton = Label:new()
    Main_NexusButton:init(Home_GUIScriptingPtr,"Spirit Nexus",0,0)
    Main_NexusButton:setPosStr("65%","15%")
    Main_NexusButton:setAlignment(TextAlginment.Center)
    Main_NexusButton:setHoverable(0,255,0,255,255,255,255,255)

    InitNexus(TGUIScriptingPtr)
    Main_NexusButton:setOnClickCallback(function()
        MenuPanels["Nexus"](TGUIScriptingPtr)
        end)

        
    --- Formation Init
    Main_FormationButton = Label:new()
    Main_FormationButton:init(Home_GUIScriptingPtr,"Formation",0,0)
    Main_FormationButton:setPosStr("75%","15%")
    Main_FormationButton:setAlignment(TextAlginment.Center)
    Main_FormationButton:setHoverable(0,255,0,255,255,255,255,255)
    InitFormationMenu(TGUIScriptingPtr)
    Main_FormationButton:setOnClickCallback(function()
        MenuPanels["Formation"](TGUIScriptingPtr)
        end)

    --- Arena Init
    InitArenaMenu(TGUIScriptingPtr)
    Main_ArenaButton = Label:new()
    Main_ArenaButton:init(Home_GUIScriptingPtr,"Arena",0,0)
    Main_ArenaButton:setPosStr("85%","80%")
    Main_ArenaButton:setAlignment(TextAlginment.Center)
    Main_ArenaButton:setHoverable(0,255,0,255,255,255,255,255)
    InitArenaMenu(TGUIScriptingPtr)
    Main_ArenaButton:setOnClickCallback(function()
        MenuPanels["Arena"](TGUIScriptingPtr)
        end)

    Home_UpdateInfo()
    Home_RequestSkillsStats()
    Home_RequestOwnedCharacterList()
    Home_RequestFormations()


    print("All done, ping is ")
    local ping = ClientGetPing(ClientScriptingPtr)
    print("ping is " .. ping)
end

function Home_UpdateInfo()
    local id,pw, guid = Home_GetInfo(3)
    SendRequest(PacketChannel.UserChannel, UserResponse.MainInfo, {id, pw, guid}, 5, 0.25)
    h_id = id
    h_pw = pw
    h_guid = guid
    MainInfo.id = id
    MainInfo.guid = guid
    MainInfo.pw = pw
end

function Home_RequestSkillsStats()
    SendRequest(PacketChannel.UserChannel, UserResponse.SkillInfo, {h_guid, "request"}, 5, 1.0)
end

function Home_RequestOwnedCharacterList()
    NexusRequestUserCharacterList(h_id,h_guid)
end

function Home_RequestFormations()
    SendRequest(PacketChannel.FormationChannel, FormationResponse.Formation_Request, {MainInfo.guid, MainInfo.id,"request"}, 5, 1.2,0.25)

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

---@Description loop for Client script
---@param host pointer instance of ClientScriptingManager
---@param packet Client_Packet
HandlePacketTask["home_main"] = function(host,packet)
    print("handle home packet task " .. packet.packetID)
    if HomeMain_HandleTask[packet.packetID] ~= nil then
        HomeMain_HandleTask[packet.packetID](ClientSide_Host,packet)
    end
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
    Home_Noti_Btn:setOnClickCallback(function()
        Home_Noti_Panel:hideWithEffect(PanelShowType.Fade,250)
        cpp_backToMenu(HomeSceneHost) 
        end)
    Home_showNotification("Failed to connect !!!!","OK")

end

Network_CommonTask[PacketID.ID_DISCONNECTION_NOTIFICATION] = function(host,packet)
    Home_Noti_Btn:setOnClickCallback(function()
        Home_Noti_Panel:hideWithEffect(PanelShowType.Fade,250)
        cpp_backToMenu(HomeSceneHost) 
        end)
    Home_showNotification("Disconnection from server !","OK")

    -- Client_Connected = false
end

Network_CommonTask[PacketID.ID_CONNECTION_LOST] = function(host,packet)
    Home_Noti_Btn:setOnClickCallback(function()
        Home_Noti_Panel:hideWithEffect(PanelShowType.Fade,250)
        cpp_backToMenu(HomeSceneHost) 
        end)
    Home_showNotification("Connection lost !","OK")

    Client_Connected = false
end

function Home_showNotification(msg,btnText)
    Home_Noti_Panel:showWithEffect(PanelShowType.Fade,250)
    Home_Noti_Msg:setText(msg)
    Home_Noti_Btn:setText(btnText)
    Home_Noti_Panel.visible = true
end

ClientMessageHandling[PacketChannel.UserChannel][UserResponse.MainInfo] = function(host,data, guid)

    local t_id, mon, souls, t_guid = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|([^|]+)|$")
    if t_id == nil or mon == nil or souls == nil or t_guid == nil then
        print("Ke3 F3i117 exception (PacketChannel.UserChannel][UserResponse.MainInfo)")
        return
    end
    -- print("check account " .. t_id .. " " .. mon .. " " .. souls .. " " .. t_guid)
    Main_MonValLabel:setText(mon)
    Main_SoulsValLabel:setText(Tag.color_TB_title .. souls .. " " .. Tag.icon_soul .. Tag.color_close)
end

ClientMessageHandling[PacketChannel.ShopChannel][ShopResponse.ShopCharacterInfo_Begin] = function(host,data, guid)
    -- print("Character request result begin")
    -- clear all metadata tables
    for k,v in pairs(S_Characters_Info) do
        S_Characters_Info[k] = nil
    end
end

ClientMessageHandling[PacketChannel.ShopChannel][ShopResponse.ShopCharacterInfo_Data] = function(host,data, guid)

    local t_name, t_data, isOwned = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|$") 

    if t_name == nil or t_data == nil or isOwned == nil then
        print("Ke3 F3i117 exception (PacketChannel.ShopChannel][ShopResponse.ShopCharacterInfo_Data)")
        return
    end

    S_Characters_Info[t_name] = Characters_Info:new()
    
    S_Characters_Info[t_name]:init(t_data, isOwned)

    -- print(t_name .. " " .. isOwned)

    print("character " .. t_name .. " is owned " .. isOwned)

    if isOwned == "true" then
        S_Characters_Info[t_name].isOwned = true
    else
        S_Characters_Info[t_name].isOwned = false
    end

    -- print("table check ")
    -- if S_Characters_Info[t_name].isOwned then 
    --     print(t_name .. " true")
    -- else
    --     print(t_name .. " false")
    -- end

    local t_charStats =  Client_ParseCharacterFromJson(host, t_data)
    ClientCharacterHandler_fillData(Home_ClientCharacterHandlerPtr, "Shop",t_name,t_charStats)
end

local function sortTableByName(a,b)
    print("comparing " .. a.ID .. " and " .. b.ID)
    return a.ID < b.ID
end

ClientMessageHandling[PacketChannel.ShopChannel][ShopResponse.ShopCharacterInfo_End] = function(host,data, guid)

    -- print("Character request result end")
    local t_countStr = string.sub(data, 2, string.len(data) - 1)
    local t_count = tonumber(t_countStr)
    if t_count == GetTableSize(S_Characters_Info) then
        -- print("Character request result end success")
        for k,v in pairs(S_Characters_Info) do
            if k == "S_Reimu" then
                print("found Reimu")
                Shop_CharacterTable["S_Reimu"] = Reimu:new()
                local t = ClientCharacterHandler_getCharacterData(Home_ClientCharacterHandlerPtr, "Shop",k)
                Shop_CharacterTable["S_Reimu"]:initNonCB(Home_ClientCharacterHandlerPtr,"Shop","S_Reimu",t)
                Shop_CharacterTable["S_Reimu"].isOwned =  v.isOwned
            elseif k == "S_Patchouli" then
                print("found Patchouli")
                Shop_CharacterTable["S_Patchouli"] = Patchouli:new()
                local t = ClientCharacterHandler_getCharacterData(Home_ClientCharacterHandlerPtr,"Shop",k)
                Shop_CharacterTable["S_Patchouli"]:initNonCB(Home_ClientCharacterHandlerPtr,"Shop","S_Patchouli",t)
                Shop_CharacterTable["S_Patchouli"].isOwned =  v.isOwned
            elseif k == "S_Yukari" then
                print("found Yukari")
                Shop_CharacterTable["S_Yukari"] = Yukari:new()
                local t = ClientCharacterHandler_getCharacterData(Home_ClientCharacterHandlerPtr, "Shop",k)
                Shop_CharacterTable["S_Yukari"]:initNonCB(Home_ClientCharacterHandlerPtr,"Shop","S_Yukari",t)
                Shop_CharacterTable["S_Yukari"].isOwned =  v.isOwned
            elseif k == "S_Meiling" then
                print("found Meiling")
                Shop_CharacterTable["S_Meiling"] = Meiling:new()
                local t = ClientCharacterHandler_getCharacterData(Home_ClientCharacterHandlerPtr, "Shop",k)
                Shop_CharacterTable["S_Meiling"]:initNonCB(Home_ClientCharacterHandlerPtr,"Shop","S_Meiling",t)
                Shop_CharacterTable["S_Meiling"].isOwned =  v.isOwned
            end
        end

        --- Remove this after real request done 
        -- for k,v in pairs(Shop_CharacterTable) do
        --     if v.isOwned then
        --         Owned_CharacterTable[k] = v
        --     end
        -- end

        -- table.sort(Shop_CharacterTable)
        local x_offset = 130
        local count = 0

        ---@type CharacterShop
        Shop_CharacterShop = _G.Shop_CharacterShop

        local tCharacters = {}
        for k,v in pairs(Shop_CharacterTable) do
            table.insert(tCharacters,v)
        end

        table.sort(tCharacters, function(a,b) return a.ID < b.ID end)

        for k,l in pairs(tCharacters) do
            local v = l
            Shop_CharacterShop:addCharPanel(Home_GUIScriptingPtr, count * x_offset, 10, 125,250, v.panelPath,v.ID,
            v.price,v.isOwned)
            count = count + 1
        end
    else
        -- print("Character request result end failed")
        SendRequest(PacketChannel.ShopChannel,ShopResponse.ShopChracterInfo , {'get_character_shop_list'}, 5, 0.25)
    end
end


require "skill_client_handler"
require "character_client_handler"
require "formation_client_handler"

require "home_Input_control"