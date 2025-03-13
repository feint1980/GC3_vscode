
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
---@param stmt pointer stm need to be bound 
---@param index number indext need to bound
---@param stringVal string 
function SV_BindSQLSTMT(stmt,index, stringVal)
    cppSqlite_BindStatement(stmt,index, stringVal)
end

--- function wrapper of cppSqlite_StepStatement
---@Desciption: create a step a sqlite3_stmt 
---@param host pointer instace of ServerScriptingManager
---@param stmt pointer stm need to be step
---@return number return value of the step
function SV_StepSQLSTMT(host,stmt)
    return cppSqlite_StepStatement(host,stmt)
end

--- function wrapper of cppSqlite_GetResultColumnCount
--- @Desciption: get the column count of a sqlite3_stmt after step
--- @param stmt pointer stm just run 
--- @return number number of column in the result
function SV_SQLGetResultColumnCount(stmt)
    return cppSqlite_GetResultColumnCount(stmt)
end

--- function wrapper of cppSqlite_gettResultInt
--- @Desciption: get the result as int value
--- @param stmt pointer stm just run
--- @param index number index of the column
--- @return number number of column in the result
function SV_SQLGetResultInt(stmt,index)
    return cppSqlite_gettResultInt(stmt,index)
end

--- function wrapper of cppSqlite_gettResultString
--- @Desciption: get the result as string value
--- @param stmt pointer stm just run
--- @param index number index of the column
--- @return string value of column in the result
function SV_SQLGetResultString(stmt,index)
    return cppSqlite_gettResultString(stmt,index)
end

--- function wrapper of cppSqlite_finalizeStmt
--- @Desciption: get the result as string value
--- @param stmt pointer stm just run
function SV_SQLFinalizeStmt(stmt)
    cppSqlite_finalizeStmt(stmt)
end

--- function wrapper of cppGenKey
--- @Desciption: get the generated key 
--- @param no number of key generated
--- @return string generated key
function SV_GenKey(no)
    return cppGenKey(no)
end