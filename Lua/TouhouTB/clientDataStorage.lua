-- clientDataStorage.lua
-- This module holds all client-side persistent data for the game

local GameStorage = {}

-- Player info: login-related, account ID, GUID, etc.
GameStorage.playerInfo = {
    userID = "",    -- string
    userGUID = "",  -- string
}

-- Data loaded/modified on the client side
GameStorage.clientSideLoadedInfo = {
    Character_Data_Tables = {},   -- table to hold character data
    Item_Data_Tables = {},        -- optional, for items
    Formation = {}                -- optional, for formation setup
}

-- Optional: utility functions to safely modify tables
function GameStorage.addCharacter(key, characterTable)
    if key and characterTable then
        GameStorage.clientSideLoadedInfo.Character_Data_Tables[key] = characterTable
    end
end

function GameStorage.getCharacter(key)
    return GameStorage.clientSideLoadedInfo.Character_Data_Tables[key]
end

return GameStorage