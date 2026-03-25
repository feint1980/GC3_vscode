package.path = package.path .. ';../../Lua/TouhouTB/Combat/?.lua;' 

function CTD_AddIcon(host, characterID,side, order)
    cpp_TurnDisplayer_AddIcon(host, characterID,side,order)
end

function CTD_UpdateOrder(host)
    cpp_TurnDisplayer_UpdateOrder(host)
end


function CTD_GetCharacterIcon(host,characterID,side)
    return cpp_TurnDisplayer_GetCharacterIcon(host,characterID,side)
end

function CTD_SetCharacterOrder(character,order)
    cpp_TurnDisplayer_SetCharacterIconOrder(character,order)
end

function CTD_SetCharacterSpeedChange(character,changeValue)
    cpp_TurnDisplayer_SetCharacterIconSpeedChange(character,changeValue)
end

function CTD_SetCharacterSpeed(character,speed)
    cpp_TurnDisplayer_SetCharacterIconSpeed(character,speed)
end

function CTD_SetCharacterDisplaySpeed(character,speed)
    cpp_TurnDisplayer_SetCharacterIconDisplaySpeed(character,speed)
end

function CTD_SetUpdateSpeedChange(host, value)
    cpp_TurnDisplayer_SetUpdateSpeedChange(host,value)
end

