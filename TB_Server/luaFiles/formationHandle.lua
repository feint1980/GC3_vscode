package.path = package.path .. ";../luaFiles/?.lua"

require "serverWrapper"
-- require "clientHandling"
require "SV_global"

MessageHandling[PacketChannel.UserChannel][ UserResponse.Formation_Request] = function(host ,data, ip, guid)


    local t_guid, t_id, tData = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|$")

    if t_guid == nil or t_id == nil or tData == nil then
        print("Ke3 F3i117 exception (PacketChannel.UserChannel][UserResponse.Formation_Request)")
        return


    end

    print("request for Formation called from " .. t_guid .. " " .. t_id )

    --- guid check
    if CH_check_userValid(t_guid , guid ,t_id,ip) == false then
        return
    end
    --- start query 
    
    local cap = 4 -- FormationQuery_CheckCap(host,t_id)
    print("formation limit " .. cap)

    local getFormationQuery = "SELECT " .. Table.formation.id .. "," .. Table.formation.account_id .. "," .. Table.formation.name .. "," .. Table.formation.index .. " FROM " .. Table.formation.tb_name .. " WHERE " .. Table.formation.account_id .. " = ?;"
    SVI_DoQuerySTMT(host,getFormationQuery,{t_id})

    local formationQueryResult = Table_DeepCopy(Query_val)

    SendReliable(host,ip,t_guid,PacketChannel.UserChannel,UserResponse.Formation_Start, {t_guid , "request_ok",tostring(cap)})

    local queryResultSize = GetTableSize(Query_val)
    print("total formation count " .. queryResultSize)

    for k = 1, queryResultSize do
        print(Query_val[k])
    end

    for i = 1, #formationQueryResult, 4 do

        if(SVI_checkData{formationQueryResult[i],formationQueryResult[i+1],formationQueryResult[i+2],formationQueryResult[i+3]} == false) then
            print("data check failed")
            return
        end

        --1 (i) formation id
        --2 (i+1) account id
        --3 (i+2) formation name
        --4 (i+3) index
        local t_formationID = tostring(formationQueryResult[i])
        local t_accountID = tostring(formationQueryResult[i+1])
        local t_formationName = tostring(formationQueryResult[i+2])
        local t_index = tostring(formationQueryResult[i+3])

        print("index i " .. i)
        print("formation ID " .. tostring( t_formationID) )
        print("formation account ID " ..  tostring(t_accountID))
        print("formation name " ..  tostring(   t_formationName))
        print("formation index " .. tostring(  t_index))

        SendReliable(host,ip,t_guid,PacketChannel.UserChannel,UserResponse.Formation_Data,{tostring(formationQueryResult[i]),tostring(formationQueryResult[i+1]),tostring(formationQueryResult[i+2]), tostring(formationQueryResult[i+3])})

        local formationDataQuery = "SELECT " .. Table.formation_info.formation_id .. "," .. Table.formation_info.character_id .. "," .. Table.formation_info.slot_index .. "," .. Table.formation_info.row_pos .. "," .. Table.formation_info.col_pos .. " FROM " .. Table.formation_info.tb_name .. " WHERE " .. Table.formation_info.formation_id .. " = ?;"
        print("fill data " .. t_accountID)
        SVI_DoQuerySTMT(host,formationDataQuery,{t_accountID})

        print("sub query " .. formationDataQuery)
        local FormationDataQueryResult = Query_val
        local formationData = {}
        for j = 1, #FormationDataQueryResult, 5 do

            --1 (j) formation id
            --2 (j+1) character id
            --3 (j+2) slot index
            --4 (j+3) row pos
            --5 (j+4) col pos

            if(SVI_checkData{FormationDataQueryResult[j],FormationDataQueryResult[j+1],FormationDataQueryResult[j+2],FormationDataQueryResult[j+3],FormationDataQueryResult[j+4]} == false) then
                print("data check failed")
                return
            end

            local formationID = tostring(FormationDataQueryResult[j])
            local characterID = tostring(FormationDataQueryResult[j+1])
            local slotIndex = tostring(FormationDataQueryResult)[j+2]
            local rowPos = tostring(FormationDataQueryResult)[j+3]
            local colPos = tostring(FormationDataQueryResult)[j+4]

            SendReliable(host, ip, t_guid, PacketChannel.UserChannel, UserResponse.Formation_SubData,{formationID,characterID,slotIndex,rowPos,colPos})

            print(" info " .. FormationDataQueryResult[j] .. " " ..  FormationDataQueryResult[j+1] .. " " ..  FormationDataQueryResult[j+2] .. " " ..  FormationDataQueryResult[j+3] .. " " ..  FormationDataQueryResult[j+4])

        end
        print("sub query end")
    end
    SendReliable(host,ip,t_guid,PacketChannel.UserChannel,UserResponse.Formation_End, {t_guid , "request_done"})
    print("query end")
end

function FormationQuery_CheckCount(host,userID)

    local queryCountCmd= "SELECT COUNT(" .. Table.formation.id .. ") FROM " .. Table.formation.tb_name .. " WHERE " .. Table.formation.account_id .. " = ?;"
    SVI_DoQuerySTMT(host,queryCountCmd,{userID})

    return Query_val[1]
end

function FormationQuery_CheckCap(host,userID)
    local queryCountCmd= "SELECT " .. Table.account_stats.formmations .. " FROM " .. Table.account_stats.tb_name .. " WHERE " .. Table.account_stats.id .. " = ?;"
    print("queryCountCmd " .. queryCountCmd)
    SVI_DoQuerySTMT(host,queryCountCmd,{userID})

    return Query_val[1]
end

