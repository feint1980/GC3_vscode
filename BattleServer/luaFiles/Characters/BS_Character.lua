package.path = package.path .. ";../../luaFiles/?.lua" 

require "battleWrapper"
require "BS_global"
require "BS_StatScale"

--[[
================================================================================
BS_Character.lua
Base battle character class

All event hooks are defined here as empty base functions.
Child classes (BS_Char_Reimu, BS_Char_Meiling, etc.) override only
the hooks relevant to their passive.

Inheritance pattern:
    BS_Char_Reimu = BS_Character:new()
    function BS_Char_Reimu:onTurnStart(battleState) ... end

Event hook summary:
    onRoundStart(battleState)
    onTurnStart(battleState)
    onTurnEnd(battleState)
    onTargeted(attackInfo, battleState) → returns redirectTarget or nil
    onAttackMissed(defender, isMagic, battleState) → returns bool or nil
    onDodgeFailed(attackInfo, battleState) → returns bool
    onApplyDmg(dmgInfo, battleState)
================================================================================
]]--

BS_Character = {
    userID                  = "",
    id                      = "",
    slotIndex               = 0,
    rowPos                  = 0,
    colPos                  = 0,
    stats                   = nil,
    cHp                     = 0,    -- current HP
    cMana                   = 0,    -- current Mana
    cSp                     = 0,    -- current SP
    cAction                 = 0,    -- current AP
    cDeathdoorSurvivalRate  = 1.0,  -- 1.0 * deathDoorSurviveChance
    buffs                   = {},
    currentStance           = nil,
    isAlive                 = true,
}

--------------------------------------------------------------------------------
--  LIFECYCLE
--------------------------------------------------------------------------------

function BS_Character:new(o)
    o = o or {}
    o.buffs = {}
    setmetatable(o, self)
    self.__index = self
    return o
end

---@return number col (x)
---@return number row (y)
function BS_Character:getPos()

    return self.colPos ,  self.rowPos
end

function BS_Character:init(userID, tId, tSlotIndex, tRowPos, tColPos)
    self.userID    = userID
    self.id        = tId
    self.slotIndex = tSlotIndex
    self.rowPos    = tRowPos
    self.colPos    = tColPos

    print("BS_Character init: " .. userID .. " | " .. tId)

    ClientOwnedCharacters = _G.ClientOwnedCharacters    

    if ClientOwnedCharacters[userID] == nil then
        print("ERROR: ClientOwnedCharacters[" .. userID .. "] is nil")
        return
    end
    if ClientOwnedCharacters[userID][tId] == nil then
        print("ERROR: ClientOwnedCharacters[" .. userID .. "][" .. tId .. "] is nil")
        return
    end

    print("stat init success")
    self.stats   = ClientOwnedCharacters[userID][tId]
    self.cHp     = self:getMaxHP()
    self.cMana   = self:getMaxMana()
    self.cSp     = 0
    self.cAction = self:getMaxAP()

    self:printStats()
end

function BS_Character:initStat()

    if ClientOwnedCharacters[self.userID] == nil then
        print("ERROR: ClientOwnedCharacters[" .. self.userID .. "] is nil")
        return
    end
    if ClientOwnedCharacters[self.userID][self.tId] == nil then
        print("ERROR: ClientOwnedCharacters[" .. self.userID .. "][" .. self.tId .. "] is nil")
        return
    end

    print("stat init success")
    self.stats   = ClientOwnedCharacters[self.userID][self.tId]
    self.cHp     = self:getMaxHP()
    self.cMana   = self:getMaxMana()
    self.cSp     = 0
    self.cAction = self:getMaxAP()

end

function BS_Character:printStats()
    print("---- " .. self.stats.name .. " ----")
    print("Physical dmg  " .. self:getPhysicDmg())
    print("Magic dmg     " .. self:getMagicDmg())
    print("Physical def  " .. self:getPhysicDef())
    print("Magic def     " .. self:getMagicDef())
    print("Max HP        " .. self:getMaxHP())
    print("Max Mana      " .. self:getMaxMana())
    print("Max SP        " .. self:getMaxSP())
    print("Phys Accuracy " .. self:getPhysicalAccuracy())
    print("Mag Accuracy  " .. self:getMagicalAccuracy())
    print("Evasion       " .. self:getEvasion())
    print("Crit chance   " .. self:getCritChance())
    print("Speed         " .. self:getSpeed(0))
    print("Death door    " .. self:getDeathDoorSurvival())
    print("AP/turn       " .. self:getMaxAP())
    print("Position : " .. self.colPos .. " " .. self.rowPos)
end

