package.path = package.path .. ";../luaFiles/?.lua" 

require "battleWrapper"
require "BS_global"


CharacterInFormation = {
    userID = "",
    id = "",
    slotIndex = 0,
    rowPos = 0,
    colPos = 0,
    stats = nil
}

function CharacterInFormation:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function CharacterInFormation:init(userID,tId, tSlotIndex, tRowPos, tColPos)
    self.userID = userID
    self.id = tId
    self.slotIndex = tSlotIndex
    self.rowPos = tRowPos
    self.colPos = tColPos

    print("CharacterInFormation stat about to init")
    if ClientOwnedCharacters[userID] == nil then
        print("ClientOwnedCharacters[" .. userID .. "] is nil")
        return
    else
        if ClientOwnedCharacters[userID][tId] == nil then
            print("ClientOwnedCharacters[" .. userID .. "][" .. tId .. "] is nil")
            return
        else
            print("ClientOwnedCharacters[" .. userID .. "][" .. tId .. "] is valid")
            self.stats =  ClientOwnedCharacters[userID][tId]
            for k,v in pairs(self.stats) do
                print("stat " .. k .. " value " .. v)
            end
        end
    end
    -- self.stats =  ClientOwnedCharacters[userID][tId]
    -- if self.stats == nil then
    --     print("Ke3 F3i117 exception (MainServerChanel.ClientData][ClientDataResponse.ClientData_Response_OwnedCharacters)  JSON decode error:")
    -- end
end

BattleFormation = {
    index = 0,
    name = "",
    characters = {}
}

function BattleFormation:new(o)
    o = o or {}
    o.characters = {}
    setmetatable(o, self)
    setmetatable(o.characters, self.characters)
    self.__index = self
    return o
end

function BattleFormation:init(tIndex, tName)
    self.index = tIndex
    self.name = tName
    print("BattleFormation called with value " .. tIndex .. " " .. tName)
end

function BattleFormation:addCharacter(tCharacter)
    table.insert(self.characters, tCharacter)
end
