package.path = package.path .. ";../../luaFiles/?.lua" .. ";../luaFiles/Characters/?.lua"


-- print("package path " .. package.path)

require "BS_Character"

--[[
================================================================================
  BS_Char_Reimu.lua
  Reimu Hakurei — Fate's Favor

  Override: onTurnStart
  At the start of her turn, has a (15% + missingHP%) chance to receive
  a random buff. Gets more dangerous as HP drops.
================================================================================
]]--

-- BS_Char_Reimu = BS_Character:new()
BS_Char_Reimu = setmetatable({}, {__index = BS_Character})
BS_Char_Reimu.__index = BS_Char_Reimu

local PASSIVE_BASE_CHANCE = 0.15

local BUFF_POOL = {
    { id = "reimu_fate_physicDmg", stat = "physicDmg", value = 5.0,  duration = 2, source = "passive" },
    { id = "reimu_fate_magicDmg",  stat = "magicDmg",  value = 5.0,  duration = 2, source = "passive" },
    { id = "reimu_fate_evasion",   stat = "evasion",   value = 0.10, duration = 2, source = "passive" },
    { id = "reimu_fate_physicDef", stat = "physicDef", value = 4.0,  duration = 2, source = "passive" },
    { id = "reimu_fate_magicDef",  stat = "magicDef",  value = 4.0,  duration = 2, source = "passive" },
    { id = "reimu_fate_ap",        stat = "ap",        value = 0.3,  duration = 1, source = "passive" },
}

---@diagnostic disable-next-line: duplicate-set-field
function BS_Char_Reimu:onTurnStart(battleState)
    local maxHp      = self:getMaxHP()
    local missingPct = math.max(0, maxHp - self.cHp) / maxHp
    local chance     = PASSIVE_BASE_CHANCE + missingPct

    print(string.format("[Reimu:Fate's Favor] roll %.0f%% (base 15%% + %.0f%% missing HP)",
        chance * 100, missingPct * 100))

    if math.random() <= chance then
        local buff = BUFF_POOL[math.random(#BUFF_POOL)]
        self:removeBuff(buff.id)  -- reset duration if already active
        self:addBuff(buff)

        print(string.format("[Reimu:Fate's Favor] triggered → %s +%.2f for %d turns",
            buff.stat, buff.value, buff.duration))

        -- battleState.broadcast("BUFF_GAINED", {
        --     characterId = self.id,
        --     ownerId     = self.userID,
        --     buffId      = buff.id,
        --     stat        = buff.stat,
        --     value       = buff.value,
        --     duration    = buff.duration,
        -- })
    else
        print("[Reimu:Fate's Favor] did not trigger")
    end

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