--------------------------------------------------------------------------------
--  OFFENSE
--------------------------------------------------------------------------------

function BS_Character:getPhysicDmg()
    return self.stats.physicDmg
        + (self.stats.strength * StatScale.str_physicDmg)
        + self:getBuffBonus("physicDmg")
end

function BS_Character:getMagicDmg()
    return self.stats.magicDmg
        + (self.stats.intelligence * StatScale.int_magicDmg)
        + self:getBuffBonus("magicDmg")
end

function BS_Character:getPhysicalAccuracy()
    return self.stats.accurate
        + (self.stats.dexterity * StatScale.dex_physAcc)
        + self:getBuffBonus("physAcc")
end

function BS_Character:getMagicalAccuracy()
    return self.stats.accurate
        + (self.stats.wisdom * StatScale.wis_magAcc)
        + self:getBuffBonus("magAcc")
end

function BS_Character:getCritChance()
    return self.stats.critChance
        + (self.stats.dexterity * StatScale.dex_crit)
        + self:getBuffBonus("critChance")
end

--------------------------------------------------------------------------------
--  DEFENSE
--------------------------------------------------------------------------------

function BS_Character:getPhysicDef()
    return self.stats.physicDef
        + (self.stats.vitality * StatScale.vit_physicDef)
        + (self.stats.strength * StatScale.str_physicDef)
        + self:getBuffBonus("physicDef")
end

function BS_Character:getMagicDef()
    return self.stats.magicDef
        + (self.stats.wisdom       * StatScale.wis_magicDef)
        + (self.stats.intelligence * StatScale.int_magicDef)
        + self:getBuffBonus("magicDef")
end

function BS_Character:getMaxHP()
    return self.stats.hp
        + (self.stats.vitality * StatScale.vit_hp)
        + (self.stats.strength * StatScale.str_hp)
        + self:getBuffBonus("hp")
end

function BS_Character:getEvasion()
    return self.stats.evadeChance
        + (self.stats.agility * StatScale.agi_evasion)
        + self:getBuffBonus("evasion")
end

function BS_Character:getDeathDoorSurvival()
    return (self.stats.deathDoorSurviveChance
        + (self.stats.vitality * StatScale.vit_deathDoor)
        + self:getBuffBonus("deathDoor"))
        * self.cDeathdoorSurvivalRate
end

--------------------------------------------------------------------------------
--  RESOURCE POINTS
--------------------------------------------------------------------------------


function BS_Character:getStrength()
    return self.stats.strength
    + self:getBuffBonus("strength")
end

function BS_Character:getVitality()
    return self.stats.vitality
    + self:getBuffBonus("vitality")
end

function BS_Character:getDexterity()
    return self.stats.dexterity
    + self:getBuffBonus("dexterity")
end

function BS_Character:getAgility()
    return self.stats.agility
    + self:getBuffBonus("agility")
end

function BS_Character:getIntelligence()
    return self.stats.intelligence
    + self:getBuffBonus("intelligence")
end

function BS_Character:getWisdom()
    return self.stats.wisdom
    + self:getBuffBonus("wisdom")
end


function BS_Character:getMaxMana()
    return self.stats.mana
        + (self.stats.wisdom       * StatScale.wis_mana)
        + (self.stats.intelligence * StatScale.int_mana)
        + self:getBuffBonus("maxMana")
end

function BS_Character:getMaxSP()
    return self.stats.spCap
end

function BS_Character:getMaxAP()
    return StatScale.ap_base
        + (self.stats.dexterity * StatScale.dex_ap)
        + (self.stats.agility   * StatScale.agi_ap)
        + (self.stats.wisdom    * StatScale.wis_ap)
        + self:getBuffBonus("ap")
end

function BS_Character:getSpeed(speedRoll)
    return (self.stats.agility + (speedRoll or 0)) * StatScale.agi_speed
end

--------------------------------------------------------------------------------
--  current stats
--------------------------------------------------------------------------------

function BS_Character:getCurrentHP()

    if self.cHp <= 0 then
        return 0
    end
    if self.cHp > self:getMaxHP() then
        self.cHp = self:getMaxHP()
    end

    return self.cHp
end

function BS_Character:getCurrentMana()

    if self.cMana <= 0 then
        return 0
    end
    if self.cMana > self:getMaxMana() then
        self.cMana = self:getMaxMana()
    end

    return self.cMana
end

function BS_Character:getCurrentSP()

    if self.cSp <= 0 then
        return 0
    end
    if self.cSp > self:getMaxSP() then
        self.cSp = self:getMaxSP()
    end

    return self.cSp
end

function BS_Character:getCurrentAP()
    return self.cAction
