package.path = package.path .. ";../luaFiles/Characters/?.lua" 

require "SV_global"
require "S_Character"

---@table EventType
---@Description 

--- Type of skill
Type = {
    innate = 1,
    passive = 2,
    active = 3
}

--- Cost of skill
Cost = {
    mana = 0,
    sp = 0,
    turn = 0
}

function Cost:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

---@class S_Skill
---@field name string
---@field description string
---@field effectTxt string
---@field quoteTxt string
---@field iconPath string
---@field ID string
---@field type number
---@field properties table
---@field cost pointer instance of Cost
S_Skill = {
    name = "Skill",
    description = "Skill Description",
    effectTxt = "Effect",
    quoteTxt = "Quote",
    iconPath =  "./Assets/TB_GUI/faces/missing.png",
    -- special properties
    ID = "None",
    type = 0, ---- none 
    properties = {},
    ---@type pointer instance of Cost
    cost = nil ,
    character = nil
}

function S_Skill:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function S_Skill:init( tCharacter,tCost , tProperties)
    self.character = tCharacter
    self.cost = tCost
    self.properties = tProperties
end

function S_Skill:onSelect()

end

function S_Skill:onCancel()

end

---- List of event 
