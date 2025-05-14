package.path = package.path  .. '../Common/?.lua' .. ';./Assets/Lua/characters/Common/?.lua;'
-- gui include
require "IconGui"

-- characters include
require "Character"

---@class Patchouli: Character


---@Description Patchouli inherits from Character
---@return Patchouli
Patchouli = Character:new({
    Strenth = 1,
    Vitality = 4,
    Dexterity = 4,
    Agility = 4,
    Intelligence = 21,
    Wisdom = 21,
    dyobj = nil,
    animationPath = "./Assets/F_AObjects/patchouli_tb.xml",
    portraitPath  = "./Assets/TB_GUI/faces/Patchouli_face.png",
    panelPath = "./Assets/TB_GUI/panels/patchouli_panel.png",
    action = 0,
    hp = 50,
    mana = 350,
    sp = 0,
    spCap = 100,
    physicDmg = 3,
    physicDef = 2,
    magicDmg = 16,
    magicDef = 9,
    accurate = 0.8,
    evadeChance = 0.26,
    critChance = 0.11,
    hpScale = 2,
    manaScale = 13,
    physicDmgScale = 1,
    magicDmgScale = 6,
    physicDefScale = 1,
    magicDefScale = 4,
    accurateScale = 0.03,
    evadeChanceScale = 0.02,
    deathDoorSurviveChance = 0.23,
    name = "Patchouli",
    lastName = "Knowledge",
    title = "Unmoving Library",
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