

print("init client side script")

ClientSide_Host = nil

---@class RakNet_SystemAddress


ServerResponseHeader = {}

---@class (exact) Client_Packet
---@field data string
---@field ipAddr pointer instance of RakNet::SystemAddress
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
    ID_CONNECTION_REQUEST_ACCEPTED = 16
}


---@Description create new instance of Label
---@return Client_Packet
function Client_Packet:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

-- ---@Description create new instance of Label
-- ---@param msg string data sent from C++ engine
-- ---@param ip pointer instance of RakNet::SystemAddress sent from C++ engine
-- function Client_Packet:init(msg, ip)
--     self.data = msg
--     self.ipAddr = ip
-- end


---Init script
function ClientSide_Init(host)
    ClientSide_Host = host
end

--- MARK:Wrapper

--- wrapper of cppSendData
---@param host pointer instance of ClientScriptingManager
---@param data string data need to send
---@return number response 
function Client_SendData(host,data)
    return cppSendData(host,data)
end

--- wrapper of cppSendData
---@param host pointer instance of ClientScriptingManager
function Client_Connect(host)
    local pID =  cppConnect(host)
end

--- get Data from C++ engine
---@Description get Data from C++ engine
---@param msg string data sent from C++ engine
---@param ip pointer instance of RakNet::SystemAddress sent from C++ engine
---@
function Client_ReceiveData(msg, ip,pID)
    local tPacket = Client_Packet:new()
    tPacket.data = msg
    tPacket.ipAddr = ip
    tPacket.packetID = pID
    Client_HandlePacket(tPacket)
end

--- handle packet
--- @param packet Client_Packet
function Client_HandlePacket(packet)
    print("handle packet")
    if Login_HandleTask[packet.packetID] ~= nil then
        Login_HandleTask[packet.packetID](ClientSide_Host,packet)
    end
end



