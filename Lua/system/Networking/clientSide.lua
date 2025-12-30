package.path = package.path .. ';../../Lua/system/GUI/?/?.lua;' .. ';../../Lua/system/GUI/widgets/?.lua;' .. ';../../Lua/system/Networking/?.lua;' .. ';../../Lua/TouhouTB/Home/?.lua;' .. ';../../Lua/system/event/?.lua;' .. ';../../Lua/TouhouTB/Home/Shop/?.lua;' .. ';../../Lua/TouhouTB/characters/?.lua;' .. ';../../Lua/?.lua;' .. './TouhouTB/characters/Common/?.lua;' .. './TouhouTB/characters/Patchy/?.lua;' .. ';../../Lua/TouhouTB/characters/Patchy/?.lua;' .. ';./TouhouTB/characters/Reimu/slots/?.lua;' .. ';../../Lua/TouhouTB/characters/Reimu/?.lua;' .. ';./TouhouTB/characters/Yukari/slots/?.lua;' .. ';../../Lua/TouhouTB/characters/Yukari/?.lua;' .. ';../../Lua/TouhouTB/?.lua' .. ';../../Lua/TouhouTB/characters/Meiling/?.lua;' .. ';../../Lua/TouhouTB/?.lua'

ClientSide_Host = nil
---@class RakNet_SystemAddress


require "clientWrapper"

ServerResponseHeader = {}

---@class (exact) Client_Packet
---@field data string data need to send
---@field ipAddr RakNet_SystemAddress instance of RakNet_SystemAddress
---@field packetID number
Client_Packet = {
    data = "",
    ---@type RakNet_SystemAddress
    ipAddr = nil,
    packetID = 0
}
Client_Connected = false

-- Packet_OtherID = {
--     ID_LOGIN_NEG = 1,
--     ID_LOGIN_POS = 2,
--     ID_REGISTER_NEG = 3,
--     ID_REGISTER_POS = 4,
--     USER_DATA_POS = 5,
--     USER_DATA_NEG = 6,
--     CHARACTER_RES = 66,
--     CHARACTER_RES_DONE = 67,
--     ID_INVALID = 77
-- }





---@Description create new instance of Label
---@return Client_Packet
function Client_Packet:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

---Init script
function ClientSide_Init(host)
    ClientSide_Host = host
end

--- Client_SendRequest
---@param host pointer instance of ClientScriptingManager
---@param channel number channel
---@param request number type of packet to wrap
---@param data string data need to send 
function Client_SendRequest(host, channel, request, data)

    local tData = string.char(channel, request) .. data

    return cppSendRequest(host, tData)
end

--- MARK:Wrapper
--- wrapper of cppSendData
---@param host pointer instance of ClientScriptingManager
---@param data string data need to send
---@param encryptIndex? number encrypt index
---@return number response 
function Client_SendData(host,data,encryptIndex)
    encryptIndex = encryptIndex or 0
    return cppSendData(host,data,encryptIndex)
end

--- wrapper of cppSendWrapData
--- @param host pointer instance of ClientScriptingManager
--- @param channel number channel
--- @param request number type of packet to wrap
--- @param list table data to wrap
function Client_SendWrapData(host,channel,request,list)
    -- print("Client_SendWrapData called ")
    return cppSendWrapData(host,WrapRequest(channel,request,list))
end

--- wrapper of cppSendBattleWrapData
--- @param host pointer instance of ClientScriptingManager
--- @param channel number channel
--- @param request number type of packet to wrap
--- @param list table data to wrap
function Client_SendBattleWrapData(host,channel,request,list)
    return cppSendBattleWrapData(host,WrapRequest(channel,request,list))
end


--- wrapper of cppSendData
---@param host pointer instance of ClientScriptingManager
function Client_Connect(host)
    local pID =  cppConnect(host)
end

---wrapper of cppParseCharacterFromJson
---@Description wrapper of cppParseCharacterFromJson
---@param host pointer instance of ClientScriptingManager
---@param data string data need to send
---@return pointer instance of CharacterStats
function Client_ParseCharacterFromJson(host,data)
    return cppParseCharacterFromJson(host,data)
end

--- get Data from C++ engine
---@Description get Data from C++ engine
---@param host pointer instance of ClientScriptingManager
---@param msg string data sent from C++ engine
---@param ip RakNet_SystemAddress instance of RakNet::SystemAddress sent from C++ engine
---@param pID number packet ID
---@param RakNetPacket RakNetPacket instance
function Client_ReceiveData(host,msg, ip,pID,RakNetPacket)
    local tPacket = Client_Packet:new()
    -- print("Client_ReceiveData recieve : " .. msg )
    tPacket.data = msg
    tPacket.ipAddr = ip
    tPacket.packetID = pID
    Client_HandlePacket(host,tPacket,RakNetPacket)
