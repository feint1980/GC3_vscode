package.path = package.path .. ';../../Lua/TouhouTB/characters/Common/?.lua;'

-- gui include
require "IconGui"

-- characters include
require "Character"

Meiling = Character:new({
     Strength = 17,
    Vitality = 18,
    Dexterity = 15,
    Agility = 15,
    Intelligence = 6,
    Wisdom = 6,
    animationPath = "./Assets/F_AObjects/meiling_tb.xml",
    portraitPath  = "./Assets/TB_GUI/faces/Meiling_face.png",
    panelPath = "./Assets/TB_GUI/panels/meiling_panel.png",
    action = 0,
    hp = 140,
    mana = 70,
    sp = 0,
    spCap = 100,
    physicDmg = 16,
    physicDef = 11.5,
    magicDmg = 8.7,
    magicDef = 3.3,
    accurate = 0.9,
    evadeChance = 0.25,
    critChance = 0.125,
    hpScale = 9,
    manaScale = 7,
    physicDmgScale = 3.2,
    magicDmgScale = 0.8,
    physicDefScale = 1.2,
    magicDefScale = 0.7,
    accurateScale = 0.039,
    evadeChanceScale = 0.029,
    deathDoorSurviveChance = 0.3,
    name = "Meiling",
    lastName = "Hong",
    title = "Gatekeeper of Scarlet Devil Mansion",
    side = 1,
    level = 1,
    xp = 0,
    price = 35,
    ID = "T_MEILING"
}
)

---@Description Yukari inherits from Character
---@function Yukari:loadCommon
---@param host pointer instance of BattleScene
---@return table
---@override
function Meiling:loadCommon(host)

    self.common_actions =  Character:loadCommon(host)
    -- todo load more common of Meiling
end


