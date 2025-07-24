---@class Skill
Skill = {
    name = "Skill",
    description = "Skill Description",
    effect = "Effect",
    quote = "Quote",
    iconPath =  "./Assets/TB_GUI/faces/missing.png",
    -- special properties
    ID = "None",
    type = 0, ---- none 
    properties = {},
    cost = nil ,
    character = nil,
    ---pointer of SkillDesc
    dyobj = nil
}

function Skill:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    print("Skill new hereeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee ")
    return o
end

function Skill:init(host, characterName, Skillname)
    local desc = ClientSkillHandler_GetSkillDesc(host, characterName, Skillname)
    self.dyobj = desc
    self.name = ClientSkillHandler_GetSkillAttributeStr(desc, "name")
    self.description = ClientSkillHandler_GetSkillAttributeStr(desc, "description")
    self.effect = ClientSkillHandler_GetSkillAttributeStr(desc, "effect")
    self.quote = ClientSkillHandler_GetSkillAttributeStr(desc, "quote")
    self.iconPath = ClientSkillHandler_GetSkillAttributeStr(desc, "iconPath")
    self.ID = ClientSkillHandler_GetSkillAttributeStr(desc, "ID")
    self.type = ClientSkillHandler_GetSkillAttributeInt(desc, "type")

end

function Skill:onSelect()

end

function Skill:onCancel()

end

function Skill:setDesc(desc)

end

function Skill_SetDesc(dyobj, desc)

end

