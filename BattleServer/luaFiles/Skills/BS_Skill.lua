
BS_SkillCost = {}
BS_SkillCost.__index = BS_SkillCost

function BS_SkillCost:new(o)
    o = o or {}
    setmetatable(o, self)
    o.apCost = o.apCost or 0
    o.manaCost = o.manaCost or 0
    o.spCost = o.spCost or 0
    o.hpCost = o.hpCost or 0
    o.manaPercentCost = o.manaPercentCost or 0
    o.hpPercentCost = o.hpPercentCost or 0
    self.__index = self
    return o
end

--[[
Actual View 
[3][2][1] | [1][2][3] 
[3][2][1] | [1][2][3]
[3][2][1] | [1][2][3]
ruling : 
1 -> front 
2 -> center 
3 -> back
--]]
BS_Required_Position = {

    R1C1 = 1,  R1C2 = 2,   R1C3 = 4,
    R2C1 = 8,  R2C2 = 16,  R2C3 = 32,
    R3C1 = 64, R3C2 = 128, R3C3 = 256,
}

BS_Required_Position.TOP    = BS_Required_Position.R1C1 | BS_Required_Position.R1C2 | BS_Required_Position.R1C3
BS_Required_Position.MIDDLE = BS_Required_Position.R2C1 | BS_Required_Position.R2C2 | BS_Required_Position.R2C3
BS_Required_Position.BOTTOM = BS_Required_Position.R3C1 | BS_Required_Position.R3C2 | BS_Required_Position.R3C3

BS_Required_Position.FRONT  = BS_Required_Position.R1C1 | BS_Required_Position.R2C1 | BS_Required_Position.R3C1
BS_Required_Position.CENTER = BS_Required_Position.R1C2 | BS_Required_Position.R2C2 | BS_Required_Position.R3C2
BS_Required_Position.BACK   = BS_Required_Position.R1C3 | BS_Required_Position.R2C3 | BS_Required_Position.R3C3
BS_Required_Position.CENTER_CENTER = BS_Required_Position.R2C2

BS_Required_Position.ALL = BS_Required_Position.TOP | BS_Required_Position.MIDDLE | BS_Required_Position.BOTTOM

BS_Target_Position = {}
BS_Target_Position.__index = BS_Target_Position

function BS_Target_Position:new(tPosition, tIsOpposite)
    local o = setmetatable({}, self)
    o.position = tPosition
    o.isOpposite = tIsOpposite
    self.__index = self
    return o
end
-- function BS_Target_Position:init(tPosition, tIsOpposite)
--     self.position = tPosition
--     self.isOpposite = tIsOpposite
-- end

BS_DMG_Type = {
    PHYSICAL = 0,
    MAGIC = 1,
    TRUE = 2
}

BS_DMG = {}
BS_DMG.__index = BS_DMG

function BS_DMG:new(o)
    o = o or {}
    setmetatable(o, self)
    o.dmgValue = o.dmgValue or 0
    o.dmgType = o.dmgType or BS_DMG_Type.PHYSICAL
    self.__index = self
    return o
end

---@class BS_Skill
BS_Skill = {}
BS_Skill.__index = BS_Skill

function BS_Skill:new(o)
    o = o or {}
    setmetatable(o, self)
    o.id = o.id or  "ID_INVALID"
    o.name = o.name or "Skill Name"
    o.cost = o.cost or BS_SkillCost:new()
    o.dmg = o.dmg or BS_DMG:new()

    o.description = o.description or "Skill Description"
    o.costText = o.costText or "TKD"

    o.requiredPosition = o.requiredPosition or BS_Required_Position.ALL
    o.targetPosition = o.targetPosition or BS_Target_Position:new(BS_Required_Position.ALL, false)

    o.isPassive = o.isPassive or false

    self.__index = self

    return o
end


function BS_Skill:create(Character)
    -- base
end

return BS_Skill

