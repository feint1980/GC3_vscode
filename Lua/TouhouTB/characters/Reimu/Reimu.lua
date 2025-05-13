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
    Agility = 10,
    Intelligence = 8,
    Wisdom = 9,
    dyobj = nil,
    animationPath = "./Assets/F_AObjects/reimu_tb.xml",
    portraitPath  = "./Assets/TB_GUI/faces/Reimu_face.png",
    panelPath = "./Assets/TB_GUI/panels/reimu_panel.png",
    action = 1.0,
    hp = 80,
    mana = 100,
    sp = 0,
    spCap = 100,
    physicDmg = 5,
    physicDef = 5,
    magicDmg = 5,
    magicDef = 5,
    accurate = 0.9,
    evadeChance = 0.3,
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
