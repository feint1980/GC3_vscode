package.path = package.path .. ";../../luaFiles/?.lua" 

require "battleWrapper"
require "BS_global"
require "BS_StatScale"

--[[
================================================================================
  BS_Character.lua
  Battle Server character instance
  All derived stats calculated at call time — buffs layer on top cleanly
  Stat scaling values live in BS_StatScale.lua
================================================================================
]]--

BS_Character = {
    userID          = "",
    id              = "",
    slotIndex       = 0,
    rowPos          = 0,
    colPos          = 0,
    stats           = nil,

    -- current battle state
    cHp             = 0,        -- current hp
    cMana           = 0,        -- current mana
    cSp             = 0,        -- current sp
    cAction         = 0,        -- current AP (carries over with tax)
    cDeathdoorSurvivalRate = 1.0, -- degrades each time character survives death door

    -- buff system (to be expanded later)
    buffs           = {},
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

function BS_Character:init(userID, tId, tSlotIndex, tRowPos, tColPos)
    self.userID     = userID
    self.id         = tId
    self.slotIndex  = tSlotIndex
    self.rowPos     = tRowPos
    self.colPos     = tColPos

    print("BS_Character init: " .. userID .. " | " .. tId)

    if ClientOwnedCharacters[userID] == nil then
        print("ERROR: ClientOwnedCharacters[" .. userID .. "] is nil")
        return
    end
    if ClientOwnedCharacters[userID][tId] == nil then
        print("ERROR: ClientOwnedCharacters[" .. userID .. "][" .. tId .. "] is nil")
        return
    end

    self.stats = ClientOwnedCharacters[userID][tId]

    -- initialize current battle values from derived stats
    self.cHp    = self:getMaxHP()
    self.cMana  = self:getMaxMana()
    self.cSp    = 0
    self.cAction = self:getMaxAP()  -- start with one turn's worth of AP

    self:printStats()
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
end

--------------------------------------------------------------------------------
--  OFFENSE
--------------------------------------------------------------------------------

function BS_Character:getPhysicDmg()
    local base = self.stats.physicDmg
        + (self.stats.strength * StatScale.str_physicDmg)
    return base + self:getBuffBonus("physicDmg")
end

function BS_Character:getMagicDmg()
    local base = self.stats.magicDmg
        + (self.stats.intelligence * StatScale.int_magicDmg)
    return base + self:getBuffBonus("magicDmg")
end

function BS_Character:getPhysicalAccuracy()
    local base = self.stats.accurate
        + (self.stats.dexterity * StatScale.dex_physAcc)
    return base + self:getBuffBonus("physAcc")
end

function BS_Character:getMagicalAccuracy()
    local base = self.stats.accurate
        + (self.stats.wisdom * StatScale.wis_magAcc)
    return base + self:getBuffBonus("magAcc")
end

function BS_Character:getCritChance()
    local base = self.stats.critChance
        + (self.stats.dexterity * StatScale.dex_crit)
    return base + self:getBuffBonus("critChance")
end

--------------------------------------------------------------------------------
--  DEFENSE
--------------------------------------------------------------------------------

function BS_Character:getPhysicDef()
    local base = self.stats.physicDef
        + (self.stats.vitality  * StatScale.vit_physicDef)
        + (self.stats.strength  * StatScale.str_physicDef)
    return base + self:getBuffBonus("physicDef")
end

function BS_Character:getMagicDef()
    local base = self.stats.magicDef
        + (self.stats.wisdom        * StatScale.wis_magicDef)
        + (self.stats.intelligence  * StatScale.int_magicDef)
    return base + self:getBuffBonus("magicDef")
end

function BS_Character:getMaxHP()
    local base = self.stats.hp
        + (self.stats.vitality  * StatScale.vit_hp)
        + (self.stats.strength  * StatScale.str_hp)
    return base + self:getBuffBonus("hp")
end

function BS_Character:getEvasion()
    local base = self.stats.evadeChance
        + (self.stats.agility * StatScale.agi_evasion)
    return base + self:getBuffBonus("evasion")
end

function BS_Character:getDeathDoorSurvival()
    local base = self.stats.deathDoorSurviveChance
        + (self.stats.vitality * StatScale.vit_deathDoor)
    return (base + self:getBuffBonus("deathDoor")) * self.cDeathdoorSurvivalRate
end

--------------------------------------------------------------------------------
--  ECONOMY
--------------------------------------------------------------------------------

function BS_Character:getMaxMana()
    local base = self.stats.mana
        + (self.stats.wisdom        * StatScale.wis_mana)
        + (self.stats.intelligence  * StatScale.int_mana)
    return base + self:getBuffBonus("mana")
end

function BS_Character:getMaxSP()
    return self.stats.spCap
end

function BS_Character:getMaxAP()
    local base = StatScale.ap_base
        + (self.stats.dexterity * StatScale.dex_ap)
        + (self.stats.agility   * StatScale.agi_ap)
        + (self.stats.wisdom    * StatScale.wis_ap)
    return base + self:getBuffBonus("ap")
end

function BS_Character:getSpeed(speedRoll)
    return (self.stats.agility + speedRoll) * StatScale.agi_speed
end

--------------------------------------------------------------------------------
--  AP MANAGEMENT
--------------------------------------------------------------------------------

--- Called at the start of each turn — taxes leftover then adds new AP
function BS_Character:gainAP()
    local taxedCarry = self.cAction * StatScale.ap_carryTax
    self.cAction = math.min(taxedCarry + self:getMaxAP(), StatScale.ap_max)
end

--- Spend AP on an action — returns true if affordable, false if not
---@param cost number
---@return boolean
function BS_Character:spendAP(cost)
    if self.cAction >= cost then
        self.cAction = self.cAction - cost
        return true
    end
    return false
end

--- Check if character can afford an action without spending
---@param cost number
---@return boolean
function BS_Character:canAfford(cost)
    return self.cAction >= cost
end

--------------------------------------------------------------------------------
--  HIT RESOLUTION
--------------------------------------------------------------------------------

--- Physical hit chance against a defender
---@param defender BS_Character
---@return number clamped hit chance
function BS_Character:getPhysicalHitChance(defender)
    local chance = self:getPhysicalAccuracy() - defender:getEvasion()
    return math.max(StatScale.hit_min, math.min(StatScale.hit_max, chance))
end

--- Magical hit chance against a defender
---@param defender BS_Character
---@return number clamped hit chance
function BS_Character:getMagicalHitChance(defender)
    local chance = self:getMagicalAccuracy() - defender:getEvasion()
    return math.max(StatScale.hit_min, math.min(StatScale.hit_max, chance))
end

--- Roll hit against a defender — returns true if attack lands
---@param defender BS_Character
---@param isMagic boolean
---@return boolean
function BS_Character:rollHit(defender, isMagic)
    local chance = isMagic 
        and self:getMagicalHitChance(defender) 
        or  self:getPhysicalHitChance(defender)
    return math.random() <= chance
end

--- Roll crit — returns true if crit lands
---@return boolean
function BS_Character:rollCrit()
    return math.random() <= self:getCritChance()
end

--------------------------------------------------------------------------------
--  DEATH DOOR
--------------------------------------------------------------------------------

--- Called when character survives death door — degrades future survival chance
function BS_Character:onDeathDoorSurvived()
    self.cDeathdoorSurvivalRate = self.cDeathdoorSurvivalRate * StatScale.deathDoor_decay
end

--- Roll death door survival — returns true if character survives
---@return boolean
function BS_Character:rollDeathDoor()
    return math.random() <= self:getDeathDoorSurvival()
end

--------------------------------------------------------------------------------
--  BUFF SYSTEM (placeholder — expand later)
--------------------------------------------------------------------------------

--[[
  Buff object structure (for future reference):
  {
      id          = "buff_unique_id",   -- prevents duplicate application
      stat        = "physicDmg",        -- which stat it affects
      value       = 5.0,                -- flat bonus
      duration    = 2,                  -- turns remaining, -1 = permanent
      source      = "passive",          -- "passive", "skill", "item"
  }
]]--

--- Get total flat buff bonus for a given stat
---@param stat string
---@return number
function BS_Character:getBuffBonus(stat)
    local total = 0
    for _, buff in ipairs(self.buffs) do
        if buff.stat == stat then
            total = total + buff.value
        end
    end
    return total
end

--- Add a buff — skips if buff with same id already exists
---@param buff table
function BS_Character:addBuff(buff)
    for _, existing in ipairs(self.buffs) do
        if existing.id == buff.id then
            return  -- already applied
        end
    end
    table.insert(self.buffs, buff)
end

--- Remove a buff by id
---@param buffId string
function BS_Character:removeBuff(buffId)
    for i, buff in ipairs(self.buffs) do
        if buff.id == buffId then
            table.remove(self.buffs, i)
            return
        end
    end
end

--- Tick all buff durations — removes expired buffs. Call at end of character's turn
function BS_Character:tickBuffs()
    local i = #self.buffs
    while i > 0 do
        local buff = self.buffs[i]
        if buff.duration ~= -1 then        -- -1 = permanent
            buff.duration = buff.duration - 1
            if buff.duration <= 0 then
                table.remove(self.buffs, i)
            end
        end
        i = i - 1
    end
end

--- Clear all buffs (on battle end or specific skill)
function BS_Character:clearBuffs()
    self.buffs = {}
end
