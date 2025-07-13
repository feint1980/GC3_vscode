package.path = package.path  .. '../Common/?.lua' .. ';./Assets/Lua/characters/Common/?.lua;'
-- gui include
require "IconGui"

-- characters include
require "Character"

---@class Patchouli: Character


---@Description Patchouli inherits from Character
---@return Patchouli
Patchouli = Character:new({
    Strength = 3,
    Vitality = 4,
    Dexterity = 7,
    Agility = 7,
    Intelligence = 26,
    Wisdom = 25,
    animationPath = "./Assets/F_AObjects/patchouli_tb.xml",
    portraitPath  = "./Assets/TB_GUI/faces/Patchouli_face.png",
    panelPath = "./Assets/TB_GUI/panels/patchouli_panel.png",
    action = 0,
    hp = 30,
    mana = 370,
    sp = 0,
    spCap = 100,
    physicDmg = 4,
    physicDef = 3,
    magicDmg = 25,
    magicDef = 9.7,
    accurate = 0.85,
    evadeChance = 0.15,
    critChance = 0.125,
    hpScale = 8,
    manaScale = 10,
    physicDmgScale = 0.5,
    magicDmgScale = 3.7,
    physicDefScale = 0.2,
    magicDefScale = 0.8,
    accurateScale = 0.035,
    evadeChanceScale = 0.025,
    deathDoorSurviveChance = 0.25,
    name = "Patchouli",
    lastName = "Knowledge",
    title = "Unmoving Library",
    side = 1,
    level = 1,
    xp = 0,
    price = 40,
    ID = "T_PATCHY",
    common_actions = {},
    items = {},
    skills = {},
    currentSlot = nil
}
)

---@Description Patchouli inherits from Character
---@function Patchouli:loadCommon
---@param host pointer instance of BattleScene
---@return table
function Patchouli:loadCommon(host)
    self.common_actions =  Character:loadCommon(host)
    -- todo load more common of patchouli
end


-- Patchouli:new