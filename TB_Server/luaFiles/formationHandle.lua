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

    local getFormationQuery = "SELECT " .. Table.formation.id .. "," .. Table.formation.account_id .. " FROM " .. Table.formation.tb_name .. " WHERE " .. Table.formation.account_id .. " = ?;"
    SVI_DoQuerySTMT(host,getFormationQuery,{t_id})
    for i = 1, #Query_val, 2 do
        print("formation " .. Query_val[i] .. " " .. Query_val[i+1])
    end

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

MessageHandling[PacketChannel.UserChannel][ UserResponse.Formation_Add] = function(host ,data, ip, guid)
    local t_guid, t_id , tData = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|$")


    if ExtractDataCheck({t_guid,t_id,tData},PacketChannel.UserChannel,UserResponse.Formation_Add) == false then 
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

        -- local addFormationQuery = "INSERT INTO " .. Table.formation.tb_name .. " (" .. Table.formation.id .. "," .. Table.formation.account_id .. ") VALUES (NULL, ?);"
        -- SVI_DoQuerySTMT(host,addFormationQuery,{t_id})
    end
    -- if t_guid == nil or t_id == nil or tData == nil then
    --     print("Ke3 F3i117 exception (PacketChannel.UserChannel][UserResponse.Formation_Add)")
    --     return
    -- end

end