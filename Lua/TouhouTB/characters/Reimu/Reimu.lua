-- package.path = package.path  .. '../Common/?.lua' .. ';./Assets/Lua/characters/Common/?.lua;'

package.path = package.path .. ';../../Lua/TouhouTB/characters/Common/?.lua;'

-- gui include
require "IconGui"

-- characters include
require "Character"
require "kickBack"

---@class Reimu: Character


---@Description Reimu inherits from Character
---@return Reimu
Reimu = Character:new({
    Strenth = 7,
    Vitality = 7,
    Dexterity = 12,
    Agility = 11,
    Intelligence = 8,
    Wisdom = 9,
    dyobj = nil,
    animationPath = "./Assets/F_AObjects/reimu_tb.xml",
    portraitPath  = "./Assets/TB_GUI/faces/Reimu_face.png",
    panelPath = "./Assets/TB_GUI/panels/reimu_panel.png",
    action = 0,
    hp = 200,
    mana = 120,
    sp = 0,
    spCap = 100,
    physicDmg = 11,
    physicDef = 10,
    magicDmg = 11,
    magicDef = 8,
    accurate = 0.88,
    evadeChance = 0.33,
    critChance = 0.13,
    hpScale = 8,
    manaScale = 7,
    physicDmgScale = 4,
    magicDmgScale = 3,
    physicDefScale = 2,
    magicDefScale = 2,
    accurateScale = 0.03,
    evadeChanceScale = 0.02,
    deathDoorSurviveChance = 0.3,
    name = "Reimu",
    lastName = "Hakurei",
    title = "Hakurei Shrine Maiden",
    common_actions = {},
    items = {},
    skills = {},
    currentSlot = nil
}
)

---@Description Reimu inherits from Character
---@function Reimu:loadCommon
---@param host pointer instance of BattleScene
---@return table
function Reimu:loadCommon(host)

    self.common_actions =  Character:loadCommon(host)
    return self.common_actions
    -- todo load more common of reimu
end

---@Description Reimu inherits from Character
---@function Reimu:loadSkills
function Reimu:loadSkills(host)

    -- local t_skills = {}
    self.skills = {}
    self.skills["KickBack"] = KickBack
    self.skills["KickBack"]:init(host,self.dyobj,self)

end
