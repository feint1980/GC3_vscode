package.path = package.path .. ";../luaFiles/?.lua" 

require "SV_global"
require "S_Character"

Character_Table["S_Meiling"] = S_Character:new(

{
    Strength = 17,
    Vitality = 18,
    Dexterity = 15,
    Agility = 15,
    Intelligence = 6,
    Wisdom = 6,
    animationPath = "./Assets/F_AObjects/meiling_tb.xml",
    portraitPath  = "./Assets/TB_GUI/faces/Meiling_face.png",
    panelPath = "./Assets/TB_GUI/panels/meiling_panel.png",
    action = 0,
    hp = 140,
    mana = 70,
    sp = 0,
    spCap = 100,
    physicDmg = 16,
    physicDef = 11.5,
    magicDmg = 8.7,
    magicDef = 3.3,
    accurate = 0.9,
    evadeChance = 0.25,
    critChance = 0.125,
    hpScale = 9,
    manaScale = 7,
    physicDmgScale = 3.2,
    magicDmgScale = 0.8,
    physicDefScale = 1.2,
    magicDefScale = 0.7,
    accurateScale = 0.039,
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