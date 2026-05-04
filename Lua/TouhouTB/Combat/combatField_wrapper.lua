
---@Description wrapper of cpp_CombatFiled_AddSlot
---@param host pointer instace CombatField
---@param col number
---@param row number
---@param side number
function CF_AddSlot(host,col,row,side)
    -- print("CF_AddSlot : col = " .. col .. ", row = " .. row .. ", side = " .. side)
    cpp_CombatField_AddSlot(host,col,row,side)
end

---@Description wrapper of cpp_CombatField_GetSlot
---@param host pointer instace CombatField
---@param col number
---@param row number
---@param side number
---@return pointer instance of CSlot
function CF_GetSlot(host, col, row, side)
    return cpp_CombatField_GetSlot(host, col, row, side)
end

---@Description wrapper of cpp_CombatField_AddCharacter
---@param host pointer instace CombatField
---@param col number
---@param row number
---@param side number
---@param animationPath string
---@param portraitPath string
---@return pointer instance of CombatCharacter
function CF_AddCharacter(host, col, row, side, animationPath, portraitPath)
    return cpp_CombatField_AddCharacter(host, col, row, side, animationPath, portraitPath)
end

---@Description wrapper of cpp_CombatField_GetCharacter
---@param host pointer instace CombatField
---@param characterID number
---@param side number   
---@return pointer instance of CombatCharacter
function CF_GetCharacter(host, characterID, side)
    return cpp_CombatField_GetCharacter(host, characterID, side)
end

---@Description wrapper of cpp_CombatField_SetCharacterStatInt
---@param character pointer instance of CombatCharacter
---@param statName string
---@param value number
function CF_SetCharacterStatFloat(character, statName, value)
    cpp_CombatField_SetCharacterStatFloat(character, statName, value)
end

---@Description wrapper of cpp_CombatField_SetCharacterStatInt
---@param character pointer instance of CombatCharacter
---@param statName string
---@param value number
function CF_SetCharacterStatString(character, statName, value)
    cpp_CombatField_SetCharacterStatStr(character, statName, value)
end

function CF_ListCharacterStats(character)
    cpp_CombatField_ListCharacterStats(character)
end


---- Banner

---@Description wrapper of cpp_getBannerInstance
---@param host pointer instance of BattleScene
---@return pointer instance of Banner
function CF_GetBannerInstance(host)
    return cpp_getBannerInstance(host)
end

---@Description wrapper of cpp_Banner_SetMsg
---@param banner pointer instance of Banner
---@param msg string
function Banner_SetMsg(banner, msg)
    cpp_Banner_SetMsg(banner, msg)
end

---@Description wrapper of cpp_Banner_ShowMsg
---@param banner pointer instance of Banner
---@param msg string
function Banner_ShowMsg(banner, msg)
    cpp_Banner_ShowMsg(banner, msg)
end

function CF_Banner_SetVisible(banner, value)
    cpp_Banner_SetVisible(banner, value)
end


-- General
function CF_Character_ParseFromString(str)
    return cpp_CFParseCharacterFromJson(str)
end


-- Field Info

function CF_GetFieldInfo(host)
    return cpp_getFieldInfoInstance(host)
end

function CF_FieldInfo_SetCharacter(host,characterID, side, statVal)

    print("CF_FieldInfo_SetCharacter called characterID = " .. characterID .. ", side = " .. side .. ", statVal = " .. statVal)
    cpp_FieldInfo_SetCharacter(host,characterID, side, statVal)
end