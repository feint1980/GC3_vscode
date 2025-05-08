package.path = package.path .. ";../luaFiles/?.lua" 

require "SV_global"
require "S_Character"


Character_Table["S_Yukari"] = S_Character:new(

{
    Strenth = 7,
    Vitality = 9,
    Dexterity = 7,
    Agility = 5,
    Intelligence = 15,
    Wisdom = 22,
    animationPath = "./Assets/F_AObjects/yukari_tb.xml",
    portraitPath  = "./Assets/TB_GUI/faces/Yukari_face.png",
    panelPath = "./Assets/TB_GUI/panels/yukari_panel.png",
    action = 0,
    hp = 130,
    mana = 200,
    sp = 0,
    spCap = 100,
    physicDmg = 7,
    physicDef = 7,
    magicDmg = 20,
    magicDef = 11,
    accurate = 0.85,
    evadeChance = 0.1,
    critChance = 0.125,
    hpScale = 8,
    manaScale = 10,
    physicDmgScale = 2,
    magicDmgScale = 3.3,
    physicDefScale = 1.7,
    magicDefScale = 2.1,
    accurateScale = 0.035,
    evadeChanceScale = 0.025,
    deathDoorSurviveChance = 0.275,
    name = "Yukari",
    lastName = "Yakumo",
    title = "Youkai of Boundaries",
    side = 1,
    level = 1,
    xp = 0,
    ID = "T_YUKARI"
})

