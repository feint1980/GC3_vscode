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
--- Right now Patchouli passive is considered OP, but I dont know how it actually work in the total game , keep the standard stat 50
S_Patchouli = S_Character:new(

{
    strength = 3, -- 3
    vitality = 4, -- 7
    dexterity = 5, -- 12 
    agility = 4, -- 16
    intelligence = 19, -- 35
    wisdom = 15, -- 50
    animationPath = "./Assets/F_AObjects/patchouli_tb.xml",
    portraitPath  = "./Assets/TB_GUI/faces/Patchouli_face.png",
    panelPath = "./Assets/TB_GUI/panels/patchouli_panel.png",
    action = 0,
    hp = 40,
    mana = 250,
    sp = 0,
    spCap = 100,
    physicDmg = 4,
    physicDef = 3,
    magicDmg = 17,
    magicDef = 12,
    accurate = 0.8,
    evadeChance = 0.2,
    critChance = 0.15,
    hpScale = 6,
    manaScale = 12,
    physicDmgScale = 0.7,
    magicDmgScale = 2.1,
    physicDefScale = 0.5,
    magicDefScale = 0.9,
    accurateScale = 0.031,
    evadeChanceScale = 0.025,
    deathDoorSurviveChance = 0.25,
    name = "Patchouli",
    lastName = "Knowledge",
    title = "Unmoving Library",
    side = 1,
    level = 1,
    xp = 0,
    price = 40,
    ID = "S_Patchouli"
})

Character_Table["S_Patchouli"] = S_Patchouli