package.path = package.path .. ";../../luaFiles/?.lua" .. ";../luaFiles/Skills/BS_Meiling/?.lua"

require "BS_Character"
require "BS_Skill_MeilingStances"
require "BS_Skill_LiangYiZhuang"
require "BS_Skill_PuBu"
require "BS_Skill_DuLiBu"


--[[
================================================================================
  BS_Char_Meiling.lua
  Hong Meiling — Liang Yi Zhuang Stance System

  Override: onTurnStart
  Meiling starts in ATTACK stance if no stance is set yet.
  Stance switch is a FREE ACTION — handled by the battle system calling
  BS_Char_Meiling.switchStance(battleState) directly, no AP cost.

  ATTACK  stance: +physicDmg, -physicDef
  DEFENSE stance: +physicDef, -physicDmg
================================================================================
]]--

-- BS_Char_Meiling = BS_Character:new()
BS_Char_Meiling = setmetatable({}, {__index = BS_Character})
BS_Char_Meiling.__index = BS_Char_Meiling

local STANCE_ATTACK  = "attack"
local STANCE_DEFENSE = "defense"

local STANCE_BUFFS = {
    [STANCE_ATTACK] = {
        bonus   = { id = "meiling_atk_dmg", stat = "physicDmg", value =  8.0, duration = -1, source = "passive" },
        penalty = { id = "meiling_atk_def", stat = "physicDef", value = -5.0, duration = -1, source = "passive" },
    },
    [STANCE_DEFENSE] = {
        bonus   = { id = "meiling_def_def", stat = "physicDef", value =  8.0, duration = -1, source = "passive" },
        penalty = { id = "meiling_def_dmg", stat = "physicDmg", value = -5.0, duration = -1, source = "passive" },
    },
}

--- Internal — clears all stance buffs then applies the new stance
---@param stance string
---@param battleState table
function BS_Char_Meiling:applyStance(stance, battleState)
    for _, buffs in pairs(STANCE_BUFFS) do
        self:removeBuff(buffs.bonus.id)
        self:removeBuff(buffs.penalty.id)
    end

    local buffs = STANCE_BUFFS[stance]
    self:addBuff(buffs.bonus)
    self:addBuff(buffs.penalty)
    self.currentStance = stance

    print(string.format("[Meiling:Liang Yi Zhuang] stance → %s", stance))

    battleState.broadcast("MEILING_STANCE_CHANGE", {
        characterId  = self.id,
        ownerId      = self.userID,
        stance       = stance,
        bonusStat    = buffs.bonus.stat,
        bonusValue   = buffs.bonus.value,
        penaltyStat  = buffs.penalty.stat,
        penaltyValue = buffs.penalty.value,
    })
end

--- Free action — called by battle system on STANCE action, no AP cost
---@param battleState table
function BS_Char_Meiling:switchStance(battleState)
    local newStance = (self.currentStance == STANCE_ATTACK)
        and STANCE_DEFENSE
        or  STANCE_ATTACK
    self:applyStance(newStance, battleState)
end

---@diagnostic disable-next-line: duplicate-set-field
function BS_Char_Meiling:onTurnStart(battleState)
    -- initialize stance on first turn
    -- if self.currentStance == nil then
    --     self:applyStance(STANCE_ATTACK, battleState)
    -- end

    battleState:broadcast(ClientChannel.Combat, CCombatResponse.Combat_IngameData,CombatIngameData.OnCharacterTurnStart,
    {
        characterID = self.id,
        characterSide = self.side,
        currentAp   = self.cAction,
        currentHp   = self.cHp,
        currentMana = self.cMana
    }
    )
end


function BS_Char_Meiling:loadSkills()

    print("BS_Char_Meiling loadSkills called |||||||||||||||||||||||||||||||||||||||||||")
    self.skills = {}

    self.skills["F"] = BS_Skill_MeilingStances:create(self)
    self.skills["A"] = BS_Skill_LiangYiZhuang:create(self)
    self.skills["S"] = BS_Skill_Pubu:create(self)
    self.skills["D"] = BS_Skill_DuLiBu:create(self)

    print(self.skills["F"].name)
    print(self.skills["F"].description)

    print(self.skills["A"].name)
    print(self.skills["A"].description)

    print(self.skills["S"].name)
    print(self.skills["S"].description)

    print(self.skills["D"].name)
    print(self.skills["D"].description)


end

-- ---@diagnostic disable-next-line: duplicate-set-field
-- function BS_Char_Meiling:getMaxHP()

--     return 5000
-- end