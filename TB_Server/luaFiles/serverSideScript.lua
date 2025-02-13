print("server side script started ...")

package.path = package.path .. ";../luaFiles/?.lua"

require "serverWrapper"



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
    login = 35
}


ResponseHandle = {}


ResponseHandle[PacketCode.login] = function(host, message)
    print("login response found, processing")
    local pattern_start = "|LOGIN_REQUEST|"
    local firstIndex = string.find(message, pattern_start)
    local beginP = firstIndex + string.len(pattern_start)

    local pattern_end = "|LOGIN_END_REQUEST|"
    local endIndex = string.find(message, pattern_end)
    
    local processResult = string.sub(message, beginP, endIndex - 1)
    --- dump 
    --- split id and account by the sigh | 
    local t_id = string.sub(processResult, 0,string.find(processResult, "|") - 1)
    local t_pw = string.sub(processResult, string.len(t_id) + 2 , string.len(processResult))
    print("id is " .. t_id)
    print("pw is " .. t_pw)

    local checkLoginSql = "SELECT * FROM " .. Table.account.tb_name .. " WHERE " ..Table.account.id.. " = '" .. t_id .. "' AND " .. Table.account.pw .. " = '" .. t_pw .. "';"
    print(checkLoginSql)
    SV_DoQuery(host, checkLoginSql)
    
    -- for i = 1, Query_count do
    --     print(Query_col[i] .. ">:<" .. Query_val[i])
    -- end

    local index = 4
    if Query_count == 0 then 
        print("a login attemp failed")
    else if Query_count > 4 then
        print("WARNING unexpected result, If you see this message in production ? you are COOKED !!!")
    else --- only one result
        print("a login attemp succeed")
        -- todo : query relevant info and send back to client
    end

end
        -- body

end

function Init(host)
    T_Host = host
end

function HandleMessage(host,message,requestCode)
    print("relay message")
    print(message)
    print("request code : " .. requestCode)

    if ResponseHandle[requestCode] ~= nil then
        ResponseHandle[requestCode](host, message)
    end

end

function AddColData(colName, value)

    Query_count = Query_count + 1
    Query_col[Query_count] = colName
    Query_val[Query_count] = value

end

print("server side script ended ...")
