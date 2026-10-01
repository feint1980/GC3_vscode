
require "BS_Skill"

BS_EndTurn = {}
BS_EndTurn.__index = BS_EndTurn

setmetatable(BS_EndTurn, { __index = BS_Skill })

BS_EndTurn.SKILL_ID = "BS_EndTurn" -- reserved id, never collides with a character's own skill ids

function BS_EndTurn:create(character)
    local o = BS_Skill.new(self)

    o.id = BS_EndTurn.SKILL_ID
    o.name = "End Turn"
    o.description = "End your turn."
    o.costText = " "
    o.cost = BS_SkillCost:new({})
    o.requiredPosition = BS_Required_Position.ALL
    o.targetPosition = BS_Target_Position:new()

    self.__index = self
    return o
end

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
