

print("init client side script")

ClientSide_Host = nil


ServerResponseHeader = {}

---@class Client_Packet
Client_Packet = {
    data = "",
    ipAddr = nil
}

---@Description create new instance of Label
---@return Label
function Client_Packet:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

---@Description create new instance of Label
---@param msg string data sent from C++ engine
---@param ip pointer instance of RakNet::SystemAddress sent from C++ engine
function Client_Packet:init(msg, ip)
    self.data = msg
    self.ipAddr = ip
end



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
    cppConnect(host)
end

--- get Data from C++ engine
---@param msg string data sent from C++ engine
---@param ip pointer instance of RakNet::SystemAddress
---@return Client_Packet
function Client_ReceiveData(msg, ip)
    Client_Packet.data = msg
    Client_Packet.ipAddr = ip
end



print("client side script OK")