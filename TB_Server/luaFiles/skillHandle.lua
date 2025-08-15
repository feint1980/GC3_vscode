package.path = package.path .. ";../luaFiles/?.lua"

require "serverWrapper"
require "SV_global"

---@Descriptiopn Handle skill request
MessageHandling[PacketChannel.UserChannel][UserResponse.SkillInfo] = function(host ,data, ip, guid)
    -- print("Request skill info get ")
    local t_guid, tData = string.match(data, "^|([^|]+)|([^|]+)|$")

    if t_guid == nil or tData == nil then
        print("Ke3 F3i117 exception (PacketChannel.UserChannel][UserResponse.SkillInfo)")
        return
    end
    -- print("recieve data " .. tData .. " from " .. t_guid)

    if CH_FindClient(t_guid) ~= nil then
        -- print("user valid " .. CH_FindClient(t_guid).name)
        --- start the send data sequences
        SendReliable(host,ip,guid,PacketChannel.UserChannel,UserResponse.SkillInfo_Start,{t_guid, "sequence_start"})
        for k,v in pairs(Skill_Serialized_Table) do
            for k2,v2 in pairs(v) do
                SendReliable(host,ip,guid,PacketChannel.UserChannel,UserResponse.SkillInfo_Data,{k,k2,v2})
            end
        end
        SendReliable(host,ip,guid,PacketChannel.UserChannel,UserResponse.SkillInfo_End,{"ev"})
    else
        print("invalid user")
        return
    end
end
