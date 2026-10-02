require "BS_Skill"

BS_Skill_LiangYiZhuang = {}
BS_Skill_LiangYiZhuang.__index = BS_Skill_LiangYiZhuang

function BS_Skill_LiangYiZhuang:create(character)
    local o = BS_Skill.new(self)

    o.id = "SKILL_LIANG_YI_ZHUANG"
    o.name = "Liang Yi Zhuang"

    o.cost = BS_SkillCost:new({ apCost = 0.5 })

    o.description = "Switch to Liang Yi Zhuang stance"
    o.costText = "0.5 AP"

    o.requiredPosition = BS_Required_Position.ALL
    o.targetPosition = BS_Target_Position:new()

    o.isPassive = false
    o.needTarget = false

    self.__index = self
    return o
end