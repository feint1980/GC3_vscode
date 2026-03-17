package.path = package.path .. ";../../luaFiles/?.lua"

require "BS_Character"

--[[
================================================================================
  BS_Char_Yukari.lua
  Yakumo Yukari — Fate Reflection

  Override: onTargeted
  When targeted by a NON-AOE attack, 17% chance to reflect the attack
  to a random alive character on the OPPONENT's field.
================================================================================
]]--

-- BS_Char_Yukari = BS_Character:new()
BS_Char_Yukari = setmetatable({}, {__index = BS_Character})
BS_Char_Yukari.__index = BS_Char_Yukari

local REFLECT_CHANCE = 0.17

function BS_Char_Yukari:onTargeted(attackInfo, battleState)
    print(string.format("[Yukari:Fate Reflection] roll %.0f%% chance", REFLECT_CHANCE * 100))

    if math.random() > REFLECT_CHANCE then
        print("[Yukari:Fate Reflection] did not trigger")
        return nil
    end

    -- find a random alive character on the opponent's field
    local opponentFormation = (self.userID == battleState.p1Id)
        and battleState.p2Formation
        or  battleState.p1Formation

    local alive = {}
    for _, char in ipairs(opponentFormation) do
        if char.cHp > 0 then table.insert(alive, char) end
    end

    if #alive == 0 then return nil end

    local redirectTarget = alive[math.random(#alive)]

    print(string.format("[Yukari:Fate Reflection] triggered → redirecting to %s",
        redirectTarget.stats.name))

    battleState.broadcast("YUKARI_REFLECT", {
        characterId      = self.id,
        originalAttacker = attackInfo.attacker and attackInfo.attacker.id or "unknown",
        redirectTo       = redirectTarget.id,
        redirectOwner    = redirectTarget.userID,
    })

    return redirectTarget
end
