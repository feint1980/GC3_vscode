

CharacterManager_host = nil

function CharacterManagerInit(host)
    print("CharacterManagerInit called")
    CharacterManager_host = host
end

---@Description Wrapper of cpp_ParseCharacterFromString
---@param str string
---@return pointer instance of Character
function ParseCharacterFromString(str)
    return cpp_ParseCharacterFromString(str)
end

function CharacterManagerCreateCharacter(userID, characterID, strValue)
    CharacterManager_host = _G.CharacterManager_host
    local stats = ParseCharacterFromString(strValue)

    return cpp_CM_CreateCharacter(CharacterManager_host, userID, characterID, stats)
end

function CM_CharacterGetCharacter(userID, characterID)
    return cpp_CM_GetCharacter(CharacterManager_host, userID, characterID)
end

---@Description Wrapper of cpp_CM_CharacterGetAttribute
---@param characterDyobj pointer instance of Character
---@param attributeName string
---@return number
function CM_CharacterGetAttribute(characterDyobj, attributeName)
    return cpp_CM_CharacterGetAttribute(characterDyobj, attributeName)
end

---@Description Wrapper of cpp_CM_GetCharacterAttributeStr
---@param characterDyobj pointer instance of Character
---@param attributeName string
---@return string
function CM_CharacterGetAttributeStr(characterDyobj, attributeName)
    return cpp_CM_CharacterGetAttributeStr(characterDyobj, attributeName)
end

---@Description Wrapper of cpp_CM_CharacterSetAttribute
---@param characterDyobj pointer instance of Character
---@param attributeName string
---@param value number
function CM_CharacterSetAttribute(characterDyobj, attributeName, value)
    cpp_CM_CharacterSetAttribute(characterDyobj, attributeName, value)
end

---@Description Wrapper of cpp_CM_CharacterSetAttributeStr
---@param characterDyobj pointer instance of Character
---@param attributeName string
---@param value string
function CM_CharacterSetAttributeStr(characterDyobj, attributeName, value)
    cpp_CM_CharacterSetAttributeStr(characterDyobj, attributeName, value)
end

---@Description Wrapper of cpp_CM_GetCharacterStatsAsString
---@param characterDyobj pointer instance of Character
---@return string
function CM_GetCharacterStatsAsString(characterDyobj)
    return cpp_CM_GetCharacterStatsAsString(characterDyobj)
end