MessageHandling[PacketChannel.UserChannel][UserResponse.Formation_Add] = function(host ,data, ip, guid)
    local t_guid, t_id , formationName, formationIndex = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|([^|]+)|$")


    if ExtractDataCheck({t_guid,t_id,formationName,formationIndex},PacketChannel.UserChannel,UserResponse.Formation_Add) == false then 
        return
    end

    if CH_check_userValid(t_guid , guid ,t_id,ip) == false then
        return
    end

    local queryCount = FormationQuery_CheckCount(host,t_id)

    local queryCap = FormationQuery_CheckCap(host,t_id)

    print("queryCount " .. queryCount .. " queryCap " .. queryCap)

    if tonumber(queryCount)  > tonumber(queryCap) then
        print("formation limit reached " .. queryCount .. "/" .. queryCap)
        return
    else
        print("formation limit not reached " .. queryCount .. "/" .. queryCap)

        local addFormationQuery = 
        "INSERT INTO " .. Table.formation.tb_name .. " (" .. Table.formation.account_id .. "," .. Table.formation.name .. "," .. Table.formation.index .. ") VALUES (?, ?, " .. formationIndex .. ") ON CONFLICT (" .. Table.formation.account_id .. "," .. Table.formation.index .. ") DO UPDATE SET " .. Table.formation.name .. " = excluded." .. Table.formation.name .. ";"

        -- print("addFormationQuery " .. addFormationQuery)

        SVI_DoQuerySTMT(host,addFormationQuery,{t_id,formationName})

        SendReliable(host,ip, guid,PacketChannel.UserChannel,UserResponse.Formation_Request,{ "Formation added !","close" })
    end
    -- if t_guid == nil or t_id == nil or tData == nil then
    --     print("Ke3 F3i117 exception (PacketChannel.UserChannel][UserResponse.Formation_Add)")
    --     return
    -- end

end


MessageHandling[PacketChannel.UserChannel][UserResponse.Formation_Remove] = function(host ,data, ip, guid)

    local t_guid, t_id , formationName, formationIndex = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|([^|]+)|$")

    if ExtractDataCheck({t_guid,t_id,formationName,formationIndex},PacketChannel.UserChannel,UserResponse.Formation_Add) == false then 
        return
    end

    if CH_check_userValid(t_guid , guid ,t_id,ip) == false then
        return
    end

    print("extracted data " .. t_guid .. " " .. t_id .. " " .. formationName .. " " .. formationIndex)

    local removeFormationQuery = 
    "DELETE FROM " .. Table.formation.tb_name .. 
    " WHERE " .. Table.formation.account_id .. " = ? AND " 
    .. Table.formation.name .. " = ? AND " 
    .. Table.formation.index .. " = ?;"


    print("removeFormationQuery " .. removeFormationQuery)
    print("bound table " .. t_id .. " " .. formationName .. " " .. formationIndex )

    SVI_DoQuerySTMT(host,removeFormationQuery,{t_id,formationName,formationIndex})

end

MessageHandling[PacketChannel.UserChannel][UserResponse.Formation_Rename] = function(host ,data, ip, guid)

    print("formation rename called ")

    local t_guid, t_id , formationOldName, formationNewName, formationIndex = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|([^|]+)|([^|]+)|$")

    if ExtractDataCheck({t_guid,t_id,formationOldName,formationNewName,formationIndex},PacketChannel.UserChannel,UserResponse.Formation_Rename) == false then 
        return
    end

    if CH_check_userValid(t_guid , guid ,t_id,ip) == false then
        return
    end

    print("passed all the check, the data is " .. t_guid .. " " .. t_id .. " " .. formationOldName .. " " .. formationNewName .. " " .. formationIndex)

    local updateNameFormationQuery = 
    "UPDATE " .. Table.formation.tb_name .. 
    " SET " .. Table.formation.name .. " = ?" ..
    " WHERE " .. Table.formation.account_id .. " = ? AND " 
    .. Table.formation.name .. " = ? AND " 
    .. Table.formation.index .. " = ?;"

    SVI_DoQuerySTMT(host,updateNameFormationQuery,{formationNewName,t_id,formationOldName,formationIndex})

end

MessageHandling[PacketChannel.UserChannel][UserResponse.Formation_InfoUpdate] = function(host ,data, ip, guid)

    print("formation info update called ")
    local t_guid, t_id , formationName, formationIndex, infoSize, infoData = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|([^|]+)|([^|]+)|([^|]+)|$")

    if ExtractDataCheck({t_guid,t_id,formationName,formationIndex,infoSize,infoData},PacketChannel.UserChannel,UserResponse.Formation_InfoUpdate) == false then
        return
    end

    if CH_check_userValid(t_guid , guid ,t_id,ip) == false then
        return
    end

    print("passed all the check, the data is " .. t_guid .. " " .. t_id .. " " .. formationName .. " " .. formationIndex .. " " .. infoSize .. " " .. infoData)

    infoData = infoData:match("^#(.-)#$")

    local result = {}

    for name, index, row, col in infoData:gmatch("([^@]+)@(%d+)@(%d+)@(%d+)@") do
        table.insert(result, {
            name = name,
            index = tonumber(index),
            row = tonumber(row),
            col = tonumber(col)
        })
    end

    -- Print result
    for i, entry in ipairs(result) do
        print(string.format("Structure %d: name=%s, index=%d, row=%d, col=%d",
            i, entry.name, entry.index, entry.row, entry.col))
    end

    -- split from format :  #S_Patchouli@1@2@1@S_Meiling@2@2@2@#


    -- for i = 1, #infoData do
    --     print(infoData[i])
    -- end



end