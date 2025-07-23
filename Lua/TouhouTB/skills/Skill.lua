---@class Skill
Skill = {
    name = "Skill",
    description = "Skill Description",
    effectTxt = "Effect",
    quoteTxt = "Quote",
    iconPath =  "./Assets/TB_GUI/faces/missing.png",
    -- special properties
    ID = "None",
    type = 0, ---- none 
    properties = {},
    cost = nil ,
    character = nil
}

function Skill:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function Skill:init( tCharacter,tCost , tProperties)
    self.character = tCharacter
    self.cost = tCost
    self.properties = tProperties
end

function Skill:onSelect()

end

function Skill:onCancel()

end

function Skill:setStat(desc)

end


function Skill_SetStat(dyobj, desc)

end
---- List of event 
