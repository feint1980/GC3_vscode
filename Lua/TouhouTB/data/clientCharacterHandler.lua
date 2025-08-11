

print("clientCharacterHandler loaded")

ClientCharacterHandler_Host = nil

function ClientCharacterHandlerInit(host)
    ClientCharacterHandler_Host = host
end


--- Wrapper cpp_CharacterFillData 
---@Description: Fill the character data
---@param host pointer instace of ClientCharacterHandler
---@param name string
---@param characterName string The name of the character
---@param characterStats pointer instance of CharacterStats
function ClientCharacterHandler_fillData(host, name, characterName, characterStats)
    cpp_CharacterFillData(host,name, characterName, characterStats)
end

--- Wrapper cpp_GetCharacterData
--- @Description: Get the character data
--- @param host pointer instace of ClientCharacterHandler
--- @param name string
--- @param characterName string The name of the character
--- @return pointer instance of CharacterDesc
function ClientCharacterHandler_getCharacterData(host, name, characterName)
    return cpp_GetCharacterData(host,name, characterName)
end

