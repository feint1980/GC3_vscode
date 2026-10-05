
Combat_Skill_Cost = {}
Combat_Skill_Cost.__index = Combat_Skill_Cost

function Combat_Skill_Cost:new(o)
    o = o or {}
    setmetatable(o, self)
    o.apCost = o.apCost or 0
    o.manaCost = o.manaCost or 0
    o.spCost = o.spCost or 0
    o.hpCost = o.hpCost or 0
    o.manaPercentCost = o.manaPercentCost or 0 -- 0..100, percent of MAX mana
    o.hpPercentCost = o.hpPercentCost or 0     -- 0..100, percent of MAX hp
    self.__index = self
    return o
end

Combat_Skill_Required_Position = {

    R1C1 = 1,  R1C2 = 2,   R1C3 = 4,
    R2C1 = 8,  R2C2 = 16,  R2C3 = 32,
    R3C1 = 64, R3C2 = 128, R3C3 = 256,
}


Combat_Skill_Required_Position.TOP    = Combat_Skill_Required_Position.R1C1 | Combat_Skill_Required_Position.R1C2 | Combat_Skill_Required_Position.R1C3
Combat_Skill_Required_Position.MIDDLE = Combat_Skill_Required_Position.R2C1 | Combat_Skill_Required_Position.R2C2 | Combat_Skill_Required_Position.R2C3
Combat_Skill_Required_Position.BOTTOM = Combat_Skill_Required_Position.R3C1 | Combat_Skill_Required_Position.R3C2 | Combat_Skill_Required_Position.R3C3

Combat_Skill_Required_Position.FRONT  = Combat_Skill_Required_Position.R1C1 | Combat_Skill_Required_Position.R2C1 | Combat_Skill_Required_Position.R3C1
Combat_Skill_Required_Position.CENTER = Combat_Skill_Required_Position.R1C2 | Combat_Skill_Required_Position.R2C2 | Combat_Skill_Required_Position.R3C2
Combat_Skill_Required_Position.BACK   = Combat_Skill_Required_Position.R1C3 | Combat_Skill_Required_Position.R2C3 | Combat_Skill_Required_Position.R3C3
Combat_Skill_Required_Position.CENTER_CENTER = Combat_Skill_Required_Position.R2C2

Combat_Skill_Required_Position.ALL = Combat_Skill_Required_Position.TOP | Combat_Skill_Required_Position.MIDDLE | Combat_Skill_Required_Position.BOTTOM

