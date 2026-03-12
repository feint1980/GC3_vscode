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
--- Right now Reimu passive is standard, keep the standard stat 50

S_Reimu = S_Character:new(
{
    strength = 7, -- 7
    vitality = 6, -- 13
    dexterity = 11, -- 24 
    agility = 10, -- 34
    intelligence = 8, -- 42
    wisdom = 8, -- 50
    animationPath = "./Assets/F_AObjects/reimu_tb.xml",
    portraitPath  = "./Assets/TB_GUI/faces/Reimu_face.png",
    panelPath = "./Assets/TB_GUI/panels/reimu_panel.png",
    action = 0,
    hp = 140,
    mana = 150,
    sp = 0,
    spCap = 100,
    physicDmg = 11,
    physicDef = 14,
    magicDmg = 10,
    magicDef = 11,
    accurate = 0.8,
    evadeChance = 0.2,
    critChance = 0.15,
    hpScale = 9,
    manaScale = 9,
    physicDmgScale = 1.5,
    magicDmgScale = 1.3,
    physicDefScale = 0.8,
    magicDefScale = 0.6,
    accurateScale = 0.031,
    evadeChanceScale = 0.025,
    deathDoorSurviveChance = 0.28,
    name = "Reimu",
    lastName = "Hakurei",
    title = "Hakurei Miko",
    side = 1,
    level = 1,
    xp = 0,
    price = 40,
    ID = "S_Reimu"
})

Character_Table["S_Reimu"] = S_Reimu
