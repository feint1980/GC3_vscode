package.path = package.path  .. '../Common/?.lua' .. ';./Assets/Lua/characters/Common/?.lua;'
-- gui include
require "IconGui"

-- characters include
require "Character"
require "kickBack"


Reimu = Character:new({
    Strenth = 9,
    Vitality = 9,
    Dexterity = 14,
    Agility = 12,
    Intelligence = 10,
    Wisdom = 11,
    dyobj = nil,
    animationPath = "./Assets/F_AObjects/reimu_tb.xml",
    action = 1.0,
    hp = 170,
    mana = 220,
    sp = 0,
    spCap = 100,
    physicDmg = 12,
    physicDef = 12,
    magicDmg = 12,
    magicDef = 11,
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

function Reimu:loadCommon(host)
   
    self.common_actions =  Character:loadCommon(host)
    -- todo load more common of reimu
end

function Reimu:loadSkills(host)

   -- local t_skills = {}
    self.skills = {}
    self.skills["KickBack"] = KickBack
    self.skills["KickBack"]:init(host,self.dyobj,self)

    -- for k,v in pairs(self.skills) do
    --     table.insert(t_skills,v)
    -- end

    -- self.skills = {}
    -- self.skills =  t_skills

    --print("skills loaded " .. #self.skills)
    --print("skills loaded " .. #t_skills)
   --return self.skills
    
end

-- Patchouli:new