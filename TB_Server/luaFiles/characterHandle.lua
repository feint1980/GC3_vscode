package.path = package.path .. ";../luaFiles/?.lua"

require "serverWrapper"
require "SV_global"

local function checkIfUserOwnedCharacter(host, userID, chacaterID)

    local checkQuery = "SELECT 1 FROM " .. Table.user_character.tb_name .. " WHERE " .. Table.user_character.id .. " = ? AND " .. Table.user_character.character_id .. " = ?;"
    local result = SVI_DoQuerySTMT(host,checkQuery,{userID,chacaterID})
    if result[1] ~= nil then
        return true
    else
        return false
    end

end

--- MARK: Shop Request
---@Description Handle register request
---@param host pointer instance of ServerScriptingManager
---@param data string data recieved
---@param ip pointer client ip
---@param guid string client guid
MessageHandling[PacketChannel.ShopChannel][ShopResponse.ShopChracterInfo] = function(host ,data, ip, guid)

    local t_request = string.sub(data, 2, string.len(data) -1)
    if t_request == 'get_character_shop_list' then
        local count = 0
        --- send begin
        SendReliable(host,ip, guid,PacketChannel.ShopChannel,ShopResponse.ShopCharacterInfo_Begin,{"IDK bro,  how about that ?"})
        for k,v in pairs(Character_Serialized_Table) do
            local chracterInfo = {}
            count = count +1
            local sendData = 0

            local isOwned  = checkIfUserOwnedCharacter(host, CH_FindClient(guid).name, Character_Table[k].ID)

            -- print(Character_Table[k].ID)
            -- determine if the player already owned this character 

            SendReliable(host,ip, guid,PacketChannel.ShopChannel,ShopResponse.ShopCharacterInfo_Data,{k,v,tostring (isOwned)})
            -- print("send " .. k .. " done !")
        end
        --- send end
        SendReliable(host,ip,guid,PacketChannel.ShopChannel,ShopResponse.ShopCharacterInfo_End,{tostring(count)})

    end
end

