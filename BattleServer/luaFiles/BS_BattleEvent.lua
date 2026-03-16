package.path = package.path .. ";../../luaFiles/?.lua"

require "battleWrapper"
require "BS_global"
require "BS_StatScale"
require "BS_Character"

--[[
================================================================================
BS_BattleEvent.lua
Core turn-based event pipeline

battleState is always a BattleSession instance.
All broadcasts go through battleState:broadcast() and battleState:sendToPlayer()
which use the real RakNet BM_sendWrapData under the hood.

Flow:
onRoundStart → onTurnStart → resolveAttack → applyDmg → onTurnEnd
                                                        → onRoundEnd / onBattleEnd
================================================================================
]]--

BS_BattleEvent = {}

--------------------------------------------------------------------------------
--  HELPERS
--------------------------------------------------------------------------------

local function isFormationWiped(formation)
    for _, char in ipairs(formation) do
        if char.cHp > 0 then return false end
    end
    return true
end

local function getAllAlive(battleState)
    local alive = {}
    for _, char in ipairs(battleState.p1Formation) do
        if char.cHp > 0 then table.insert(alive, char) end
    end
    for _, char in ipairs(battleState.p2Formation) do
        if char.cHp > 0 then table.insert(alive, char) end
    end
    return alive
end

--------------------------------------------------------------------------------
--  ON ROUND START
--------------------------------------------------------------------------------

function BS_BattleEvent.onRoundStart(battleState)
    battleState.currentRound = battleState.currentRound + 1
    print("[onRoundStart] Round " .. battleState.currentRound)

    -- fire onRoundStart hook on all alive characters
    for _, char in ipairs(getAllAlive(battleState)) do
        char:onRoundStart(battleState)
    end

    -- build speed entries, cache the dice roll on each character
    local entries = {}
    for _, char in ipairs(getAllAlive(battleState)) do
        local roll = math.random(1, 6)
        char.lastSpeedRoll = roll       -- cached for recalcTurnQueue mid-round
        table.insert(entries, {
            character      = char,
            effectiveSpeed = char:getSpeed(roll),
        })
    end

    -- sort descending
    table.sort(entries, function(a, b)
        return a.effectiveSpeed > b.effectiveSpeed
    end)

    -- resolve ties by reroll
    local i = 1
    while i <= #entries do
        local j = i + 1
        while j <= #entries
            and entries[j].effectiveSpeed == entries[i].effectiveSpeed do
            j = j + 1
        end
        if j - i > 1 then
            local group = {}
            for k = i, j - 1 do table.insert(group, entries[k]) end
            for k = 1, #group do group[k].tieBreak = math.random(100) end
            table.sort(group, function(a, b) return a.tieBreak > b.tieBreak end)
            for k = 1, #group do entries[i + k - 1] = group[k] end
        end
        i = j
    end

    -- build turn queue
    battleState.turnQueue = {}
    local queueInfo = {}
    for idx, entry in ipairs(entries) do
        table.insert(battleState.turnQueue, entry.character)
        table.insert(queueInfo, {
            order       = idx,
            characterId = entry.character.id,
            ownerId     = entry.character.userID,
        })
    end

    battleState:broadcast(ClientChannel.Combat, CCombatResponse.Combat_Round_Start, {
        round     = battleState.currentRound,
        turnQueue = queueInfo,
    })

    -- pop and start first turn
    local firstChar = table.remove(battleState.turnQueue, 1)
    battleState.currentChar = firstChar
    BS_BattleEvent.onTurnStart(firstChar, battleState)
end

--------------------------------------------------------------------------------
--  ON TURN START
--------------------------------------------------------------------------------

function BS_BattleEvent.onTurnStart(character, battleState)
    print("[onTurnStart] " .. character.stats.name)

    character:gainAP()
    character:tickBuffs()
    character:onTurnStart(battleState)  -- passive hook (Reimu, Meiling)

    -- notify the active player it's their turn
    battleState:sendToPlayer(character.userID,
        ClientChannel.Combat, CCombatResponse.Combat_Your_Turn, {
            characterId = character.id,
            currentAP   = character.cAction,
            currentHp   = character.cHp,
            currentMana = character.cMana,
        })

    -- notify both players whose turn it is
    battleState:broadcast(ClientChannel.Combat, CCombatResponse.Combat_Turn_Announce, {
        characterId = character.id,
        ownerId     = character.userID,
    })
end

--------------------------------------------------------------------------------
--  ON TURN END
--------------------------------------------------------------------------------

--- Returns "NEXT_TURN" | "ROUND_END" | "BATTLE_END"
function BS_BattleEvent.onTurnEnd(character, battleState)
    print("[onTurnEnd] " .. character.stats.name)

    character:onTurnEnd(battleState)  -- passive hook

    if isFormationWiped(battleState.p1Formation) then
        return BS_BattleEvent.onBattleEnd(battleState, battleState.p2Id)
    end
    if isFormationWiped(battleState.p2Formation) then
        return BS_BattleEvent.onBattleEnd(battleState, battleState.p1Id)
    end

    if #battleState.turnQueue == 0 then return "ROUND_END" end
    return "NEXT_TURN"
end

--------------------------------------------------------------------------------
--  ON ROUND END
--------------------------------------------------------------------------------

function BS_BattleEvent.onRoundEnd(battleState)
    print("[onRoundEnd] Round " .. battleState.currentRound .. " complete")
    battleState:broadcast(ClientChannel.Combat, CCombatResponse.Combat_Round_End, {
        round = battleState.currentRound,
    })
end

--------------------------------------------------------------------------------
--  ON BATTLE END
--------------------------------------------------------------------------------

