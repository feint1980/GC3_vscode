BS_Skill_ManaShield = {}
BS_Skill_ManaShield.__index = BS_Skill_ManaShield

function BS_Skill_ManaShield:create(character)
    local o = BS_Skill.new(self)

    o.id = "SKILL_MANA_SHIELD"
    o.name = "Mana Shield"
    o.isPassive = true
    o.description = "Absorbs " .. TextColor.color_TB_WIS .. "80% " .. TextColor.color_close .. "of incoming damage, converting\nit into mana loss instead of HP loss.\nIf her mana is depleted, the shield\nfails and she begins to take full damage."
    o.costText = "Passive"
    
    o.availablePosition = BS_Required_Position.ALL

    o.targetPosition = BS_Target_Position:new(BS_Required_Position.ALL, false)

    self.__index = self
    return o
end