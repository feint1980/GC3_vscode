

CharacterManager_host = nil

function CharacterManagerInit(host)
    print("CharacterManagerInit called")
    CharacterManager_host = host
end

---@Description Wrapper of cpp_ParseCharacterFromString
---@param str string
---@return pointer instance of Character
function ParseCharacterFromString(str)
    return cpp_ParseCharacterFromString(CharacterManager_host, str)
end

