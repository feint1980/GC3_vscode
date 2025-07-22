
---@table BuffType
BuffType = {
    buff = 1,
    debuff = 2
}

---@table BuffBit
BuffBit = {

    strChange            = 1 << 0,
    vitChange            = 1 << 1,
    dexChange            = 1 << 2,
    agiChange            = 1 << 3,
    intChange            = 1 << 4,
    hpChange             = 1 << 5, -- heal, dot 
    mpChange             = 1 << 6, -- mana gain/burn
    maxHpChange          = 1 << 7,
    maxMpChange          = 1 << 8,

    physicDmgChange      = 1 << 9,
    magicDmgChange       = 1 << 10,
    physicDefChange      = 1 << 11,
    magicDefChange       = 1 << 12,
    accurateChange       = 1 << 13,
    evadeChanceChange    = 1 << 14,
    hitChanceChange      = 1 << 15,
    critChanceChange     = 1 << 16,
    hpScaleChange        = 1 << 17,
    mpScaleChange        = 1 << 18,
    physicDmgScaleChange = 1 << 19,
    magicDmgScaleChange  = 1 << 20,
    physicDefScaleChange = 1 << 21,
    magicDefScaleChange  = 1 << 22,
    accurateScaleChange  = 1 << 23,
    hitChanceScaleChange = 1 << 24,
    evadeChanceScaleChange = 1 << 25,
    deathDoorChanceChange = 1 << 26,
    -- You can go all the way up to:
    -- maxBit = 1 << 62
}


---@class S_Buff
S_Buff = {
    name = "None",
    description = "None",
    buffBit = 0,
    buffType = BuffType.buff,
    duration = 0,
    buffID = 0,
    ---@type table
    properties = {} --- use buffBit to store value for each property 
}