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

Account_Table = {
    tb_name = "account_table",
    no = "account_no",
    id = "account_id",
    pw = "account_password",
    lvl = "account_lvl"

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
    account = Account_Table
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

PacketCode = {
    login = 35,
    register = 36,
    requestKey = 37
}

ResponseHandle = {}


--- function CheckAccountValid
---@Description : check if the query of account and password is valid (only one result)
---@param host pointer instance of ServerScriptingManager
---@param id string account id (1)
---@param pw string account password (2)
---@return boolean true if valid
function CheckAccountValid(host, id, pw)

    print("CheckAccountValid debug: id is " .. id .. " pw is " .. pw)
    local queryCountCmd= " SELECT COUNT(" .. Table.account.id .. ") FROM " .. Table.account.tb_name .. " WHERE " .. Table.account.id .. " = '" .. id .. "' AND " .. Table.account.pw .. " = '" .. pw .. "';"

    print("query " .. queryCountCmd)
    SVI_DoQuery(host, queryCountCmd)
    print("result " .. Query_val[1])
    local result = Query_val[1]
    local count = tonumber(result)
    print("count " .. count)

    if count > 1 then
        print("WARNING unexpected result, If you see this message in production ? you are COOKED !!!")
        return false
    end
    if count == 0 then
        print("valid check failed")
        return false
    end
    print("CheckAccountValid debug: everything OK ")
    return true

end

ResponseHandle[PacketCode.requestKey] = function(host, packet)

    local message = SV_GetPacketData(packet)

    print("request key found, processing")
    local pattern_start = "|REQUEST_KEY_REQUEST|"
    local firstIndex = string.find(message, pattern_start)
    local beginP = firstIndex + string.len(pattern_start)

    local pattern_end = "|REQUEST_KEY_END_REQUEST|"
    local endIndex = string.find(message, pattern_end)

    local processResult = string.sub(message, beginP, endIndex - 1)

    local clientIP = SV_GetPacketIP(packet)

    --- dump
    --- split id and account by the sigh |
    local t_id = string.sub(processResult, 0,string.find(processResult, "|") - 1)
    local t_pw = string.sub(processResult, string.len(t_id) + 2 , string.len(processResult))
    print("id is " .. t_id)
    print("pw is " .. t_pw)

    if CheckAccountValid(host, t_id, t_pw) then
        print("account is valid")
        SVI_DoQuery(host,"SELECT " .. Table.account.lvl .. " FROM " .. Table.register_key.tb_name .. " WHERE " .. Table.register_key.id .. " = '" .. t_id .. "';")

        local result = tonumber(Query_val[1])
        if result > 1 then 
            -- gen key 
            print("here")
        else
            print("here")
        end
    end

end

ResponseHandle[PacketCode.login] = function(host,packet)
    print("login response found, processing")

    local message = SV_GetPacketData(packet)

    local pattern_start = "|LOGIN_REQUEST|"
    local firstIndex = string.find(message, pattern_start)
    local beginP = firstIndex + string.len(pattern_start)

    local pattern_end = "|LOGIN_END_REQUEST|"
    local endIndex = string.find(message, pattern_end)

    local clientIP = SV_GetPacketIP(packet)

    local processResult = string.sub(message, beginP, endIndex - 1)
    --- dump 
    --- split id and account by the sigh | 
    local t_id = string.sub(processResult, 0,string.find(processResult, "|") - 1)
    local t_pw = string.sub(processResult, string.len(t_id) + 2 , string.len(processResult))
    print("id is " .. t_id)
    print("pw is " .. t_pw)

    local totalParam = Table.account.id .. ", " .. Table.account.pw .. ", " .. Table.account.lvl 
    local startQuery = "SELECT "

    local endQuery = " FROM " .. Table.account.tb_name .. " WHERE " .. Table.account.id .. " = '" .. t_id .. "' AND " .. Table.account.pw .. " = '" .. t_pw .. "';"

    local checkLoginSql = startQuery .. totalParam .. endQuery
    local checkCountSql = startQuery .. "COUNT(*)"  .. endQuery

    if CheckAccountValid(host, t_id, t_pw) then
        -- print("account is valid")
        print("account is valid")
    else
        print("login failed")
        SV_SendMsg(host,clientIP,"Login failed ( this will be packet to client)" )
    end

end


function Init(host)
    T_Host = host
end


--- function HandleMessage 
--- @Description : handle message from client
--- @param host pointer instance of ServerScriptingManager
--- @param clientIP pointer of IP system from client
--- @param message string message from client
--- @param requestCode number request code
function HandleMessage(host,packet,requestCode)
    print("relay message")

    local message = SV_GetPacketData(packet)

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

print("server side script ended ...")
