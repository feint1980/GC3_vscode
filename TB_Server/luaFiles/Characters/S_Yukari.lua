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
-- I must say that Yukari passive is somewhat unpredictable, keep the standard stat 50
S_Yukari = S_Character:new(

{
    strength = 6, --6 
    vitality = 9, -- 15 
    dexterity = 5, -- 20
    agility = 5, -- 25
    intelligence = 11, -- 38
    wisdom = 14, -- 50 
    animationPath = "./Assets/F_AObjects/yukari_tb.xml",
    portraitPath  = "./Assets/TB_GUI/faces/Yukari_face.png",
    panelPath = "./Assets/TB_GUI/panels/yukari_panel.png",
    action = 0,
    hp = 140,
    mana = 150,
    sp = 0,
    spCap = 100,
    physicDmg = 7,
    physicDef = 11,
    magicDmg = 14,
    magicDef = 12,
    accurate = 0.8,
    evadeChance = 0.2,
    critChance = 0.15,
    hpScale = 8,
    manaScale = 10,
    physicDmgScale = 1.1,
    magicDmgScale = 1.7,
    physicDefScale = 0.6,
    magicDefScale = 0.8,
    accurateScale = 0.031,
    evadeChanceScale = 0.025,
    deathDoorSurviveChance = 0.26,
    name = "Yukari",
    lastName = "Yakumo",
    title = "Youkai of Boundaries",
    side = 1,
    level = 1,
    xp = 0,
    price = 45,
    ID = "S_Yukari"
})

Character_Table["S_Yukari"] = S_Yukari