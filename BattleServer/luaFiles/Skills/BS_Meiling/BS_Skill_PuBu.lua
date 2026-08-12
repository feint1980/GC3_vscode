require "BS_Skill"

BS_Skill_Pubu = {}
BS_Skill_Pubu.__index = BS_Skill_Pubu

function BS_Skill_Pubu:create(character)
    local o = BS_Skill.new(self)

    o.id = "SKILL_PUBU"
    o.name = "Pu Bu"
    o.isPassive = false
    o.description = "Switch to Pu Bu stance"
    o.costText = "0.25 AP"

    o.availablePosition = BS_Required_Position.ALL

    o.targetPosition = BS_Target_Position:new(BS_Required_Position.ALL, false)

    self.__index = self
    return o
end