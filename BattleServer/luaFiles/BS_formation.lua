package.path = package.path .. ";../luaFiles/?.lua" 

require "battleWrapper"
require "BS_global"


BattleFormation = {
    index = 0,
    name = "",
    ---@type table of BS_Character
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
    -- print("BattleFormation called with value " .. tIndex .. " " .. tName)
end

function BattleFormation:addCharacter(tCharacter)
    table.insert(self.characters, tCharacter)
end
