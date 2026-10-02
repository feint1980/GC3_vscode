
package.path = package.path .. ";../../luaFiles/?.lua" .. ";../luaFiles/Skills/?.lua"

require "BS_Skill"

BS_Move = {}
BS_Move.__index = BS_Move
-- Without this, BS_Move.__index = BS_Move is a self-loop and never
-- reaches BS_Skill, so canAfford/pay/validate/use would be unreachable on instances.
setmetatable(BS_Move, { __index = BS_Skill })

BS_Move.SKILL_ID = "BS_Move" -- reserved id, never collides with a character's own skill ids

function BS_Move:create(character)
    local o = BS_Skill.new(self)

    o.id = BS_Move.SKILL_ID
    o.name = "Move"
    o.description = "Move to an empty slot on your side, 1 cell away (diagonals allowed)."
    o.costText = "1 AP"

    -- Must be >= 1 AP: AP carries over (gainAP), so with manual end-turn a 0-cost
    -- Move would be unlimited spam.
    o.cost = BS_SkillCost:new({ apCost = 1 })

    o.requiredPosition = BS_Required_Position.ALL

    -- own side, empty cell, Chebyshev distance 1.
    -- REQUIRE_FREE already excludes the caster's own cell, so (0,0) is never legal.
    o.targetPosition = BS_Target_Position:new(
        BS_TargetFilter.SELF_SIDE_ONLY | BS_TargetFilter.REQUIRE_FREE,
        1, 1)

    o.isPassive = false
    o.needTarget = true

    self.__index = self
    return o
end

---@diagnostic disable-next-line: duplicate-set-field
function BS_Move:validate(battleState, caster, targetCell)
    -- hook for rooted/immobile characters; delete if it never gets used
    if caster.cannotMove then return false, "CANNOT_MOVE" end
    return BS_Skill.validate(self, battleState, caster, targetCell)
end

---@diagnostic disable-next-line: duplicate-set-field
function BS_Move:execute(battleState, caster, targetCell)
    local fromCol, fromRow = caster:getPos()

    -- must update the grid AND caster.colPos/rowPos together;
    -- melee's "front-most in column" reads live positions.
    battleState:moveCharacter(caster, targetCell.row, targetCell.col)

    return {
        type          = "MOVE",
        characterID   = caster.id,
        characterSide = caster.side,
        from          = { row = fromRow, col = fromCol },
        to            = { row = targetCell.row, col = targetCell.col },
    }
end

-- One shared instance for all characters (stateless, so this is safe).
-- BS_Character:getSkill("move") should return this instead of looking in self.skills.
BS_Move.shared = BS_Move:create()

return BS_Move
