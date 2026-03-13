--[[
================================================================================
  BS_StatScale.lua
  Universal stat scaling table for Battle Server
  All derived stat formulas reference this file — change here, affects everywhere
  
  Formula pattern:
    derived = base + (stat * scale)
  
  Mixed stat design:
    Every stat has 1 primary + 1~2 secondaries
    No stat is completely dead for any character
================================================================================
]]--

StatScale = {

    ----------------------------------------------------------------------------
    -- STRENGTH (STR)
    -- Primary   : Physical Damage
    -- Secondary : HP (muscle mass)
    -- Tertiary  : Physical Defense (toughness)
    ----------------------------------------------------------------------------
    str_physicDmg   = 1.5,
    str_hp          = 2.0,
    str_physicDef   = 0.2,

    ----------------------------------------------------------------------------
    -- VITALITY (VIT)
    -- Primary   : HP
    -- Secondary : Physical Defense
    -- Tertiary  : Death Door Survival chance
    ----------------------------------------------------------------------------
    vit_hp          = 8.0,
    vit_physicDef   = 0.5,
    vit_deathDoor   = 0.025,

    ----------------------------------------------------------------------------
    -- DEXTERITY (DEX)
    -- Primary   : Physical Accuracy
    -- Secondary : Critical Hit Chance
    -- Tertiary  : AP gain
    ----------------------------------------------------------------------------
    dex_physAcc     = 0.031,
    dex_crit        = 0.005,
    dex_ap          = 0.02,

    ----------------------------------------------------------------------------
    -- AGILITY (AGI)
    -- Primary   : Speed / Turn Order
    -- Secondary : Evasion
    -- Tertiary  : AP gain
    ----------------------------------------------------------------------------
    agi_speed       = 0.9,
    agi_evasion     = 0.025,
    agi_ap          = 0.02,

    ----------------------------------------------------------------------------
    -- INTELLIGENCE (INT)
    -- Primary   : Magic Damage
    -- Secondary : Mana (more power needs more fuel)
    -- Tertiary  : Magic Defense (understanding magic = resisting it)
    ----------------------------------------------------------------------------
    int_magicDmg    = 1.7,
    int_mana        = 3.0,
    int_magicDef    = 0.15,

    ----------------------------------------------------------------------------
    -- WISDOM (WIS)
    -- Primary   : Magic Defense
    -- Secondary : Mana
    -- Tertiary  : Magical Accuracy + AP gain
    ----------------------------------------------------------------------------
    wis_magicDef    = 0.6,
    wis_mana        = 6.0,
    wis_magAcc      = 0.031,
    wis_ap          = 0.01,

    ----------------------------------------------------------------------------
    -- AP SYSTEM
    -- AP = ap_base + (DEX * dex_ap) + (AGI * agi_ap) + (WIS * wis_ap)
    -- Carry over with 20% tax on leftover
    -- Hard cap at ap_max
    ----------------------------------------------------------------------------
    ap_base         = 1.0,
    ap_carryTax     = 0.8,   -- multiply leftover by this (0.8 = 20% tax)
    ap_max          = 3.0,   -- hard hoard cap

    ----------------------------------------------------------------------------
    -- HIT RESOLUTION
    -- hitChance = clamp(attackerAccuracy - defenderEvasion, hit_min, hit_max)
    ----------------------------------------------------------------------------
    hit_min         = 0.05,  -- always at least 5% hit chance
    hit_max         = 0.95,  -- always at least 5% miss chance

    ----------------------------------------------------------------------------
    -- DEATH DOOR
    -- survivalChance degrades each time character survives death door
    -- multiply cDeathdoorSurvivalRate by deathDoor_decay on each survival
    ----------------------------------------------------------------------------
    deathDoor_decay = 0.67,  -- ~33% reduction per survival (0.5 = 50%)
}
