


print("clientCharacterHandler loaded")

ClientCharacterHandler_Host = nil

function ClientCharacterHandlerInit(host)
    ClientCharacterHandler_Host = host
end


--- Wrapper cpp_CharacterFillData 
---@Description: Fill the character data
---@param host pointer instace of ClientCharacterHandler
---@param characterName string The name of the character
---@param characterStats pointer instance of CharacterStats
function ClientCharacterHandler_fillData(host, characterName, characterStats)
    cpp_CharacterFillData(host, characterName, characterStats)
end

--- Wrapper cpp_GetCharacterData
--- @Description: Get the character data
--- @param host pointer instace of ClientCharacterHandler
--- @param characterName string The name of the character
--- @return pointer instance of CharacterDesc
function ClientCharacterHandler_getCharacterData(host, characterName)
    return cpp_GetCharacterData(host, characterName)
end

