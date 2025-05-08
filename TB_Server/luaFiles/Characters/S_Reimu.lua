package.path = package.path .. ";../luaFiles/?.lua" 

require "SV_global"
require "S_Character"

Character_Table["S_Reimu"] = S_Character:new(
{
    Strenth = 9,
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
    physicDef = 10,
    magicDmg = 12,
    magicDef = 9,
    accurate = 0.95,
    evadeChance = 0.15,
    critChance = 0.125,
    hpScale = 8,
    manaScale = 9,
    physicDmgScale = 3,
    magicDmgScale = 2,
    physicDefScale = 1,
    magicDefScale = 1,
    accurateScale = 0.039,
    evadeChanceScale = 0.029,
    deathDoorSurviveChance = 0.3,
    name = "Reimu",
    lastName = "Hakurei",
    title = "Hakurei Miko",
    side = 1,
    level = 1,
    xp = 0,
    ID = "T_REIMU"
})

