
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


--- function wrapper of cppDoQuerySTMT
---@Description: call a server to do a query
---@param host pointer instance of ServerScriptingManager
---@param stmt pointer instance of sqlite3_stmt
function SV_DoQuerySTMT(host,stmt)
    cppDoQuerySTMT(host,stmt)
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
---@param host pointer instance of ServerScriptingManager
---@param packet pointer instance of RakNet::Packet
---@return string data of the packet 
function SV_GetPacketData(host,packet)
    return cppPacket_getData(host,packet)
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

--- function wrapper of cppSqlite_CreateStatement
---@Desciption: create a sqlite3_stmt 
---@param host pointer instace of ServerScriptingManager
---@param baseQuery string base query 
function SV_CreateSQLSTMT(host,baseQuery)
    return cppSqlite_CreateStatement(host,baseQuery)
end

--- function wrapper of cppSqlite_BindStatement
---@Desciption: create a sqlite3_stmt 
---@param host pointer instace of ServerScriptingManager
---@param stmt pointer stm need to be bound 
---@param index number indext need to bound
---@param stringVal string 
function SV_BindSQLSTMT(host,stmt,index, stringVal)
    cppSqlite_BindStatement(host,stmt,index, stringVal)
end

--- function wrapper of 