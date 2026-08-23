BS_Skill_FateFavor = {}
BS_Skill_FateFavor.__index = BS_Skill_FateFavor

function BS_Skill_FateFavor:create(character)
    local o = BS_Skill.new(self)

    o.id = "SKILL_FATE_FAVOR"
    o.name = "Fate's Favor"
    o.isPassive = true
    o.description = "On turn start, Reimu has a " .. TextColor.color_orange .. "10%" .. TextColor.color_close .. " base chance\n plus a bonus equal to her missing HP\n percentage, to gain 1 of these random\n buffs below:\
    > Heal 10% max HP.\
    > Gain 30% crit chance (only 1 hit).\
    > Gain 30% evade chance.\
    > Remove all debuffs.\
    Lasts 1 turn."
    o.costText = "Passive"

    o.availablePosition = BS_Required_Position.ALL

    o.targetPosition = BS_Target_Position:new(BS_Required_Position.ALL, false)

    self.__index = self
    return o
end