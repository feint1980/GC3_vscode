package.path = package.path  .. '../Common/?.lua' .. ';./Assets/Lua/characters/Common/?.lua;'
-- gui include
require "IconGui"

-- characters include
require "Character"

Patchouli = Character:new({
    Strenth = 3,
    Vitality = 4,
    Dexterity = 8,
    Agility = 4,
    Intelligence = 22,
    Wisdom = 22,
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
    defence = 4,
    accurate = 0.85,
    evadeChance = 0.1,
    name = "Patchouli",
    lastName = "Knowledge",
    title = "Unmoving Library",
    common_actions = {},
    items = {},
    skills = {},
    currentSlot = nil
}
)



function Patchouli:loadCommon(host)
   
    self.common_actions =  Character:loadCommon(host)
    -- todo load more common of patchouli
end


-- Patchouli:new