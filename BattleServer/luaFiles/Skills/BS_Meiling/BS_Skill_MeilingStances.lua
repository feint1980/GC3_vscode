require "BS_Skill"

BS_Skill_MeilingStances = {}
BS_Skill_MeilingStances.__index = BS_Skill_MeilingStances

function BS_Skill_MeilingStances:create(character)
    local o = BS_Skill.new(self)

    o.id = "SKILL_MEILING_STANCES"
    o.name = "Meiling Stances"
    o.isPassive = true
    o.description = 
    "Meiling can switch between 3 stances each\
    stance grant difference buffs:\
 > Liang Yi Zhuang: grant +5% physic attack,\
    +5% physic def\
 > Pu Bu: grant -40% physic attack,\
    +25% physic def\
 > Du Li Bu: grant +20% physic attack,\
    -40% physic def"
    o.costText = "Passive"

    o.availablePosition = BS_Required_Position.ALL

    o.targetPosition = BS_Target_Position:new(BS_Required_Position.ALL, false)

    self.__index = self
    return o
end