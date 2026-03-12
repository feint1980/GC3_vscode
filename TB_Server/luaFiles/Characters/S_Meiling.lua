package.path = package.path .. ";../luaFiles/?.lua" 

require "SV_global"
require "S_Character"

-- standard stats : 50 
-- standard dmg : 21
-- standard dmgScale : 2.8
-- standard def : 25
-- standard defScale : 1.4
-- standard hp/mana : 290
-- hp/mana scale : 18
-- accurate chance/scale 0.8 / 0.031
-- evade chance/scale 0.2 / 0.025
-- crit chance : 0.15 calculated by : 0.15 + (dex * 0.1)
-- deathDoorSurviveChance : depend
-- Meiling passive is kinda meh so , increase base stat by 4 (54) 

S_Meiling = S_Character:new(
{
    strength = 12, -- 12
    vitality = 14, -- 26
    dexterity = 12, -- 38
    agility = 10, -- 48
    intelligence = 3, -- 51
    wisdom = 3, -- 54
    animationPath = "./Assets/F_AObjects/meiling_tb.xml",
    portraitPath  = "./Assets/TB_GUI/faces/Meiling_face.png",
    panelPath = "./Assets/TB_GUI/panels/meiling_panel.png",
    action = 0,
    hp = 200,
    mana = 90,
    sp = 0,
    spCap = 100,
    physicDmg = 14,
    physicDef = 16,
    magicDmg = 7,
    magicDef = 9,
    accurate = 0.8,
    evadeChance = 0.2,
    critChance = 0.15,
    hpScale = 11,
    manaScale = 7,
    physicDmgScale = 1.8,
    magicDmgScale = 1.0,
    physicDefScale = 0.9,
    magicDefScale = 0.5,
    accurateScale = 0.031,
    evadeChanceScale = 0.025,
    deathDoorSurviveChance = 0.3,
    name = "Meiling",
    lastName = "Hong",
    title = "Gatekeeper of Scarlet Devil Mansion",
    side = 1,
    level = 1,
    xp = 0,
    price = 35,
    ID = "S_Meiling"
})

Character_Table["S_Meiling"] = S_Meiling