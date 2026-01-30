package.path = package.path .. ";../luaFiles/?.lua"

require "serverWrapper"
-- require "clientHandling"
require "SV_global"

--- keep just for the old package ( from client inquiry)
PacketCode = {
    login = 35,
    register = 36,
    requestKey = 37,
    requestUserData = 65,
    requestCharacterList = 66
}

--- function CheckAccountValid
---@Description : check if the query of account and password is valid (only one result)
---@param host pointer instance of ServerScriptingManager
---@param id string account id (1)
---@param pw string account password (2)
---@return number? tResult of count query
function CheckAccountCount(host, id, pw)

    local queryCountCmd= "SELECT COUNT(" .. Table.account.id .. ") FROM " .. Table.account.tb_name .. " WHERE " .. Table.account.id .. " = ? AND " .. Table.account.pw .. " = ?;"
    local ePW = SV_getEncryptPW(host, pw)
    -- print("tpw " .. pw)
    -- print("epw " .. ePW)
    SVI_DoQuerySTMT(host,queryCountCmd,{id,ePW})
    -- print("result " .. Query_val[1])
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
    -- print("CheckAccountValid debug: everything OK ")
    return true
end

--- MARK: Request_Key 
ResponseHandle[PacketCode.requestKey] = function(host, packet)

    local message = SV_GetPacketData(host,packet)

    -- print("request key found, processing")
    local pattern_start = "|REQUEST_KEY_REQUEST|"
    -- print("message " .. message)
    local firstIndex = string.find(message, pattern_start)
    local beginP = firstIndex + string.len(pattern_start)

    local pattern_end = "|REQUEST_KEY_END_REQUEST|"
    local endIndex = string.find(message, pattern_end)
    local processResult = string.sub(message, beginP, endIndex - 1)
    local clientIP = SV_GetPacketIP(packet)

    --- split id and account by the sigh |
    local t_id = string.sub(processResult, 0,string.find(processResult, "|") - 1)
    local t_pw = string.sub(processResult, string.len(t_id) + 2 , string.len(processResult))
    -- print("id is " .. t_id)
    -- print("pw is " .. t_pw)

    if CheckAccountValid(host, t_id, t_pw) then
        print("account is valid")
        local queryCountCmd= "SELECT " .. Table.account.lvl .. " FROM " .. Table.account.
        tb_name .. " WHERE " .. Table.account.id .. " = ? AND " .. Table.account.pw .. " = ?;"
        local ePW = SV_getEncryptPW(host, t_pw)

        SVI_DoQuerySTMT(host,queryCountCmd,{t_id,ePW})

        local result = tonumber(Query_val[1])
        if result > 1 then 
            -- gen key 
            local keyGen = AddRegisterKey(host)
            if keyGen ~= nil then
                print("sendata " .. keyGen)
                SV_SendMsg(host,clientIP,"Your register key is: " .. keyGen)
            else
                print("keygen is nil")
            end
        else
            SV_SendMsg(host,clientIP,"Your account does not have authority to request key" )
        end
    else
        SV_SendMsg(host,clientIP,"Access denied !" )
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

--- MARK:Login reponse

---- Wrap Mesage Handling
---@param host pointer instance of ServerScriptingManager
---@param data string data recieved
---@param ip pointer client ip
---@param guid string client guid
MessageHandling[PacketChannel.AccountChannel][AccountResponse.Alogin] = function(host ,data, ip, guid)
    -- print("Server AccountResponse.Alogin called")
    ClientEPList = _G.ClientEPList

    local t_id, t_pw = string.match(data, "^|([^|]+)|([^|]+)|$")

    if t_id == nil or t_pw == nil then
        print("Ke3 F3i117 exception (PacketChannel.AccountChannel][AccountResponse.Alogin)")

        print("raw data try to decode " .. data)
        return
    end

    local loginResult = "K2 request failed"
    if CheckAccountValid(host, t_id, t_pw) then
        loginResult = "granted"
        for k,v in pairs(ClientEPList) do
            if v.name == t_id then
                loginResult = "Account already logged in !"
                print("Account already logged in !")
                break
            end
        end
    else
        loginResult = "Account or password is incorrect !"
    end

    print("loging from " .. SV_GetIPString(ip) .. " with ping " .. SV_GetTargetPing(ip))

    print("login result " .. loginResult)
    SendReliable(host,ip,guid,PacketChannel.AccountChannel,AccountResponse.Alogin,{ t_id,loginResult,t_pw, guid})

    if loginResult == "granted" then
        CH_AddClientEP(ip, guid, t_id)
    end
