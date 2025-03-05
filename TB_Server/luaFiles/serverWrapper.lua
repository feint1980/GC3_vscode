
--- Classes declare
---@class pointer


--- function wrapper of cppDoQuery
---@Description: call a server to do a query
---@param host pointer instance of ServerScriptingManager
---@param query string the query command
function SV_DoQuery(host,query)
    cppDoQuery(host,query)
    SV_GetQueryResults(host)
end


--- function wrapper of cppGetQueryResults
---@Description: get the result of a query
---@param host pointer instance of ServerScriptingManager
function SV_GetQueryResults(host)
    return cppGetQueryResults(host)
end

--- function wrapper of cppPacket_getData
---@Description: get the data of a packet 
---@param packet pointer instance of RakNet::Packet
---@return string data of the packet 
function SV_GetPacketData(packet)
    return cppPacket_getData(packet)
end


--- function wrapper of cppPacket_getIP
---@Description: get the IP of a packet 
---@param packet pointer instance of RakNet::Packet
---@return pointer instance of RakNet::SystemAddress
function SV_GetPacketIP(packet)
    return cppPacket_getIP(packet)
end

--- function wrapper of cppPacket_extract
---@Description: get the data of a packet 
---@param packet pointer instance of RakNet::Packet
---@return string data of the packet 
---@return pointer instance of RakNet::SystemAddress
function SV_ExtractPacket(packet)
    return cppPacket_extract(packet)
end

--- function wrapper of cppSendToClient
---@Description: send a packet to a client
---@param host pointer instance of ServerScriptingManager
---@param clientIP pointer instance of RakNet::SystemAddress
---@param message string message to send
function SV_SendMsg(host,clientIP,message)
    cppSendToClient(host,clientIP,message)
end

--- function wrapper of cppGenKey
---@Description: generate a key
function SV_GenKey(numberOfChars)
    return cppGenKey(numberOfChars)
end