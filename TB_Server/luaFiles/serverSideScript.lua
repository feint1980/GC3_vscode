print("server side script started ...")

package.path = package.path .. ";../luaFiles/?.lua"

require "serverWrapper"



--- function SV_DoQuery, clear data before a query
---@Description: call a server to do a query
---@param host pointer instance of ServerScriptingManager
---@param query string the query command
function SVI_DoQuery(host,query)
    ClearQuery()
    SV_DoQuery(host,query)
end


--- function SVI_DoQuerySTMT, clear data before a query
---@Description: call a server to do a query
---@param host pointer instance of ServerScriptingManager
---@param baseStmt string the the base stmt
---@param paramList table the param list
function SVI_DoQuerySTMT(host, baseStmt, paramList )
    ClearQuery()

    local stmt = SV_CreateSQLSTMT(host,baseStmt)

    for i = 1, #paramList do
        -- print( "bind index " .. i)
        SV_BindSQLSTMT(stmt,i,paramList[i])
    end

    SV_DoQuerySTMT(host,stmt)

    SV_SQLFinalizeStmt(stmt)
end


Account_Table = {
    tb_name = "account_table",
    no = "account_no",
    id = "account_id",
    pw = "account_password",
    lvl = "account_lvl"

}

RegisterKey_Table = {
    tb_name = "register_key_table",
    no = "key_no",
    val = "key_str_val",
    ready = "key_ready"
}

---@class Table
-- Table = {
--     register_key = "register_key_table",
--     account = "account_table",
--     account_stats = "account_stats_table";
--     character_base = "character_base_table";
--     character_exisance = "character_existance_table";
-- }

Table = {
    account = Account_Table,
    register_key = RegisterKey_Table
}


Query_count = 0

Query_col = {

}

Query_val = {

}

function ClearQuery()
    for i = 1, Query_count do
        Query_col[i] = nil
        Query_val[i] = nil
    end
    Query_count = 0
end

function AddColData(colName, value)
    Query_count = Query_count + 1
    Query_col[Query_count] = colName
    Query_val[Query_count] = value
end

T_Host = nil


ResponseHandle = {}

---@Description combines packet
---@param type string type of packet to wrap
---@param list table data to wrap
function CombinePackage(type,list)
    ----
    local returnValue = "|"
    returnValue = returnValue .. type .. "_REQUEST|" 
    for i = 1, #list do
        returnValue = returnValue .. list[i] .. "|"
    end
    returnValue = returnValue .. type .. "_END_REQUEST|"
    return returnValue
end



function ServerSide_Init(host)
    T_Host = host
end

--- function HandleMessage 
--- @Description : handle message from client
--- @param host pointer instance of ServerScriptingManager
--- @param packet pointer instance of 
--- @param requestCode number request code
function HandleMessage(host,packet,requestCode)


    local message = SV_GetPacketData(host,packet)
    print("relay message")
    print(message)
    print("request code : " .. requestCode)

    if ResponseHandle[requestCode] ~= nil then
        ResponseHandle[requestCode](host,packet)
    end

end

function AddColData(colName, value)

    Query_count = Query_count + 1
    Query_col[Query_count] = colName
    Query_val[Query_count] = value

end

require "accountHandle"

print("server side script ended ...")
