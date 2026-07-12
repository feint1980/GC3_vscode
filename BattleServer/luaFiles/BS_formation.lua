package.path = package.path .. ";../luaFiles/?.lua" 

require "battleWrapper"
require "BS_global"

---@class BattleFormation
---@field index number
---@field name string
---@field characters table of BS_Character
BattleFormation = {}
BattleFormation.__index = BattleFormation

function BattleFormation:new()
    local o = setmetatable({}, self)
    o.index = 0
    o.name = ""
    o.characters = {}
    self.__index = self
    return o
end

function BattleFormation:init(tIndex, tName)
    self.index = tIndex
    self.name = tName
    -- print("BattleFormation called with value " .. tIndex .. " " .. tName)
end

function BattleFormation:addCharacter(tCharacter)
    print("adding character to formation " .. self.name .. " (" .. self.index .. ")")
    table.insert(self.characters, tCharacter)
    print("added, size now is " .. #self.characters)
end

