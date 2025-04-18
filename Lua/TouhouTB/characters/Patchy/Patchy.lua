package.path = package.path  .. '../Common/?.lua' .. ';./Assets/Lua/characters/Common/?.lua;'
-- gui include
require "IconGui"

-- characters include
require "Character"

---@class Patchy: Character
---@return Patchy
Patchy = Character:new({
    Strenth = 3,
    Vitality = 3,
    Dexterity = 3,
    Agility = 3,
    Intelligence = 18,
    Wisdom = 18,

    dyobj = nil,
    animationPath = "./Assets/F_AObjects/patchouli_tb.xml",
    action = 1.0,
    hp = 30,
    mana = 370,
    sp = 0,
    spCap = 100,
    physicDmg = 4,
    physicDef = 6,
    magicDmg = 25,
    magicDef = 13,
    accurate = 0.85,
    evadeChance = 0.1,
    name = "Patchy",
    lastName = "Knowledge",
    title = "Unmoving Library",
    common_actions = {},
    items = {},
    skills = {},
    currentSlot = nil
}
)

-- Patchouli:new