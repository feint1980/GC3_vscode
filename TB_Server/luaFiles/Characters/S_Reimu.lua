package.path = package.path .. ";../luaFiles/?.lua" 

require "SV_global"
require "S_Character"

S_Reimu = S_Character:new(
{
    Strength = 7,
    Vitality = 6,
    Dexterity = 11,
    Agility = 10,
    Intelligence = 8,
    Wisdom = 8,
    animationPath = "./Assets/F_AObjects/reimu_tb.xml",
    portraitPath  = "./Assets/TB_GUI/faces/Reimu_face.png",
    panelPath = "./Assets/TB_GUI/panels/reimu_panel.png",
    action = 0,
    hp = 80,
    mana = 120,
    sp = 0,
    spCap = 100,
    physicDmg = 14,
    physicDef = 6,
    magicDmg = 12,
    magicDef = 6.8,
    accurate = 0.85,
    evadeChance = 0.18,
    critChance = 0.025,
    hpScale = 8,
    manaScale = 9,
    physicDmgScale = 1.5,
    magicDmgScale = 1.2,
    physicDefScale = 0.5,
    magicDefScale = 0.45,
    accurateScale = 0.031,
    evadeChanceScale = 0.023,
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
