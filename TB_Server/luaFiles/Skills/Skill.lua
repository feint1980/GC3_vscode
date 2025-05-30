

Tag.icon_soul = "<img=\"./Assets/TB_GUI/icons/soul.png\">"

---@class Skill
Skill = {
    name = "Skill",
    description = "Skill Description",
    effectTxt = "Effect",
    quoteTxt = "Quote",
    iconPath =  "./Assets/TB_GUI/faces/missing.png",
    -- special properties
    properties = {}
}

function Skill:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

