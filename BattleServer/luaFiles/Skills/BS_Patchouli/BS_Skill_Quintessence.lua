package.path = package.path .. ";../../luaFiles/?.lua" .. ";../luaFiles/Skills/?.lua"

require "BS_Skill"

BS_Skill_Quintessence = {}
BS_Skill_Quintessence.__index = BS_Skill_Quintessence


function BS_Skill_Quintessence:create(character)
    local o = BS_Skill.new(self)

    o.id = "SKILL_QUINTESSENCE"
    o.name = "Quintessence"

    o.cost = BS_SkillCost:new({ apCost = 0.5 })

    o.description = "Change the combination of the Philosopher's \nStones, each orb granted (per orbs):\
 > Metal: Gain 2% crit chance\
 > Wood: Gain 1% evade chance\
 > Fire: Gain 2% magic damage amplification\
 > Water: Gain 2% of total mana regeneration\
 > Earth: Gain 2% physical protection."
    o.costText =  TextColor.color_orange .. "0.5 AP" .. TextColor.color_close

    o.requiredPosition = BS_Required_Position.ALL
    o.targetPosition = BS_Target_Position:new()

    o.isPassive = false
    o.needTarget = false

    self.__index = self
    return o
end
