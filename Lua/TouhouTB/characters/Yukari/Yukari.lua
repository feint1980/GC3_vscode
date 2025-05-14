package.path = package.path  .. '../Common/?.lua' .. ';./Assets/Lua/characters/Common/?.lua;'
-- gui include
require "IconGui"

-- characters include
require "Character"
require "kickBack"


Yukari = Character:new({
    Strenth = 6,
    Vitality = 7,
    Dexterity = 4,
    Agility = 6,
    Intelligence = 15,
    Wisdom = 16,
    dyobj = nil,
    animationPath = "./Assets/F_AObjects/yukari_tb.xml",
    portraitPath  = "./Assets/TB_GUI/faces/Yukari_face.png",
    panelPath = "./Assets/TB_GUI/panels/yukari_panel.png",
    action = 0,
    hp = 220,
    mana = 250,
    sp = 0,
    spCap = 100,
    physicDmg = 7,
    physicDef = 6,
    magicDmg = 13,
    magicDef = 10,
    accurate = 0.8,
    evadeChance = 0.33,
    critChance = 0.13,
    hpScale = 8,
    manaScale = 9,
    physicDmgScale = 2,
    magicDmgScale = 5,
    physicDefScale = 2,
    magicDefScale = 3,
    accurateScale = 0.03,
    evadeChanceScale = 0.02,
    deathDoorSurviveChance = 0.32,
    name = "Yukari",
    lastName = "Yakumo",
    title = "Boundary Lord",
    common_actions = {},
    items = {},
    skills = {},
    currentSlot = nil
}
)

---@Description Yukari inherits from Character
---@function Yukari:loadCommon
---@param host pointer instance of BattleScene
---@return table
---@override
function Yukari:loadCommon(host)

    self.common_actions =  Character:loadCommon(host)
    -- todo load more common of yukari
end