Combat_Skill_Target_Filter = {
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

-- CHANGED: moved above Combat_Skill_Target_Position:new so it can be called from there
local function assertValidFilterMask(mask)
    local F = Combat_Skill_Target_Filter
    assert((mask & (F.SELF_SIDE_ONLY | F.OPPONENT_SIDE_ONLY)) ~= (F.SELF_SIDE_ONLY | F.OPPONENT_SIDE_ONLY),
        "SELF_SIDE_ONLY + OPPONENT_SIDE_ONLY both set — leave both unset for either side")
    assert((mask & (F.REQUIRE_TARGET | F.REQUIRE_FREE)) ~= (F.REQUIRE_TARGET | F.REQUIRE_FREE),
        "REQUIRE_TARGET + REQUIRE_FREE both set — zero cells can ever match")
    assert((mask & (F.SELF_CHARACTER_ONLY | F.OTHER_CHARACTER_ONLY)) ~= (F.SELF_CHARACTER_ONLY | F.OTHER_CHARACTER_ONLY),
        "SELF_CHARACTER_ONLY + OTHER_CHARACTER_ONLY both set — zero cells can ever match")
    assert(not ((mask & F.SELF_CHARACTER_ONLY) ~= 0 and (mask & F.REQUIRE_FREE) ~= 0),
        "SELF_CHARACTER_ONLY + REQUIRE_FREE — caster's own cell is never empty, zero cells can ever match")
end


Combat_Skill_Target_Position = {
    filterFlag = 0,
    rowRange = nil, -- nil = unrestricted; inclusive distance from caster's row
    colRange = nil, -- nil = unrestricted; inclusive distance from caster's column
}
Combat_Skill_Target_Position.__index = Combat_Skill_Target_Position

function Combat_Skill_Target_Position:new(filterFlag, rowRange, colRange)
    -- assertValidFilterMask(filterFlag)
    local o = {}
    setmetatable(o, Combat_Skill_Target_Position)

    o.filterFlag = filterFlag or 0
    o.rowRange = rowRange or nil
    o.colRange = colRange or nil
    assertValidFilterMask(o.filterFlag)
    return o
end

-- function Combat_Skill_Target_Position:isCellLegal(casterCell, targetCell, occupant)
--     local mask = self.filterFlag -- CHANGED: was self.filterMask (nil -> runtime error)
--     local isSelfSide = (targetCell.side == casterCell.side)

--     if (mask & Combat_Skill_Target_Filter.SELF_SIDE_ONLY) ~= 0 and not isSelfSide then return false end
--     if (mask & Combat_Skill_Target_Filter.OPPONENT_SIDE_ONLY) ~= 0 and isSelfSide then return false end

--     if (mask & Combat_Skill_Target_Filter.REQUIRE_TARGET) ~= 0 and occupant == nil then return false end
--     if (mask & Combat_Skill_Target_Filter.REQUIRE_FREE) ~= 0 and occupant ~= nil then return false end

--     local COL_BITS = Combat_Skill_Target_Filter.FRONT_ONLY | Combat_Skill_Target_Filter.CENTER_ONLY | Combat_Skill_Target_Filter.BACK_ONLY
--     if (mask & COL_BITS) ~= 0 then
--         local colOk = (targetCell.col == 1 and (mask & Combat_Skill_Target_Filter.FRONT_ONLY)  ~= 0)
--                 or (targetCell.col == 2 and (mask & Combat_Skill_Target_Filter.CENTER_ONLY) ~= 0)
--                 or (targetCell.col == 3 and (mask & Combat_Skill_Target_Filter.BACK_ONLY)   ~= 0)
--         if not colOk then return false end
--     end

--     local ROW_BITS = Combat_Skill_Target_Filter.TOP_ROW_ONLY | Combat_Skill_Target_Filter.MIDDLE_ROW_ONLY | Combat_Skill_Target_Filter.BOTTOM_ROW_ONLY
--     if (mask & ROW_BITS) ~= 0 then
--         local rowOk = (targetCell.row == 1 and (mask & Combat_Skill_Target_Filter.TOP_ROW_ONLY)    ~= 0)
--                 or (targetCell.row == 2 and (mask & Combat_Skill_Target_Filter.MIDDLE_ROW_ONLY) ~= 0)
--                 or (targetCell.row == 3 and (mask & Combat_Skill_Target_Filter.BOTTOM_ROW_ONLY) ~= 0)
--         if not rowOk then return false end
--     end

--     local isCasterCell = isSelfSide and targetCell.row == casterCell.row and targetCell.col == casterCell.col
--     if (mask & Combat_Skill_Target_Filter.SELF_CHARACTER_ONLY) ~= 0 and not isCasterCell then return false end
--     if (mask & Combat_Skill_Target_Filter.OTHER_CHARACTER_ONLY) ~= 0 and isCasterCell then return false end

--     -- NEW: range checks were stored but never enforced.
--     -- Compared by index, so on the opponent side it's distance from the mirrored cell.
--     if self.rowRange ~= nil and math.abs(targetCell.row - casterCell.row) > self.rowRange then return false end
--     if self.colRange ~= nil and math.abs(targetCell.col - casterCell.col) > self.colRange then return false end

--     return true
-- end

-- Combat_Skill_DMG_Type = {
--     PHYSICAL = 0,
--     MAGIC = 1,
--     TRUE = 2
-- }

-- Combat_Skill_DMG = {}
-- Combat_Skill_DMG.__index = Combat_Skill_DMG

-- function Combat_Skill_DMG:new(o)
--     o = o or {}
--     setmetatable(o, self)
--     o.dmgValue = o.dmgValue or 0
--     o.dmgType = o.dmgType or Combat_Skill_DMG_Type.PHYSICAL
--     self.__index = self
--     return o
-- end

-- ---@class Combat_Skill
-- Combat_Skill = {}
-- Combat_Skill.__index = Combat_Skill

-- function Combat_Skill:new(o)
--     o = o or {}
--     setmetatable(o, self)
--     o.id = o.id or  "ID_INVALID"
--     o.name = o.name or "Skill Name"

--     o.description = o.description or "Skill Description"
--     o.costText = o.costText or "0 AP"
--     o.cost = o.cost or Combat_Skill_Cost:new()
--     o.requiredPosition = o.requiredPosition or Combat_Skill_Required_Position.ALL
--     o.targetPosition = o.targetPosition or Combat_Skill_Target_Position:new()
--     o.dmg = o.dmg or Combat_Skill_DMG:new()

--     o.isPassive = o.isPassive or false

--     self.__index = self
--     return o

-- end