end

--- MARK: Register reponse
---@Description Handle register request
---@param host pointer instance of ServerScriptingManager
---@param data string data recieved
---@param ip pointer client ip
---@param guid string client guid
MessageHandling[PacketChannel.AccountChannel][AccountResponse.Aregister] = function(host ,data, ip, guid)
    local t_id, t_pw, t_key = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|$")

    if t_id == nil or t_pw == nil or t_key == nil then
        print("Ke3 F3i117 exception (PacketChannel.AccountChannel][AccountResponse.Aregister)")
        return
    end

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
            SendReliable(host,ip,guid,PacketChannel.AccountChannel,AccountResponse.Aregister,{ "Register Key is invalid !"})
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
                SendReliable(host,ip, guid,PacketChannel.AccountChannel,AccountResponse.Aregister,{ "Register successfully !" })
                -- add starter mon and souls to new account
                local insertCurrency =  "INSERT INTO account_stats_table (account_id, mon, souls) VALUES (?, 100, 150);"
                SVI_DoQuerySTMT(host,insertCurrency,{t_id})
            else
                SV_SendMsg(host,ip,CombinePackage("REGISTER_RES_NEG",{ "Register Key already used !"}))
            end
        else
            print("multiple key found in query, WARNING")
        end
    elseif accountCount == 1 then
        SendReliable(host,ip,guid,PacketChannel.AccountChannel,AccountResponse.Aregister,{"Account already exists !"})
        -- SV_SendMsg(host,ip,"Account already exists" )
    else
        SendReliable(host,ip,guid,PacketChannel.AccountChannel,AccountResponse.Aregister,{"Oh no, we got a hecker !!!!"})
        print("accountCount is " .. accountCount)
        print("If you see this warning in production, you are COOKED !")
    end
end

--- May move to user channel lua file if needed

--- MARK: User request Info response
---@Description Handle register request
---@param host pointer instance of ServerScriptingManager
---@param data string data recieved
---@param ip pointer client ip
---@param guid string client guid
MessageHandling[PacketChannel.UserChannel][UserResponse.MainInfo] = function(host ,data, ip, guid)

    -- print("MessageHandling[PacketChannel.UserChannel][UserResponse.MainInfo] = function(host ,data, ip, guid)")

    print("request from " .. guid)
    local t_id, t_pw, t_guid = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|$")

    if t_id == nil or t_pw == nil or t_guid == nil then
        print("Ke3 F3i117 exception (PacketChannel.UserChannel][UserResponse.MainInfo)")
        return
    end
    -- print("check account " .. t_id .. " " .. t_pw .. " " .. t_guid)

    if CheckAccountValid(host, t_id, t_pw) then
        -- print("account check OK, getting data from DB")
        local getDataQuerry = "SELECT mon,souls from " .. Account_Stats_Table.tb_name .. " WHERE " .. Account_Stats_Table.id  .. " = ?;"
        SVI_DoQuerySTMT(host,getDataQuerry,{t_id})

        local mon = Query_val[1]
        local souls = Query_val[2]

        SendReliable(host,ip,guid,PacketChannel.UserChannel,UserResponse.MainInfo,{ t_id,mon,souls,t_guid})
    end
end

