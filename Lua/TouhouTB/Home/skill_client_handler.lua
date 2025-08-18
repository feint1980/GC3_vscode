package.path = package.path .. ';../../Lua/TouhouTB/skills/?.lua;'

require "homeGlobal"
require "Skill"

Skill_Serialized_Table = _G.Skill_Serialized_Table
local t_skill_count = 0
ClientMessageHandling[PacketChannel.UserChannel][UserResponse.SkillInfo_Start] = function(host,data, guid)
    local t_guid, tData = string.match(data, "^|([^|]+)|([^|]+)|$")

    if t_guid == nil or tData == nil then
        print("Ke3 F3i117 exception (PacketChannel.UserChannel][UserResponse.SkillInfo_Start)")
        return
    end

    print("recieve data " .. tData .. " from " .. t_guid)
    for k,v in pairs(Skill_Serialized_Table) do
        Skill_Serialized_Table[k] = nil
    end
    Skill_Serialized_Table = {}
end

ClientMessageHandling[PacketChannel.UserChannel][UserResponse.SkillInfo_Data] = function(host,data, guid)

    local characterKey , skillKey, skillValue = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|$") 

    if characterKey == nil or skillKey == nil or skillValue == nil then
        print("Ke3 F3i117 exception (PacketChannel.UserChannel][UserResponse.SkillInfo_Data)")
        return
    end

    if Skill_Serialized_Table[characterKey] == nil then
        Skill_Serialized_Table[characterKey] = {}
    end
    if Skill_Table[characterKey] == nil then
        Skill_Table[characterKey] = {}
    end

    Skill_Serialized_Table[characterKey][skillKey] = skillValue

    ClientSkillHandler_AddSkillDesc(Home_SkillHandlerPtr,characterKey, skillKey, skillValue)

    Skill_Table[characterKey][skillKey] = Skill:new()
    Skill_Table[characterKey][skillKey]:init(Home_SkillHandlerPtr,characterKey, skillKey)


    print("skill check bro |")
    print(Skill_Table[characterKey][skillKey].name)


    t_skill_count = t_skill_count + 1
end


ClientMessageHandling[PacketChannel.UserChannel][UserResponse.SkillInfo_End] = function(host,data, guid)
    local tData = string.sub(data,2,string.len(data) - 1)
    -- if tData == "ev" then 
        -- print("skill transfer ended, total skill:" .. tostring(t_skill_count))
        -- print("check data")
        -- for k,v in pairs(Skill_Serialized_Table) do
        --     for k2,v2 in pairs(v) do
        --         print(k .. " " .. k2 .. " " .. v2)
        --     end
        -- end
    -- end
end


--- Wrapper 
--- @description wrapper of cppParseCharacterFromJson
--- @param str string
--- @return pointer instance of SkillStat
function Client_Parse_SkillSetFromStr(str)
    return cpp_SkillStat_parseFromStr(str)
end

---@Description Wrapper of cpp_Skill_AddSkillStats
---@param characterKey string
---@param skillKey string
---@param skillValue string
---@return pointer instance of SkillDesc
function ClientSkillHandler_AddSkillDesc(host,characterKey, skillKey, skillValue)
    return cpp_Skill_AddSkillDesc(host,characterKey, skillKey, skillValue)
end

---@Description Wrapper of cpp_Skill_GetSkillDesc
---@param characterKey string
---@param skillKey string
---@return pointer instance of SkillDesc
function ClientSkillHandler_GetSkillDesc(host,characterKey, skillKey)
    return cpp_Skill_GetSkillDesc(host,characterKey, skillKey)
end

---@Description Wrapper of cpp_Skill_GetSkillAttributeInt
---@param skillDesc pointer instance of SkillDesc
---@param attribute string
---@return number
function ClientSkillHandler_GetSkillAttributeInt(skillDesc, attribute)
    return cpp_Skill_GetSkillAttributeInt(skillDesc, attribute)
end

---@Description Wrapper of cpp_Skill_GetSkillAttributeStr
---@param skillDesc pointer instance of SkillDesc
---@param attribute string
---@return string
function ClientSkillHandler_GetSkillAttributeStr(skillDesc, attribute)
    return cpp_Skill_GetSkillAttributeStr(skillDesc, attribute)
end


