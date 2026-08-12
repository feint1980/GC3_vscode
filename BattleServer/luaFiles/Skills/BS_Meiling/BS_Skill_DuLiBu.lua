require "BS_Skill"

BS_Skill_DuLiBu = {}
BS_Skill_DuLiBu.__index = BS_Skill_DuLiBu

function BS_Skill_DuLiBu:create(character)
    local o = BS_Skill.new(self)

    o.id = "SKILL_DU_LI_BU"
    o.name = "Du Li Bu"
    o.isPassive = false
    o.description = "Switch to Du Li Bu stance"
    o.costText = "0.25 AP"

    o.availablePosition = BS_Required_Position.ALL

    o.targetPosition = BS_Target_Position:new(BS_Required_Position.ALL, false)

    self.__index = self
    return o
end