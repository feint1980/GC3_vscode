require "BS_Skill"

BS_Skill_LiangYiZhuang = {}
BS_Skill_LiangYiZhuang.__index = BS_Skill_LiangYiZhuang

function BS_Skill_LiangYiZhuang:create(character)
    local o = BS_Skill.new(self)

    o.id = "SKILL_LIANG_YI_ZHUANG"
    o.name = "Liang Yi Zhuang"
    o.isPassive = false
    o.description = "Switch to Liang Yi Zhuang stance"
    o.costText = "0.25 AP"

    o.availablePosition = BS_Required_Position.ALL

    o.targetPosition = BS_Target_Position:new(BS_Required_Position.ALL, false)

    self.__index = self
    return o
end