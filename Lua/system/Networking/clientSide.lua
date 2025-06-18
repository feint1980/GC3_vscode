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

PacketID = {
    ID_DISCONNECTION_NOTIFICATION = 21,
    ID_ALREADY_CONNECTED = 18,
    ID_INCOMPATIBLE_PROTOCOL_VERSION = 25,
    ID_REMOTE_DISCONNECTION_NOTIFICATION = 31,
    ID_REMOTE_CONNECTION_LOST = 32,
    ID_REMOTE_NEW_INCOMING_CONNECTION = 33,
    ID_CONNECTION_BANNED = 23,
    ID_CONNECTION_ATTEMPT_FAILED = 17,
    ID_NO_FREE_INCOMING_CONNECTIONS = 20,
    ID_INVALID_PASSWORD = 24,
    ID_CONNECTION_LOST = 22,
    ID_CONNECTION_REQUEST_ACCEPTED = 16,
    ID_OTHER = 124
}

Packet_OtherID = {
    ID_LOGIN_NEG = 1,
    ID_LOGIN_POS = 2,
    ID_REGISTER_NEG = 3,
    ID_REGISTER_POS = 4,
    USER_DATA_POS = 5,
    USER_DATA_NEG = 6,
    CHARACTER_RES = 66,
    CHARACTER_RES_DONE = 67,
    ID_INVALID = 77
}

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

    print("Client_SendWrapData called")
    return cppSendWrapData(host,WrapRequest(channel,request,list))
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
---@param msg string data sent from C++ engine
---@param ip RakNet_SystemAddress instance of RakNet::SystemAddress sent from C++ engine
---@param pID number packet ID
function Client_ReceiveData(msg, ip,pID)
    local tPacket = Client_Packet:new()
    -- print("Client_ReceiveData recieve : " .. msg )
    tPacket.data = msg
    tPacket.ipAddr = ip
    tPacket.packetID = pID
    Client_HandlePacket(tPacket)
end

HandlePacketTask = {}

--- handle packet
--- @param packet Client_Packet
function Client_HandlePacket(packet)
    -- print("handle packet" .. packet.packetID)
    for k,v in pairs(HandlePacketTask) do
        -- print(k)
        if HandlePacketTask[k] ~= nil then
            HandlePacketTask[k](ClientSide_Host,packet)
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

ClientMessageHandling = {

}

ClientMessageHandling[PacketChannel.AccountChannel] = {}

ClientMessageHandling[PacketChannel.ShopChannel] = {}

ClientMessageHandling[PacketChannel.TransactionChannel] = {}

ClientMessageHandling[PacketChannel.UserChannel] = {}

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

function ClientHandlerWrapResponse(host,chanel,request, data,ip,guid)
    print("ClientHandlerWrapResponse called" )

    if ClientMessageHandling[chanel][request] ~= nil then
        ClientMessageHandling[chanel][request](host,data,ip,guid)
    end
end