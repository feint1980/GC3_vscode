require "BS_Skill"

BS_Skill_Pubu = {}
BS_Skill_Pubu.__index = BS_Skill_Pubu

function BS_Skill_Pubu:create(character)
    local o = BS_Skill.new(self)

    o.id = "SKILL_PUBU"
    o.name = "Pu Bu"

    o.cost = BS_SkillCost:new({ apCost = 0.5 })

    --o.dmg pass ( no dmg )

    o.description = "Switch to Pu Bu stance"
    o.costText = "0.5 AP"

    o.requiredPosition = BS_Required_Position.ALL
    o.targetPosition = BS_Target_Position:new()

    o.needTarget = true
    o.isPassive = false

    self.__index = self
    return o
end