package.path = package.path  .. '../Common/?.lua' .. ';./Assets/Lua/characters/Common/?.lua;'
-- gui include
require "IconGui"

-- characters include
require "Character"
require "kickBack"


Yukari = Character:new({
    Strength = 7,
    Vitality = 9,
    Dexterity = 7,
    Agility = 5,
    Intelligence = 15,
    Wisdom = 22,
    animationPath = "./Assets/F_AObjects/yukari_tb.xml",
    portraitPath  = "./Assets/TB_GUI/faces/Yukari_face.png",
    panelPath = "./Assets/TB_GUI/panels/yukari_panel.png",
    action = 0,
    hp = 130,
    mana = 200,
    sp = 0,
    spCap = 100,
    physicDmg = 7,
    physicDef = 38,
    magicDmg = 20,
    magicDef = 7.8,
    accurate = 0.85,
    evadeChance = 0.1,
    critChance = 0.125,
    hpScale = 8,
    manaScale = 10,
    physicDmgScale = 1.5,
    magicDmgScale = 3.3,
    physicDefScale = 0.5,
    magicDefScale = 0.75,
    accurateScale = 0.035,
    evadeChanceScale = 0.025,
    deathDoorSurviveChance = 0.225,
    name = "Yukari",
    lastName = "Yakumo",
    title = "Youkai of Boundaries",
    side = 1,
    level = 1,
    xp = 0,
    price = 45,
    ID = "sdsdsd",
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


