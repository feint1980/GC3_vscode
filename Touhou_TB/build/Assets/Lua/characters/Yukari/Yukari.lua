package.path = package.path  .. '../Common/?.lua' .. ';./Assets/Lua/characters/Common/?.lua;'
-- gui include
require "IconGui"

-- characters include
require "Character"
require "kickBack"


Yukari = Character:new({
    Strenth = 12,
    Vitality = 12,
    Dexterity = 8,
    Agility = 7,
    Intelligence = 15,
    Wisdom = 17,
    dyobj = nil,
    animationPath = "./Assets/F_AObjects/yukari_tb.xml",
    portraitPath  = "./Assets/TB_GUI/faces/Yukari_face.png",
    action = 1.0,
    hp = 220,
    mana = 300,
    sp = 0,
    spCap = 100,
    physicDmg = 12,
    physicDef = 12,
    magicDmg = 12,
    magicDef = 11,
    accurate = 0.9,
    evadeChance = 0.3,
    name = "Yukari",
    lastName = "Yakumo",
    title = "Boundary Lord",
    common_actions = {},
    items = {},
    skills = {},
    currentSlot = nil
}
)

function Yukari:loadCommon(host)
   
    self.common_actions =  Character:loadCommon(host)
    -- todo load more common of yukari
end