--- MARK: Buy Transaction
MessageHandling[PacketChannel.TransactionChannel][ShopResponse.ShopCharacter_Buy] = function(host ,data, ip, guid)

    -- check account valid (1st gatekeep, easy)
    if CH_FindClient(guid) == nil then
        print("client not found, request from ip " .. tostring(ip))
        return
    end
    print("request buy chracter from " .. CH_FindClient(guid).name)
    print("data rr " .. data)
    -- check if account is valid (2nd gatekeep)
    local t_id, t_pw , characterID = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|$")

    if t_id == nil or t_pw == nil or characterID == nil then
        print("Ke3 F3i117 exception (PacketChannel.TransactionChannel][ShopResponse.ShopCharacter_Buy)")
        return
    end

    if CheckAccountValid(host, t_id, t_pw) then
        print("gatekeep 2 ok")
    end
    
    --- check if the buying character exist in db
    local checkChracterQuery = "SELECT " ..  Table.character_base.character_id .. " FROM " .. Table.character_base.tb_name .. " WHERE " .. Table.character_base.character_id .. " = ?;"
    local result = SVI_DoQuerySTMT(host,checkChracterQuery,{characterID})

    if result[1] == nil then
        print("character not found in db -- return")
        return
    else
        print("character found in db")
    end

    -- check if the server already loaded the character in server buffer 
    local foundInBuffer = false
    ---@type S_Character
    local characterRef = nil
    for k, v in pairs(Character_Table) do
        if v.ID == characterID then
            foundInBuffer = true
            characterRef = v
            break
        end
    end
    if foundInBuffer == false then
        print("character not found in server buffer -- return")
        return
    else
        print("character found in server buffer")
    end

    -- transaction start 

    SV_SQLExec(host, "BEGIN TRANSACTION;")

    local alreadyOwned = false

    local checkOwnedQuery = "SELECT 1 FROM " .. Table.user_character.tb_name .. " WHERE " .. Table.user_character.id .. " = ? AND " .. Table.user_character.character_id .. " = ?;"
    local result = SVI_DoQuerySTMT(host,checkOwnedQuery,{t_id,characterID})
    if result[1] ~= nil then
        alreadyOwned = true
    end
    print("Character owned status " .. tostring(alreadyOwned))
    if alreadyOwned == true then
        SendReliable(host,ip,guid,PacketChannel.TransactionChannel,ShopResponse.ShopCharacter_Buy,{"Character already owned","BUY_RES_NE"})
        SV_SQLExec(host, "ROLLBACK;")
        return
    end

    --- get soul cost of selected character 
    local souldCost = characterRef.price
    print("soul cost " .. tostring(souldCost))

    local currentOwnedSoul = 0
    
    local checkSoulQuery = "SELECT " .. Table.account_stats.soul .. " FROM " .. Table.account_stats.tb_name .. " WHERE " .. Table.account_stats.id .. " = ?;"
    result = SVI_DoQuerySTMT(host,checkSoulQuery,{t_id})
    currentOwnedSoul = result[1]
    print("current owned souls " .. tostring(currentOwnedSoul))

    if tonumber(currentOwnedSoul) < souldCost then
        -- send noti back to client ( not enough soul)
        SendReliable(host,ip,guid,PacketChannel.TransactionChannel,ShopResponse.ShopCharacter_Buy,{"Not Enough Souls!","BUY_RES_NE"})
        SV_SQLExec(host, "ROLLBACK;")
        return
    end

    if alreadyOwned == false and tonumber(currentOwnedSoul) >= tonumber(souldCost) then

        local updateSoulQuery = "UPDATE " .. Table.account_stats.tb_name .. " SET " .. Table.account_stats.soul .. " = " .. Table.account_stats.soul .. " - " .. tostring(souldCost) .."  WHERE " .. Table.account_stats.id .. " = ?;"

        print("update soul query " .. updateSoulQuery)
        SVI_DoQuerySTMT(host,updateSoulQuery,{t_id})

        -- stats right now use serialized table, consider have it access from db
        local tStats = "T_F_OFF"

        local getStatsSQL = "SELECT " .. Table.character_base.stats .. " FROM " .. Table.character_base.tb_name .. " WHERE " .. Table.character_base.character_id .. " = ?;"
        local tResult = SVI_DoQuerySTMT(host,getStatsSQL,{characterID})
        tStats = tResult[1]

        print("stat : " .. tostring(tStats))
        local insertQuery = "INSERT INTO " .. Table.user_character.tb_name .. " (" .. Table.user_character.id .. ", " .. Table.user_character.character_id .. ") VALUES (?, ?);"
        SVI_DoQuerySTMT(host,insertQuery,{t_id,characterID, tStats})
        SV_SQLExec(host, "COMMIT;")

        print("Transaction from " .. CH_FindClient(guid).name .. " for buying " .. characterRef.name .. " completed  OK !" )
        SendReliable(host,ip,guid,PacketChannel.TransactionChannel,ShopResponse.ShopCharacter_Buy,{"You unlocked " .. characterRef.name .. "!", "BUY_RES_OK"})
        return
    else
        print("rolling back, Buying character failed")
        print("already owned " .. tostring(alreadyOwned))
        print("balance " .. tostring(currentOwnedSoul) .. " < " .. tostring(souldCost))
        SV_SQLExec(host, "ROLLBACK;")
        return
    end
end


