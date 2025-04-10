package.path = package.path .. ";../luaFiles/?.lua" 

require "global"

Character_Table["S_Patchouli"] =  
{
    Strenth = 3,
    Vitality = 4,
    Dexterity = 7,
    Agility = 4,
    Intelligence = 22,
    Wisdom = 21,
    animationPath = "./Assets/F_AObjects/patchouli_tb.xml",
    portraitPath  = "./Assets/TB_GUI/faces/Patchouli_face.png",
    action = 0,
    hp = 30,
    mana = 370,
    sp = 0,
    spCap = 100,
    physicDmg = 4,
    physicDef = 3,
    magicDmg = 25,
    magicDef = 13,
    accurate = 0.85,
    evadeChance = 0.1,
    critChance = 0.125,
    hpScale = 8,
    manaScale = 10,
    physicDmgScale = 1,
    magicDmgScale = 3.7,
    physicDefScale = 1,
    magicDefScale = 2.7,
    accurateScale = 0.035,
    evadeChanceScale = 0.025,
    deathDoorSurviveChance = 0.25,
    name = "Patchouli",
    lastName = "Knowledge",
    title = "Unmoving Library",
    side = 1,
    level = 1,
    xp = 0,
    ID = "T_PATCHY"
}

