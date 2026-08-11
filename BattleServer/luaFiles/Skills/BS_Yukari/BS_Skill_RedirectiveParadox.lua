
BS_Skill_RedirectiveParadox = {}
BS_Skill_RedirectiveParadox.__index = BS_Skill_RedirectiveParadox

function BS_Skill_RedirectiveParadox:create(character)
    local o = BS_Skill.new(self)

    o.id = "SKILL_REDIRECTIVE_PARADOX"
    o.name = "Redirective Paradox"
    o.isPassive = true
    o.description = "When targeted, Yukari has 17% to redirect the attack / projectile to a random character (including allies)."
    o.costText = "Passive"

    o.availablePosition = BS_Required_Position.ALL

    o.targetPosition = BS_Target_Position:new(BS_Required_Position.ALL, false)

    self.__index = self
    return o

end

