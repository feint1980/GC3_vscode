package.path = package.path .. ";../luaFiles/?.lua" 

require "SV_global"
require "S_Character"

Character_Table["S_Reimu"] = S_Character:new(
{
    Strength = 9,
    Vitality = 8,
    Dexterity = 13,
    Agility = 13,
    Intelligence = 10,
    Wisdom = 11,
    animationPath = "./Assets/F_AObjects/reimu_tb.xml",
    portraitPath  = "./Assets/TB_GUI/faces/Reimu_face.png",
    panelPath = "./Assets/TB_GUI/panels/reimu_panel.png",
    action = 0,
    hp = 100,
    mana = 120,
    sp = 0,
    spCap = 100,
    physicDmg = 14,
    physicDef = 6,
    magicDmg = 12,
    magicDef = 6.8,
    accurate = 0.95,
    evadeChance = 0.15,
    critChance = 0.125,
    hpScale = 8,
    manaScale = 9,
    physicDmgScale = 2.5,
    magicDmgScale = 2.2,
    physicDefScale = 0.5,
    magicDefScale = 0.45,
    accurateScale = 0.039,
    evadeChanceScale = 0.029,
    deathDoorSurviveChance = 0.25,
    name = "Reimu",
    lastName = "Hakurei",
    title = "Hakurei Miko",
    side = 1,
    level = 1,
    xp = 0,
    price = 40,
    ID = "S_Reimu"
})

