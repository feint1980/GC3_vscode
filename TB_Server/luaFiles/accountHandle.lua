package.path = package.path .. ";../luaFiles/?.lua"

require "serverWrapper"
require "clientHandling"

PacketCode = {
    login = 35,
    register = 36,
    requestKey = 37,
    requestUserData = 65
}




--- function CheckAccountValid
---@Description : check if the query of account and password is valid (only one result)
---@param host pointer instance of ServerScriptingManager
---@param id string account id (1)
---@param pw string account password (2)
---@return number tResult of count query
function CheckAccountCount(host, id, pw)
    -- tResult = -1

    local queryCountCmd= "SELECT COUNT(" .. Table.account.id .. ") FROM " .. Table.account.tb_name .. " WHERE " .. Table.account.id .. " = ? AND " .. Table.account.pw .. " = ?;"
    local ePW = SV_getEncryptPW(host, pw)

    print("tpw " .. pw)
    print("epw " .. ePW)

    SVI_DoQuerySTMT(host,queryCountCmd,{id,ePW})

    print("result " .. Query_val[1])
    local result = Query_val[1]
    local count =  tonumber(result)

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

    local message = SV_GetPacketData(host,packet)

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
        

        -- SVI_DoQuery(host,"SELECT " .. Table.account.lvl .. " FROM " .. Table.account.tb_name .. " WHERE " .. Table.account.id .. " = '" .. t_id .. "' AND " .. Table.account.pw .. " = '" .. t_pw .. "';")


        local queryCountCmd= "SELECT " .. Table.account.lvl .. " FROM " .. Table.account.
        tb_name .. " WHERE " .. Table.account.id .. " = ? AND " .. Table.account.pw .. " = ?;"
        
        -- local stmt = SV_CreateSQLSTMT(host,queryCountCmd)
        
        -- SV_BindSQLSTMT(stmt,1,t_id)
        -- SV_BindSQLSTMT(stmt,2,t_pw)
        
        -- SVI_DoQuerySTMT(host,stmt)
        -- SV_SQLFinalizeStmt(stmt)
        local ePW = SV_getEncryptPW(host, t_pw)

        SVI_DoQuerySTMT(host,queryCountCmd,{t_id,ePW})

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

    local message = SV_GetPacketData(host,packet)
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

    -- local checkAccountExistQuery = "SELECT COUNT(" .. Table.account.id .. ") FROM " .. Table.account.tb_name .. " WHERE " .. Table.account.id .. " = '" .. t_id .. "';"

    local checkAccountExistQuery = "SELECT COUNT(" .. Table.account.id .. ") FROM " .. Table.account.tb_name .. " WHERE " .. Table.account.id .. " = ?;"

    SVI_DoQuerySTMT(host,checkAccountExistQuery,{t_id})


    local result = Query_val[1]
    local accountCount = tonumber(result)
    if accountCount == 0 then

        local checkKeyExistQuery = "SELECT COUNT(*) FROM " .. Table.register_key.tb_name .. " WHERE " .. Table.register_key.val .. " = ?;"

        SVI_DoQuerySTMT(host,checkKeyExistQuery,{t_key})

        result = Query_val[1]
        local keyCount = tonumber(result)
        if keyCount == 0 then
            -- key not exist
            -- SV_SendMsg(host,clientIP,"The register key is invalid" )
            SV_SendMsg(host,clientIP,CombinePackage("REGISTER_RES_NEG",{ "Register Key is invalid !"}))
        elseif keyCount == 1 then
            -- key exist
            -- check if key is ready

            local checkKeyReadyQuery = "SELECT " .. Table.register_key.ready .. " FROM " .. Table.register_key.tb_name .. " WHERE " .. Table.register_key.val .. " = ?;"

            SVI_DoQuerySTMT(host,checkKeyReadyQuery,{t_key})

            local keyReadyValue = tonumber(Query_val[1])
            if keyReadyValue == 1 then

                local insertAccountQuery = "INSERT INTO " .. Table.account.tb_name ..'('.. Table.account.id .. ', ' .. Table.account.pw  .. ") VALUES ( ?,?);"

                local ePW = SV_getEncryptPW(host, t_pw)

                SVI_DoQuerySTMT(host,insertAccountQuery,{t_id,ePW})

                local updateKeyQuery = "UPDATE " .. Table.register_key.tb_name .. " SET " .. Table.register_key.ready .. " = '0' WHERE " .. Table.register_key.val .. " = ?;"

                SVI_DoQuerySTMT(host,updateKeyQuery,{t_key})

                SV_SendMsg(host,clientIP,CombinePackage("REGISTER_RES_POS",{ "Register successfully !" }) )

                -- add starter mon and souls to new account
                local insertCurrency =  "INSERT INTO account_stats_table (account_id, mon, souls) VALUES (?, 100, 15);"
                SVI_DoQuerySTMT(host,insertCurrency,{t_id})

            else
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

--- MARK: Request User Data
ResponseHandle[PacketCode.requestUserData] = function(host,packet)
    print("request user data found, processing")
    local message = SV_GetPacketData(host,packet)
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
    local t_guid = string.sub(halfProcess, string.len(t_pw) + 2 , string.len(halfProcess))

    print("reuest data from " .. clientIP .. " " .. t_id .. " " .. t_pw .. " " .. t_guid)

end

--- MARK: Login reponse
ResponseHandle[PacketCode.login] = function(host,packet)
    print("login response found, processing")

    local message = SV_GetPacketData(host,packet)

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

    
    if CheckAccountValid(host, t_id, t_pw) then

        print("account check OK, send OK message")
        local guid = SV_GetPacketGUID(packet)
        SV_SendMsg(host,clientIP,CombinePackage("LOGIN_RES_POS",{ t_id,t_pw, guid}))


        local systemAddress = SV_GetPacketIP(packet)

        CH_AddClientEP(systemAddress, guid, t_id)

    else
        print("account check failed send negative response")
        SV_SendMsg(host,clientIP,CombinePackage("LOGIN_RES_NEG",{"Account or password is incorrect !"}) )

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
            print("generated already existing key (" .. keyGen ..") , trying again")
        end

    end
    return nil
end
