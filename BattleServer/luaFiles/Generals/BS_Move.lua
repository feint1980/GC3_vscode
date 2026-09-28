-- BS_Move.lua
-- General Move skill, shared by every character (BS_Character:getSkill returns BS_Move.shared).
-- Must NOT require BS_Character / BS_BattleSession at file top (circular require:
-- BS_Character requires this file).
local BS_Skill = require("BS_Skill") -- also defines the BS_* globals

-- child class: metatable inheritance, NOT BS_Skill:new()
BS_Move = setmetatable({}, { __index = BS_Skill })
BS_Move.__index = BS_Move

BS_Move.SKILL_ID = "move" -- reserved id, never collides with character skill ids

function BS_Move:new(o)
    o = o or {}
    o.id = BS_Move.SKILL_ID
    o.name = o.name or "Move"
    o.description = o.description or "Move to an empty slot on your side, 1 cell away (diagonals allowed)."

    -- Must be >= 1 AP: AP carries over (gainAP), so a 0-cost Move with manual
    -- end-turn would be unlimited spam.
    o.cost = o.cost or BS_SkillCost:new({ apCost = 1 })
    o.costText = o.costText or "1 AP"

    -- own side, empty cell, Chebyshev distance 1.
    -- REQUIRE_FREE already excludes the caster's own cell, so (0,0) is never legal.
    o.targetPosition = BS_Target_Position:new(
        BS_TargetFilter.SELF_SIDE_ONLY | BS_TargetFilter.REQUIRE_FREE,
        1, 1)

    -- requiredPosition stays ALL (default): any cell can move
    return BS_Skill.new(self, o)
end

---@diagnostic disable-next-line: duplicate-set-field
function BS_Move:validate(battleState, caster, targetCell)
    -- "all characters that can move": runtime flag on the character (NOT on caster.stats,
    -- which is the shared persisted table). Delete if it never gets used.
    if caster.cannotMove then return false, "CANNOT_MOVE" end
    return BS_Skill.validate(self, battleState, caster, targetCell)
end

---@diagnostic disable-next-line: duplicate-set-field
function BS_Move:execute(battleState, caster, targetCell)
    local fromCol, fromRow = caster:getPos()

    -- must update the grid AND caster.colPos/rowPos together;
    -- melee's "front-most in column" reads live positions.
    battleState:moveCharacter(caster, targetCell.row, targetCell.col)

    -- key names match the OnCharacterTurnStart payload (characterID / characterSide)
    return {
        type          = "MOVE",
        characterID   = caster.id,
        characterSide = caster.side,
        from          = { row = fromRow, col = fromCol },
        to            = { row = targetCell.row, col = targetCell.col },
    }
end

-- One shared instance for all characters. Safe: the skill holds no per-caster state.
BS_Move.shared = BS_Move:new()

return BS_Move

--[[
Client action menu: prepend BS_Move.shared to the list built from character:getSkills(),
since Move is intentionally not in that table.

Battle session, per action packet:
    local skill = caster:getSkill(packet.skillId)
    if not skill then reject("UNKNOWN_SKILL") end
    local ok, result = skill:use(battleState, caster, targetCellBuiltByServer)
    -- ok: broadcast result to both players, stay in this character's ACTION_PHASE
    -- END_TURN action (or timer expiry) is what advances the turnQueue
]]
