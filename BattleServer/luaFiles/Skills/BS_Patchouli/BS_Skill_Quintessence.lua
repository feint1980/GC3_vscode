package.path = package.path .. ";../../luaFiles/?.lua" .. ";../luaFiles/Skills/?.lua"

require "BS_Skill"

BS_Skill_Quintessence = {}
BS_Skill_Quintessence.__index = BS_Skill_Quintessence


function BS_Skill_Quintessence:create(character)
    local o = BS_Skill.new(self)

    o.id = "SKILL_QUINTESSENCE"
    o.name = "Quintessence"
    o.isPassive = false
    o.description = "Change the combination of the Philosopher's Stones, \neach type of orbs has a different buff.\n\
        > Metal: Gain 2% crit chance (per orb)\n\
        > Wood: Gain 1% evade chance (per orb)\n\
        > Fire: Gain 2% magic damage amplification (per orb)\n\
        > Water: Gain 2% of total mana regeneration (per orb)\n\
        > Earth: Gain 2% physical protection (per orb)\n."
    o.costText =  TextColor.color_orange .. "0.25 AP" .. TextColor.color_close

    o.availablePosition = BS_Required_Position.ALL

    o.targetPosition = BS_Target_Position:new(BS_Required_Position.ALL, false)

    self.__index = self
    return o
end
