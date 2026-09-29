-- BS_EndTurn.lua
-- Not a BS_Skill: no target cell, no resource cost. Forcing it through
-- BS_Skill:use() would mean faking a targetCell just to pass validate()'s
-- bounds check, so this stays a separate, minimal module.
--
-- ASSUMPTIONS (rename to match your real BS_BattleSession):
--   battleState:getActiveCharacter() -> the character whose turn it currently is
--   battleState:advanceTurn()        -> pops turnQueue, moves to next turn/round
BS_EndTurn = {}

function BS_EndTurn:validate(battleState, caster, senderUserID)
    if not caster.isAlive then return false, "CASTER_DEAD" end
    if caster.userID ~= senderUserID then return false, "NOT_YOUR_CHARACTER" end

    local active = battleState:getActiveCharacter()
    if active ~= caster then return false, "NOT_YOUR_TURN" end

    return true
end

-- Single entry point, same shape as BS_Skill:use() (ok, result) so the packet
-- handler can treat END_TURN the same way it treats a skill action.
function BS_EndTurn:use(battleState, caster, senderUserID)
    local ok, err = self:validate(battleState, caster, senderUserID)
    if not ok then return false, err end

    battleState:advanceTurn()

    return true, {
        type          = "END_TURN",
        characterID   = caster.id,
        characterSide = caster.side,
    }
end

return BS_EndTurn
