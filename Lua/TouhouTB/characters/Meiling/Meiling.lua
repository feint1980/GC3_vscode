package.path = package.path .. ';../../Lua/TouhouTB/characters/Common/?.lua;'

-- gui include
require "IconGui"

-- characters include
require "Character"

Meiling = Character:new({
    Strength = 12,
    Vitality = 13,
    Dexterity = 11,
    Agility = 9,
    Intelligence = 5,
    Wisdom = 4,
    dyobj = nil,
    animationPath = "./Assets/F_AObjects/meiling_tb.xml",
    portraitPath  = "./Assets/TB_GUI/faces/Meiling_face.png",
    panelPath = "./Assets/TB_GUI/panels/meiling_panel.png",
    action = 0,
    hp = 300,
    mana = 80,
    sp = 0,
    spCap = 100,
    physicDmg = 13,
    physicDef = 15,
    magicDmg = 3,
    magicDef = 6,
    accurate = 0.85,
    evadeChance = 0.3,
    critChance = 0.125,
    hpScale = 10,
    manaScale = 5,
    physicDmgScale = 4,
    magicDmgScale = 1,
    physicDefScale = 2,
    magicDefScale = 2,
    accurateScale = 0.03,
    evadeChanceScale = 0.02,
    deathDoorSurviveChance = 0.35,
    name = "Meiling",
    lastName = "Hong",
    title = "Gatekeeper",
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
function Meiling:loadCommon(host)

    self.common_actions =  Character:loadCommon(host)
    -- todo load more common of Meiling
end


