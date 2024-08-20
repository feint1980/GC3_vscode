package.path = package.path  .. '../Common/?.lua' .. ';./Assets/Lua/characters/Common/?.lua;'
-- gui include
require "IconGui"

-- characters include
require "Character"

Reimu = Character:new({
    Strenth = 9,
    Vitality = 9,
    Dexterity = 14,
    Agility = 12,
    Intelligence = 10,
    Wisdom = 11,
    dyobj = nil,
    animationPath = "./Assets/F_AObjects/reimu_tb.xml",
    action = 1.0,
    hp = 170,
    mana = 220,
    sp = 0,
    spCap = 100,
    physicDmg = 12,
    physicDef = 12,
    magicDmg = 12,
    magicDef = 11,
    accurate = 0.9,
    evadeChance = 0.3,
    name = "Reimu",
    lastName = "Hakurei",
    title = "Hakurei Shrine Maiden",
    common_actions = {},
    items = {},
    skills = {},
    currentSlot = nil
}
)

-- Patchouli:new