BS_Fate_Favor = {}
BS_Fate_Favor.__index = BS_Fate_Favor

function BS_Fate_Favor:create(character)
    local o = BS_Skill.new(self)

    o.id = "SKILL_FATE_FAVOR"
    o.name = "Fate's Favor"
    o.isPassive = true
    o.description = "On turn start, Reimu has a " .. TextColor.color_orange .. "10%" .. TextColor.color_close .. " base chance\n plus a bonus equal to her missing HP percentage, to gain 1 of these random buffs below:\n \
        > Heal 10% max HP.\n\
        > Gain 30% crit chance (only 1).\n\
        > Gain 30% evade chance.\n\
        > Remove all debuffs.\n\
        Lasts 1 turn."
    o.costText = "Passive"

    o.availablePosition = BS_Required_Position.ALL

    o.targetPosition = BS_Target_Position:new(BS_Required_Position.ALL, false)

    self.__index = self
    return o
end