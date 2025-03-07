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

PacketCode = {
    login = 35,
    register = 36,
    requestKey = 37
}

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


--- function CheckAccountValid
---@Description : check if the query of account and password is valid (only one result)
---@param host pointer instance of ServerScriptingManager
---@param id string account id (1)
---@param pw string account password (2)
---@return number tResult of count query
function CheckAccountCount(host, id, pw)
    -- tResult = -1
    print("CheckAccountValid debug: id is " .. id .. " pw is " .. pw)
    local queryCountCmd= " SELECT COUNT(" .. Table.account.id .. ") FROM " .. Table.account.tb_name .. " WHERE " .. Table.account.id .. " = '" .. id .. "' AND " .. Table.account.pw .. " = '" .. pw .. "';"

    print("query " .. queryCountCmd)
    SVI_DoQuery(host, queryCountCmd)
    print("result " .. Query_val[1])
    local result = Query_val[1]
    local count =  tonumber(result)
    
    -- print("tResult " .. tResult)
    return count
end
--- function CheckAccountValid
---@Description : check if the query of account and password is valid (only one result)
---@param host pointer instance of ServerScriptingManager
---@param id string account id (1)
---@param pw string account password (2)
---@return boolean true if valid
function CheckAccountValid(host, id, pw)
    local count = CheckAccountCount(host, id, pw)

    if count > 1 then
        print("WARNING unexpected result, If you see this message in production ? you are COOKED !!!")
        return false
    elseif count == 0 then
        print("valid check failed")
        return false
    end
    print("CheckAccountValid debug: everything OK ")
    return true
end

--- MARK: Request_Key 
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

    --- split id and account by the sigh |
    local t_id = string.sub(processResult, 0,string.find(processResult, "|") - 1)
    local t_pw = string.sub(processResult, string.len(t_id) + 2 , string.len(processResult))
    print("id is " .. t_id)
    print("pw is " .. t_pw)

    if CheckAccountValid(host, t_id, t_pw) then
        print("account is valid")
        
        SVI_DoQuery(host,"SELECT " .. Table.account.lvl .. " FROM " .. Table.account.tb_name .. " WHERE " .. Table.account.id .. " = '" .. t_id .. "' AND " .. Table.account.pw .. " = '" .. t_pw .. "';")

        local result = tonumber(Query_val[1])
        if result > 1 then 
            -- gen key 
            local keyGen = AddRegisterKey(host)
            if keyGen ~= nil then
                SV_SendMsg(host,clientIP,"Your register key is: " .. keyGen)
            else
                print("keygen is nil")
            end
        else
            SV_SendMsg(host,clientIP,"Your account does not have authority to request key" )
        end
    else
        SV_SendMsg(host,clientIP,"Access denied !" )
        -- SV_SendMsg(host,clientIP,CombinePackage("LOGIN_RES_NEG",{"Account or password is incorrect !"}) )
    end

end