--- MARK: Owned Response
MessageHandling[PacketChannel.UserChannel][UserResponse.OwnedCharacter_Request] = function(host ,data, ip, guid)
    -- print("Request character owned info get ")

    local t_id, t_guid, tData = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|$")

    if t_id == nil or t_guid == nil or tData == nil then
        print("Ke3 F3i117 exception (PacketChannel.UserChannel][UserResponse.OwnedCharacter_Request)")
        return
    end

    -- print("recieve data " .. tData .. " from " .. t_guid)

    --- guid check 
    if t_guid ~= guid then
        print("invalid user,  warning, craft packet found from ip " .. SV_GetIPString(ip))
        return
    else
        -- print("guid check OK")
    end

    --- connected guid check 
    if CH_FindClient(t_guid) == nil then
        print("client not found, warning, craft packet found from ip " .. SV_GetIPString(ip))
        return
    else
        -- print("client found " .. CH_FindClient(t_guid).name .. "|" .. SV_GetIPString(ip))
    end

    -- check if id and t_id match
    if t_id ~= CH_FindClient(t_guid).name then
        print("invalid user,  warning, craft packet found from ip " .. SV_GetIPString(ip))
        return
    else
        -- print("id OK : " .. t_id .. "/" .. CH_FindClient(t_guid).name) 
    end


    ExistingCharacters[t_id] = {}

    --- Get owned character list 
    -- local ownedCharacterQuery = "SELECT " .. Table.user_character.character_id .. "," .. Table.user_character.level .. "," .. Table.user_character.exp .. "," .. Table.user_character.stats ..   " FROM " .. Table.user_character.tb_name .. " WHERE " .. Table.user_character.id .. " = ?;" 

    local ownedCharacterCountQuery = "SELECT COUNT(*) FROM " .. Table.user_character.tb_name .. " WHERE " .. Table.user_character.id .. " = ?;"

    local ownedCharacterCount = SVI_DoQuerySTMT(host,ownedCharacterCountQuery,{t_id})


    local tOwnedCount = tonumber(ownedCharacterCount[1])
    if tOwnedCount > 0 then
        print("user has " .. tostring(ownedCharacterCount[1]) .. " owned character")

        local ownedCharacterQuery = "SELECT " .. 
        Table.user_character.character_id .. ", " ..
        Table.user_character.level .. ", " ..
        Table.user_character.exp .. ", " ..
        Table.user_character.stat_points .. ", " ..
        Table.user_character.str_pts .. ", " ..
        Table.user_character.vit_pts .. ", " ..
        Table.user_character.dex_pts .. ", " ..
        Table.user_character.agi_pts .. ", " ..
        Table.user_character.int_pts .. ", " ..
        Table.user_character.wis_pts ..
        " FROM " .. Table.user_character.tb_name .. 
        " WHERE " .. Table.user_character.id .. " = ?;"

        local resultCount = 10
        print("owned character query " .. ownedCharacterQuery)

        local result = SVI_DoQuerySTMT(host,ownedCharacterQuery,{t_id})

        -- print("owned character query result")

        -- local queryResultCount = 4
        -- for i = 1, #Query_val, queryResultCount do
            -- print("owned character ID " .. Query_val[i] )
            -- print("owned character level " .. Query_val[i+1])
            -- print("owned character exp " .. Query_val[i+2])
            -- print("owned character stats " .. Query_val[i+3])
        -- end

        for i = 1, tOwnedCount do
            local indexJump = resultCount * (i - 1)

            local baseCharacterStatQuery = "SELECT " .. Table.character_base.stats .. " FROM " .. Table.character_base.tb_name .. " WHERE " .. Table.character_base.character_id .. " = ?;"
            print(baseCharacterStatQuery)
            print(result[1 + indexJump])
            local result2 = SVI_DoQuerySTMT(host,baseCharacterStatQuery,{result[1 + indexJump]})

            print("rrr " .. result2[1])

            local characterStat, pos, err = JSON_Decode(result2[1])

            if err then
                print("Ke3 F3i117 exception (MainServerChanel.ClientData][ClientDataResponse.ClientData_Response_OwnedCharacters)  JSON decode error:", err)
            end

            if characterStat == nil then
                print("Ke3 F3i117 exception (MainServerChanel.ClientData][ClientDataResponse.ClientData_Response_OwnedCharacters)  JSON decode error: characterStat is nil")
                return
            end

            -- for k,v in pairs(characterStat) do
            --     print(k .. " : " .. v)
            -- end
            -- result map
            -- character_id - 1
            -- level - 2
            -- exp - 3
            -- stat_points - 4
            -- str_pts - 5
            -- vit_pts - 6
            -- dex_pts - 7
            -- agi_pts - 8
            -- int_pts - 9
            -- wis_pts - 10

            -- rewrite level value
            characterStat.level = tonumber(result[2 + indexJump])
            -- rewrite xp value
            characterStat.exp = tonumber(result[3 + indexJump])

            local stat_points = tonumber(result[4 + indexJump])
            local str_pts = tonumber(result[5 + indexJump])
            local vit_pts = tonumber(result[6 + indexJump])
            local dex_pts = tonumber(result[7 + indexJump])
            local agi_pts = tonumber(result[8 + indexJump])
            local int_pts = tonumber(result[9 + indexJump])
            local wis_pts = tonumber(result[10 + indexJump])
            -- should do a total stat_points check ( will do it )
            -- or may be this was calculated in the SQLite schema
            characterStat.strength = characterStat.strength + str_pts
            characterStat.vitality = characterStat.vitality + vit_pts
            characterStat.dexterity = characterStat.dexterity + dex_pts
            characterStat.agility = characterStat.agility + agi_pts
            characterStat.intelligence = characterStat.intelligence + int_pts
            characterStat.wisdom = characterStat.wisdom + wis_pts


            local encodedCharacterStat =  JSON_Encode(characterStat)

            -- print("encodedCharacterStat " .. encodedCharacterStat)

            AddExistingCharacter(t_id, result[1 + indexJump], result[2 + indexJump], result[3 + indexJump], encodedCharacterStat)
        end

    else
        print("no owned character")
        -- SendReliable(host,ip,t_guid,PacketChannel.UserChannel,UserResponse.OwnedCharacter_Start,{t_guid,"request_ok"})
        -- return
    end

    
    SendReliable(host,ip,t_guid,PacketChannel.UserChannel,UserResponse.OwnedCharacter_Start,{t_guid,"request_ok"})

    for k,v in pairs(ExistingCharacters[t_id]) do
        SendReliable(host,ip,t_guid,PacketChannel.UserChannel,UserResponse.OwnedCharacter_Data,{t_guid,k,CM_GetCharacterStatsAsString(v.dyobj)})

    end

    SendReliable(host,ip,t_guid,PacketChannel.UserChannel,UserResponse.OwnedCharacter_End,{t_guid,"ev"})

end

function AddExistingCharacter(userID, characterID, characterLevel, characterExp, characterStats)
    -- print("called AddExistingCharacter " .. characterID .. " " .. guid)

    if characterID == "S_Reimu" then
        ExistingCharacters[userID][characterID] = S_Reimu:new()
    elseif characterID == "S_Meiling" then
        ExistingCharacters[userID][characterID] = S_Meiling:new()
    elseif characterID == "S_Patchouli" then
        ExistingCharacters[userID][characterID] = S_Patchouli:new()
    elseif characterID == "S_Yukari" then
        ExistingCharacters[userID][characterID] = S_Yukari:new()
    end
    if ExistingCharacters[userID][characterID] ~= nil then
        -- print("AddExistingCharacter exist")
        ExistingCharacters[userID][characterID]:init(userID, characterID, characterStats)
        ExistingCharacters[userID][characterID]:setXP(characterExp)
        ExistingCharacters[userID][characterID]:setLVL(characterLevel)
    else
        -- print("AddExistingCharacter not exist " .. characterID)
    end
end

function RemoveExistingCharacter(userID)
    ExistingCharacters[userID] = nil
end