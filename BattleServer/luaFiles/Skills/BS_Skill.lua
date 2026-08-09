

BS_SkillCost = {}
BS_SkillCost.__index = BS_SkillCost



BS_Skill = {}
BS_Skill.__index = BS_Skill

function BS_Skill:new()
    local o = setmetatable({}, self)
    o.id = "ID_INVALID"
    o.name = "Skill Name"
    o.description = "Skill Description"
    
    self.__index = self
    return o
end

return BS_Skill

