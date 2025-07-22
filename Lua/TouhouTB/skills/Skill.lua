

---@class Skill
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