end




--------------------------------------------------------------------------------
--  AP MANAGEMENT
--------------------------------------------------------------------------------

function BS_Character:gainAP()
    local taxedCarry = self.cAction * StatScale.ap_carryTax
    self.cAction = math.min(taxedCarry + self:getMaxAP(), StatScale.ap_max)
end

function BS_Character:spendAP(cost)
    if self.cAction >= cost then
        self.cAction = self.cAction - cost
        return true
    end
    return false
end

function BS_Character:canAfford(cost)
    return self.cAction >= cost
end

--------------------------------------------------------------------------------
--  HIT RESOLUTION
--------------------------------------------------------------------------------

function BS_Character:getPhysicalHitChance(defender)
    local chance = self:getPhysicalAccuracy() - defender:getEvasion()
    return math.max(StatScale.hit_min, math.min(StatScale.hit_max, chance))
end

function BS_Character:getMagicalHitChance(defender)
    local chance = self:getMagicalAccuracy() - defender:getEvasion()
    return math.max(StatScale.hit_min, math.min(StatScale.hit_max, chance))
end

function BS_Character:rollHit(defender, isMagic)
    local chance = isMagic
        and self:getMagicalHitChance(defender)
        or  self:getPhysicalHitChance(defender)
    return math.random() <= chance
end

function BS_Character:rollCrit()
    return math.random() <= self:getCritChance()
end

--------------------------------------------------------------------------------
--  DEATH DOOR
--------------------------------------------------------------------------------

function BS_Character:onDeathDoorSurvived()
    self.cDeathdoorSurvivalRate = self.cDeathdoorSurvivalRate * StatScale.deathDoor_decay
end

function BS_Character:rollDeathDoor()
    return math.random() <= self:getDeathDoorSurvival()
end

--------------------------------------------------------------------------------
--  BUFF SYSTEM
--------------------------------------------------------------------------------

function BS_Character:getBuffBonus(stat)
    local total = 0
    for _, buff in ipairs(self.buffs) do
        if buff.stat == stat then
            total = total + buff.value
        end
    end
    return total
end

function BS_Character:addBuff(buff)
    for _, existing in ipairs(self.buffs) do
        if existing.id == buff.id then return end
    end
    table.insert(self.buffs, buff)
end

function BS_Character:removeBuff(buffId)
    for i, buff in ipairs(self.buffs) do
        if buff.id == buffId then
            table.remove(self.buffs, i)
            return
        end
    end
end

function BS_Character:tickBuffs()
    local i = #self.buffs
    while i > 0 do
        local buff = self.buffs[i]
        if buff.duration ~= -1 then
            buff.duration = buff.duration - 1
            if buff.duration <= 0 then
                table.remove(self.buffs, i)
            end
        end
        i = i - 1
    end
end

function BS_Character:clearBuffs()
    self.buffs = {}
end

--------------------------------------------------------------------------------
--  BASE EVENT HOOKS — empty by default, child classes override as needed
--------------------------------------------------------------------------------

--- Called at the start of each round before turn queue is built
---@param battleState table
function BS_Character:onRoundStart(battleState)
    
    print(self.id .. " onRoundStart (BS_Character)")

end

--- Called at the start of this character's turn
--- gainAP and tickBuffs are called by BS_BattleEvent BEFORE this hook
---@param battleState table
function BS_Character:onTurnStart(battleState) end

--- Called at the end of this character's turn
---@param battleState table
function BS_Character:onTurnEnd(battleState) end

--- Called when this character is targeted by a NON-AOE attack
--- Return a BS_Character to redirect, nil to proceed normally
---@param attackInfo table { attacker, rawDmg, isMagic, isAOE }
---@param battleState table
---@return BS_Character|nil
function BS_Character:onTargeted(attackInfo, battleState)
    return nil
end

--- Called when this character's attack misses
--- Return true if reroll hits, false if misses, nil if passive did not fire
---@param defender BS_Character
---@param isMagic boolean
---@param battleState table
---@return boolean|nil
function BS_Character:onAttackMissed(defender, isMagic, battleState)
    return nil
end

--- Called when this character fails to dodge
--- Return true if reroll dodges, false otherwise
---@param attackInfo table
---@param battleState table
---@return boolean
function BS_Character:onDodgeFailed(attackInfo, battleState)
    return false
end

--- Called just before damage is applied to this character
--- Modify dmgInfo.rawDmg to reduce incoming damage
--- Set dmgInfo.cancelled = true to fully cancel
---@param dmgInfo table
---@param battleState table
function BS_Character:onApplyDmg(dmgInfo, battleState) end

---- 