
---@Description wrapper of cpp_CombatFiled_AddSlot
---@param host pointer instace CombatField
---@param col number
---@param row number
---@param side number
function CF_AddSlot(host,col,row,side)
    -- print("CF_AddSlot : col = " .. col .. ", row = " .. row .. ", side = " .. side)
    cpp_CombatField_AddSlot(host,col,row,side)
end

function CF_GetSlot(host, col, row, side)
    return cpp_CombatField_GetSlot(host, col, row, side)
end

function CF_AddCharacter(host, col, row, side, animationPath, portraitPath)
    return cpp_CombatField_AddCharacter(host, col, row, side, animationPath, portraitPath)
end

function CF_GetCharacter(host, characterID, side)
    return cpp_CombatField_GetCharacter(host, characterID, side)
end

function CF_SetCharacterStatFloat(character, statName, value)
    cpp_CombatField_SetCharacterStatFloat(character, statName, value)
end

function CF_SetCharacterStatString(character, statName, value)
    cpp_CombatField_SetCharacterStatStr(character, statName, value)
end

function CF_ListCharacterStats(character)
    cpp_CombatField_ListCharacterStats(character)
end