end

HandlePacketTask = {}

--- handle packet
--- @param host pointer instance of ClientScriptingManager
--- @param packet Client_Packet
--- @param RakNetPacket instance of RakNetPacket
function Client_HandlePacket(host,packet,RakNetPacket)
    -- print("handle packet" .. packet.packetID)
    for k,v in pairs(HandlePacketTask) do
        -- print(k)
        if HandlePacketTask[k] ~= nil then
            HandlePacketTask[k](host,packet,RakNetPacket)
        end
    end
end

function GetTableSize(t)
    local count = 0
    for _, _ in pairs(t) do
        count = count + 1
    end
    return count
end




-- ---@Description combines packet
-- ---@param type string type of packet to wrap
-- ---@param list table data to wrap
-- function CombinePackage(type,list)
--     local returnValue = "|"
--     returnValue = returnValue .. type .. "_REQUEST|" 
--     for i = 1, #list do
--         returnValue = returnValue .. list[i] .. "|"
--     end
--     returnValue = returnValue .. type .. "_END_REQUEST|"
--     return returnValue
-- end

--- Handle wrapper message
---@Description Handle wrapper message
---@param host pointer instance of ClientScriptingManager
---@param chanel number channel
---@param request number type of packet to wrap
---@param data string data need to send
function ClientHandlerWrapResponse(host,chanel,request, data,guid)
    -- print("ClientHandlerWrapResponse called" )

    if ClientMessageHandling[chanel][request] ~= nil then
        ClientMessageHandling[chanel][request](host,data,guid)
    end
end

function ClientHandlerBattleResponse(host,chanel,request, data,guid)
    print("ClientBattleHandling called" .. chanel .. " " .. request)
    if  ClientBattleHandling[chanel] == nil then
        print("channel not found " .. chanel)
        return
    end
    if ClientBattleHandling[chanel][request] ~= nil then
        ClientBattleHandling[chanel][request](host,data,guid)
    end
end


RequestPacket = {
    host = nil,
    channel = 255,
    request = 255,
    data = {},
    retries = 5,
    sendTime = 0,
    delay = 0.25,
    packetType = 0,
}

RequestPacketType = {
    MainServer = 1,
    BattleServer = 2
}

function RequestPacket:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

RequestQueue = {

}
RequestQueueIndex = 0


-- Add request
---@param channel number channel
---@param request number request
---@param data table data
---@param retries number
---@param delayFirst? number
---@param delayEach? number
function SendRequest(channel, request, data, retries, delayFirst, delayEach)

    delayFirst = delayFirst or 0
    delayEach = delayEach or 0.25
    table.insert(RequestQueue, {
        channel = channel,
        request = request,
        data = data,
        retries = retries or 5,
        packetType = RequestPacketType.MainServer,
        nextSendTime = os.clock() + delayFirst,
        delay = delayEach
    })
end

function SendBattleRequest(channel, request, data, retries, delayFirst, delayEach)
    delayFirst = delayFirst or 0
    delayEach = delayEach or 0.1
    table.insert(RequestQueue, {
        channel = channel,
        request = request,
        data = data,
        retries = retries or 5,
        packetType = RequestPacketType.BattleServer,
        nextSendTime = os.clock() + delayFirst,
        delay = delayEach
    })
end

function UpdateRequests(host)
    local now = os.clock()

    for i = #RequestQueue, 1, -1 do
        local req = RequestQueue[i]

        if now >= req.nextSendTime then
            local success = 0
            if req.packetType == RequestPacketType.MainServer then
                success = Client_SendWrapData(host, req.channel, req.request,req.data )
            elseif req.packetType == RequestPacketType.BattleServer then
                success = Client_SendBattleWrapData(host, req.channel, req.request,req.data )
            end
            -- print("try to send in chanel " .. req.channel .. " request " .. req.request)
            if success == 0 then
                req.retries = req.retries - 1
                if req.retries <= 0 then
                    print("[✘] Request failed after retries:", req.channel, req.request)
                    table.remove(RequestQueue, i)
                else
                    print("[↻] Retry scheduled:", req.channel, req.request, "retries left:", req.retries)
                    req.nextSendTime = now + req.delay
                end
            else
                -- print("[✔] Request sent:", req.channel, req.request)
                table.remove(RequestQueue, i)
            end
        end
    end
end

-- require "arena_client_handler"

function Client_CollectPingStart()
    -- print("Client_CollectPingStart called")
    Arena_ResetList()
end

function Client_PingUpdate(serverGUID, ping)
    -- print("Client_PingUpdate called")
    Arena_UpdateServerPing(serverGUID, ping)
end


-- Battle server handling 
require "clientBattleSide"