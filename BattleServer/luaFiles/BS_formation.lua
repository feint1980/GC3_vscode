package.path = package.path .. ";../luaFiles/?.lua" 

require "battleWrapper"
require "BS_global"


CharacterInFormation = {
    id = "",
    slotIndex = 0, 
    rowPos = 0,
    colPos = 0
}

function CharacterInFormation:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function CharacterInFormation:init(tId, tSlotIndex, tRowPos, tColPos)
    self.id = tId
    self.slotIndex = tSlotIndex
    self.rowPos = tRowPos
    self.colPos = tColPos
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
