package.path = package.path .. ";../../luaFiles/?.lua"

require "BS_Character"

--[[
================================================================================
  BS_Char_Patchouli.lua
  Patchouli Knowledge — Manashield

  Override: onApplyDmg
  Absorbs 80% of incoming damage as mana loss instead of HP loss.
  If mana runs out, excess overflows to HP as normal.
  Counter: mana drain skills.
================================================================================
]]--

-- BS_Char_Patchouli = BS_Character:new()
BS_Char_Patchouli = setmetatable({}, {__index = BS_Character})
BS_Char_Patchouli.__index = BS_Char_Patchouli

local ABSORB_RATE = 0.80

---@diagnostic disable-next-line: duplicate-set-field
function BS_Char_Patchouli:onApplyDmg(dmgInfo, battleState)
    if self.cMana <= 0 then
        print("[Patchouli:Manashield] depleted — taking full damage")
        return
    end

    local toAbsorb = dmgInfo.rawDmg * ABSORB_RATE
    local toHp     = dmgInfo.rawDmg * (1 - ABSORB_RATE)

    if self.cMana >= toAbsorb then
        -- full absorption
        self.cMana       = self.cMana - toAbsorb
        dmgInfo.absorbed = toAbsorb
        dmgInfo.rawDmg   = toHp

        print(string.format("[Patchouli:Manashield] absorbed %.1f → mana now %.1f",
            toAbsorb, self.cMana))
    else
        -- partial — mana covers what it can, rest overflows to HP
        local actualAbsorbed = self.cMana
        local overflow       = toAbsorb - actualAbsorbed

        self.cMana       = 0
        dmgInfo.absorbed = actualAbsorbed
        dmgInfo.rawDmg   = toHp + overflow

        print(string.format("[Patchouli:Manashield] partial — absorbed %.1f, overflow %.1f, mana depleted",
            actualAbsorbed, overflow))
    end

    battleState.broadcast("MANASHIELD_ABSORBED", {
        characterId = self.id,
        absorbed    = dmgInfo.absorbed,
        manaLeft    = self.cMana,
    })
end
