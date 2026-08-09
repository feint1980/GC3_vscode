package.path = package.path .. ";../../luaFiles/?.lua"

require "BS_Character"

--[[
================================================================================
  BS_Char_Remilia.lua
  Remilia Scarlet — Fate Manipulation

  Override: onAttackMissed, onDodgeFailed
  On a missed attack OR failed dodge, gets a second roll at 50% reduced chance.
  Abuses the RNG layers of the game more than any other character.
================================================================================
]]--

BS_Char_Remilia = BS_Character:new()

-- local REROLL_CHANCE = 0.50

-- function BS_Char_Remilia:onAttackMissed(defender, isMagic, battleState)
--     print(string.format("[Remilia:Fate Manipulation] attack reroll %.0f%% chance",
--         REROLL_CHANCE * 100))

--     if math.random() > REROLL_CHANCE then
--         print("[Remilia:Fate Manipulation] reroll did not activate")
--         return nil
--     end

--     local hit = self:rollHit(defender, isMagic)

--     print(string.format("[Remilia:Fate Manipulation] attack reroll → %s", hit and "HIT" or "MISS"))

--     battleState.broadcast("REMILIA_FATE_REROLL", {
--         characterId = self.id,
--         type        = "attack",
--         result      = hit and "hit" or "miss",
--     })

--     return hit
-- end

-- function BS_Char_Remilia:onDodgeFailed(attackInfo, battleState)
--     print(string.format("[Remilia:Fate Manipulation] dodge reroll %.0f%% chance",
--         REROLL_CHANCE * 100))

--     if math.random() > REROLL_CHANCE then
--         print("[Remilia:Fate Manipulation] reroll did not activate")
--         return false
--     end

--     local attacker  = attackInfo.attacker
--     local hitChance = attackInfo.isMagic
--         and attacker:getMagicalHitChance(self)
--         or  attacker:getPhysicalHitChance(self)

--     -- dodge succeeds if new roll beats the attacker's hit chance
--     local dodged = math.random() > hitChance

--     print(string.format("[Remilia:Fate Manipulation] dodge reroll → %s",
--         dodged and "DODGED" or "HIT"))

--     battleState.broadcast("REMILIA_FATE_REROLL", {
--         characterId = self.id,
--         type        = "dodge",
--         result      = dodged and "dodged" or "hit",
--     })

--     return dodged
-- end