function BS_BattleEvent.onBattleEnd(battleState, winnerId)
    local loserId = (winnerId == battleState.p1Id)
        and battleState.p2Id or battleState.p1Id

    print("[onBattleEnd] Winner: " .. winnerId)

    battleState:broadcast(ClientChannel.Combat, CCombatResponse.Combat_Battle_End, {
        winnerId     = winnerId,
        loserId      = loserId,
        roundsPlayed = battleState.currentRound,
    })

    return "BATTLE_END"
end

--------------------------------------------------------------------------------
--  DAMAGE PIPELINE
--------------------------------------------------------------------------------

--[[
  dmgInfo:
  {
      attacker  = BS_Character,
      defender  = BS_Character,
      rawDmg    = number,
      isMagic   = boolean,
      isAOE     = boolean,
      isCrit    = boolean,    -- filled here
      finalDmg  = number,     -- filled here
      absorbed  = number,     -- filled by Patchouli passive
      cancelled = boolean,    -- set by passive to cancel
  }
]]--

function BS_BattleEvent.applyDmg(attacker, defender, rawDmg, isMagic, isAOE, battleState)
    local dmgInfo = {
        attacker  = attacker,
        defender  = defender,
        rawDmg    = rawDmg,
        isMagic   = isMagic,
        isAOE     = isAOE,
        isCrit    = false,
        finalDmg  = 0,
        absorbed  = 0,
        cancelled = false,
    }

    -- defender's onApplyDmg hook (Patchouli manashield)
    defender:onApplyDmg(dmgInfo, battleState)

    if dmgInfo.cancelled then
        print("[applyDmg] cancelled by passive")
        return dmgInfo
    end

    -- defense reduction: dmg * (1 - def/100), max 95%
    local def       = isMagic and defender:getMagicDef() or defender:getPhysicDef()
    local reduction = math.min(def / 100, 0.95)
    local reduced   = dmgInfo.rawDmg * (1 - reduction)

    -- crit multiplies final damage (after def)
    if attacker:rollCrit() then
        dmgInfo.isCrit = true
        reduced = reduced * 1.5
    end

    dmgInfo.finalDmg = math.max(1, math.floor(reduced))
    defender.cHp     = defender.cHp - dmgInfo.finalDmg

    print(string.format("[applyDmg] %s → %s | raw:%.1f def:%.0f%% final:%d%s",
        attacker.stats.name, defender.stats.name,
        rawDmg, reduction * 100, dmgInfo.finalDmg,
        dmgInfo.isCrit and " [CRIT]" or ""))

    if defender.cHp <= 0 then
        BS_BattleEvent.onDeathDoor(defender, battleState)
    end

    return dmgInfo
end

--------------------------------------------------------------------------------
--  DEATH DOOR
--------------------------------------------------------------------------------

function BS_BattleEvent.onDeathDoor(character, battleState)
    print("[deathDoor] " .. character.stats.name)

    if character:rollDeathDoor() then
        character.cHp = 1
        character:onDeathDoorSurvived()

        print(string.format("[deathDoor] %s survived — rate now %.2f",
            character.stats.name, character.cDeathdoorSurvivalRate))

        battleState:broadcast(ClientChannel.Combat, CCombatResponse.Combat_Death_Door_Survived, {
            characterId = character.id,
            ownerId     = character.userID,
            newRate     = character.cDeathdoorSurvivalRate,
        })
    else
        character.cHp = 0
        print("[deathDoor] " .. character.stats.name .. " died")

        battleState:broadcast(ClientChannel.Combat, CCombatResponse.Combat_Character_Died, {
            characterId = character.id,
            ownerId     = character.userID,
        })
    end
end

--------------------------------------------------------------------------------
--  ON TARGETED
--------------------------------------------------------------------------------

function BS_BattleEvent.onTargeted(defender, attackInfo, battleState)
    if attackInfo.isAOE then return true, defender end

    local redirectTarget = defender:onTargeted(attackInfo, battleState)

    if redirectTarget ~= nil then
        print(string.format("[onTargeted] redirected %s → %s",
            defender.stats.name, redirectTarget.stats.name))
        return true, redirectTarget
    end

    return true, defender
end

--------------------------------------------------------------------------------
--  FULL ATTACK RESOLUTION
--------------------------------------------------------------------------------

function BS_BattleEvent.resolveAttack(attacker, intendedDefender, rawDmg, isMagic, isAOE, battleState)

    -- step 1: onTargeted — may redirect (Yukari)
    local proceed, actualDefender = BS_BattleEvent.onTargeted(intendedDefender, {
        attacker = attacker,
        rawDmg   = rawDmg,
        isMagic  = isMagic,
        isAOE    = isAOE,
    }, battleState)

    if not proceed then return nil end

    -- step 2: hit roll
    local hit = attacker:rollHit(actualDefender, isMagic)

    -- Remilia: reroll on miss (attacker side)
    if not hit then
        local rerolled = attacker:onAttackMissed(actualDefender, isMagic, battleState)
        if rerolled ~= nil then hit = rerolled end
    end

    -- Remilia: reroll on failed dodge (defender side)
    if hit then
        local dodged = actualDefender:onDodgeFailed({
            attacker = attacker,
            isMagic  = isMagic,
        }, battleState)
        if dodged then hit = false end
    end

    if not hit then
        print(string.format("[resolveAttack] %s missed %s",
            attacker.stats.name, actualDefender.stats.name))

        battleState:broadcast(ClientChannel.Combat, CCombatResponse.Combat_Attack_Missed, {
            attackerId = attacker.id,
            defenderId = actualDefender.id,
        })
        return nil
    end

    -- step 3: apply damage
    return BS_BattleEvent.applyDmg(attacker, actualDefender, rawDmg, isMagic, isAOE, battleState)
end
