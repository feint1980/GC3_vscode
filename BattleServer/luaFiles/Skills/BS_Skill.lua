package.path = package.path .. ';../../Lua/system/objects/?.lua;'

require "compositeObject"

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


BS_TargetFilter = {
    SELF_SIDE_ONLY            = 1,    -- restrict to caster's own side
    OPPONENT_SIDE_ONLY        = 2,    -- restrict to opposing side
    REQUIRE_TARGET            = 4,    -- cell must be occupied
    REQUIRE_FREE              = 8,    -- cell must be empty
    FRONT_ONLY                = 16,   -- C1 only
    CENTER_ONLY               = 32,   -- C2 only
    BACK_ONLY                 = 64,   -- C3 only
    TOP_ROW_ONLY              = 128,  -- R1 only
    MIDDLE_ROW_ONLY           = 256,  -- R2 only
    BOTTOM_ROW_ONLY           = 512,  -- R3 only
    SELF_CHARACTER_ONLY       = 1024,  -- must be caster's own cell
    OTHER_CHARACTER_ONLY      = 2048,  -- must NOT be caster's own cell
}


BS_Target_Position = {
    filterFlag = 0, -- default ( no filter )
    maxDiffRow = 0, -- adjacent row you can target
    maxDiffCol = 0, -- adjacent col you can target
}

BS_Target_Position.__index = BS_Target_Position


function BS_Target_Position:new(tPosition)
    local o = setmetatable({}, self)
    o.position = tPosition
    self.__index = self
    return o
end

local function assertValidFilterMask(mask)
    local F = BS_TargetFilter
    assert((mask & (F.SELF_SIDE_ONLY | F.OPPONENT_SIDE_ONLY)) ~= (F.SELF_SIDE_ONLY | F.OPPONENT_SIDE_ONLY),
        "SELF_SIDE_ONLY + OPPONENT_SIDE_ONLY both set — leave both unset for either side")
    assert((mask & (F.REQUIRE_TARGET | F.REQUIRE_FREE)) ~= (F.REQUIRE_TARGET | F.REQUIRE_FREE),
        "REQUIRE_TARGET + REQUIRE_FREE both set — zero cells can ever match")
    assert((mask & (F.SELF_CHARACTER_ONLY | F.OTHER_CHARACTER_ONLY)) ~= (F.SELF_CHARACTER_ONLY | F.OTHER_CHARACTER_ONLY),
        "SELF_CHARACTER_ONLY + OTHER_CHARACTER_ONLY both set — zero cells can ever match")
    assert(not ((mask & F.SELF_CHARACTER_ONLY) ~= 0 and (mask & F.REQUIRE_FREE) ~= 0),
        "SELF_CHARACTER_ONLY + REQUIRE_FREE — caster's own cell is never empty, zero cells can ever match")
end


function BS_Target_Position:isCellLegal(casterCell, targetCell, occupant)
    local mask = self.filterMask
    local isSelfSide = (targetCell.side == casterCell.side)

    if (mask & BS_TargetFilter.SELF_SIDE_ONLY) ~= 0 and not isSelfSide then return false end
    if (mask & BS_TargetFilter.OPPONENT_SIDE_ONLY) ~= 0 and isSelfSide then return false end

    if (mask & BS_TargetFilter.REQUIRE_TARGET) ~= 0 and occupant == nil then return false end
    if (mask & BS_TargetFilter.REQUIRE_FREE) ~= 0 and occupant ~= nil then return false end

    local COL_BITS = BS_TargetFilter.FRONT_ONLY | BS_TargetFilter.CENTER_ONLY | BS_TargetFilter.BACK_ONLY
    if (mask & COL_BITS) ~= 0 then
        local colOk = (targetCell.col == 1 and (mask & BS_TargetFilter.FRONT_ONLY)  ~= 0)
                or (targetCell.col == 2 and (mask & BS_TargetFilter.CENTER_ONLY) ~= 0)
                or (targetCell.col == 3 and (mask & BS_TargetFilter.BACK_ONLY)   ~= 0)
        if not colOk then return false end
    end

    local ROW_BITS = BS_TargetFilter.TOP_ROW_ONLY | BS_TargetFilter.MIDDLE_ROW_ONLY | BS_TargetFilter.BOTTOM_ROW_ONLY
    if (mask & ROW_BITS) ~= 0 then
        local rowOk = (targetCell.row == 1 and (mask & BS_TargetFilter.TOP_ROW_ONLY)    ~= 0)
                or (targetCell.row == 2 and (mask & BS_TargetFilter.MIDDLE_ROW_ONLY) ~= 0)
                or (targetCell.row == 3 and (mask & BS_TargetFilter.BOTTOM_ROW_ONLY) ~= 0)
        if not rowOk then return false end
    end

    local isCasterCell = isSelfSide and targetCell.row == casterCell.row and targetCell.col == casterCell.col
    if (mask & BS_TargetFilter.SELF_CHARACTER_ONLY) ~= 0 and not isCasterCell then return false end
    if (mask & BS_TargetFilter.OTHER_CHARACTER_ONLY) ~= 0 and isCasterCell then return false end

    return true
end


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