--- MARK: Register reponse
ResponseHandle[PacketCode.register] = function(host,packet)
    print("register response found, processing")

    local message = SV_GetPacketData(packet)
    local clientIP = SV_GetPacketIP(packet)

    local pattern_start = "|REGISTER_REQUEST|"
    local firstIndex = string.find(message, pattern_start)
    local beginP = firstIndex + string.len(pattern_start)
    local pattern_end = "|REGISTER_END_REQUEST|"
    local endIndex = string.find(message, pattern_end)

    local processResult = string.sub(message, beginP, endIndex - 1)

    local t_id = string.sub(processResult, 0,string.find(processResult, "|") - 1)
    local halfProcess = string.sub(processResult, string.len(t_id) + 2 , string.len(processResult))
    local t_pw = string.sub(halfProcess, 0,string.find(halfProcess, "|") - 1)
    local t_key = string.sub(halfProcess, string.len(t_pw) + 2 , string.len(halfProcess))
    
    print("id is " .. t_id)
    --print("half is " .. halfProcess)
    print("pw is " .. t_pw)
    print("key is " .. t_key)

    local checkAccountExistQuery = "SELECT COUNT(" .. Table.account.id .. ") FROM " .. Table.account.tb_name .. " WHERE " .. Table.account.id .. " = '" .. t_id .. "';"

    SVI_DoQuery(host,checkAccountExistQuery)
    local result = Query_val[1]
    local accountCount = tonumber(result)
    if accountCount == 0 then
        -- local addAccountQuery = "INSERT INTO " .. Table.account.tb_name .. " VALUES ('" .. t_id .. "', '" .. t_pw .. "', '" .. t_key .. "');"
        -- id is avaiable, check if the key is avaiable to use
        local checkKeyExistQuery = "SELECT COUNT(*) FROM " .. Table.register_key.tb_name .. " WHERE " .. Table.register_key.val .. " = '" .. t_key .. "';"

        SVI_DoQuery(host,checkKeyExistQuery)
        result = Query_val[1]
        local keyCount = tonumber(result)
        if keyCount == 0 then
            -- key not exist
            -- SV_SendMsg(host,clientIP,"The register key is invalid" )
            SV_SendMsg(host,clientIP,CombinePackage("REGISTER_RES_NEG",{ "Register Key is invalid !"}))
        elseif keyCount == 1 then
            -- key exist
            -- check if key is ready
            local checkKeyReadyQuery = "SELECT " .. Table.register_key.ready .. " FROM " .. Table.register_key.tb_name .. " WHERE " .. Table.register_key.val .. " = '" .. t_key .. "';"

            SVI_DoQuery(host,checkKeyReadyQuery)
            local keyReadyValue = tonumber(Query_val[1])
            if keyReadyValue == 1 then
                local insertAccountQuery = "INSERT INTO " .. Table.account.tb_name ..'('.. Table.account.id .. ', ' .. Table.account.pw  .. ") VALUES ('" .. t_id .. "', '" .. t_pw .. "');"
                -- print("account insert check : " .. insertAccountQuery)
                SV_DoQuery(host,insertAccountQuery)
                local updateKeyQuery = "UPDATE " .. Table.register_key.tb_name .. " SET " .. Table.register_key.ready .. " = '0' WHERE " .. Table.register_key.val .. " = '" .. t_key .. "';"
                SV_DoQuery(host,updateKeyQuery)
                SV_SendMsg(host,clientIP,CombinePackage("REGISTER_RES_POS",{ "Register successfully !" }) )
                -- SV_SendMsg(host,clientIP,"Register success")
            else
                -- SV_SendMsg(host,clientIP,"Register Key already use")
                SV_SendMsg(host,clientIP,CombinePackage("REGISTER_RES_NEG",{ "Register Key already used !"}))
            end
        else
            print("multiple key found in query, WARNING")
        end

    elseif accountCount == 1 then
        SV_SendMsg(host,clientIP,CombinePackage("REGISTER_RES_NEG",{ "Account already exists !"}))
        -- SV_SendMsg(host,clientIP,"Account already exists" )
    else
        print("accountCount is " .. accountCount)
        print("If you see this warning in production, you are COOKED !")
    end

end

--- MARK: Login reponse
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
        SV_SendMsg(host,clientIP,CombinePackage("LOGIN_RES_POS",{ "login granted, will send user data later"}))
    else
        SV_SendMsg(host,clientIP,CombinePackage("LOGIN_RES_NEG",{"Account or password is incorrect !"}) )
        -- SV_SendMsg(host,clientIP,"Login failed ( this will be packet to client)" )
    end

end

function AddRegisterKey(host)
    local registerKeyNum = 12

    local inserOK = false

    local keyGen = "DDR"
    while not inserOK do
        keyGen = SV_GenKey(registerKeyNum)

        local queryCheck = "SELECT COUNT(" .. Table.register_key.val .. ") FROM " .. Table.register_key.tb_name .. " WHERE " .. Table.register_key.val .. " = '" .. keyGen .. "';"
        SVI_DoQuery(host,queryCheck)

        local result = Query_val[1]
        local count = tonumber(result)
        if count == 0 then
            inserOK = true
            local queryInsert = "INSERT INTO " .. Table.register_key.tb_name .. " (" .. Table.register_key.val .. ", " .. Table.register_key.ready .. ") VALUES ('" .. keyGen .. "', '1');"
            SV_DoQuery(host,queryInsert)
            return keyGen
        else 
            print("generated already existing key ()" .. keyGen ..") , trying again")
        end

    end
    return nil
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
