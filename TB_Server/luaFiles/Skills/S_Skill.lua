


---@class Skill
S_Skill = {
    name = "Skill",
    description = "Skill Description",
    effectTxt = "Effect",
    quoteTxt = "Quote",
    iconPath =  "./Assets/TB_GUI/faces/missing.png",
    -- special properties
    ID = "None",
    properties = {}
}

function S_Skill:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

