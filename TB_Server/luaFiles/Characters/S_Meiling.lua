package.path = package.path .. ";../luaFiles/?.lua" 

require "SV_global"
require "S_Character"

S_Meiling = S_Character:new(

{
    Strength = 12,
    Vitality = 14,
    Dexterity = 11,
    Agility = 9,
    Intelligence = 4,
    Wisdom = 5,
    animationPath = "./Assets/F_AObjects/meiling_tb.xml",
    portraitPath  = "./Assets/TB_GUI/faces/Meiling_face.png",
    panelPath = "./Assets/TB_GUI/panels/meiling_panel.png",
    action = 0,
    hp = 140,
    mana = 70,
    sp = 0,
    spCap = 100,
    physicDmg = 12,
    physicDef = 8.5,
    magicDmg = 8,
    magicDef = 3.3,
    accurate = 0.81,
    evadeChance = 0.13,
    critChance = 0.022,
    hpScale = 11,
    manaScale = 6,
    physicDmgScale = 1.7,
    magicDmgScale = 0.8,
    physicDefScale = 1.2,
    magicDefScale = 0.7,
    accurateScale = 0.032,
    evadeChanceScale = 0.029,
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