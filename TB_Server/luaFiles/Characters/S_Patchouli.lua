package.path = package.path .. ";../luaFiles/?.lua" 

require "SV_global"
require "S_Character"


S_Patchouli = S_Character:new(

{
    Strength = 3,
    Vitality = 4,
    Dexterity = 7,
    Agility = 7,
    Intelligence = 26,
    Wisdom = 25,
    animationPath = "./Assets/F_AObjects/patchouli_tb.xml",
    portraitPath  = "./Assets/TB_GUI/faces/Patchouli_face.png",
    panelPath = "./Assets/TB_GUI/panels/patchouli_panel.png",
    action = 0,
    hp = 30,
    mana = 370,
    sp = 0,
    spCap = 100,
    physicDmg = 4,
    physicDef = 3,
    magicDmg = 25,
    magicDef = 9.7,
    accurate = 0.85,
    evadeChance = 0.15,
    critChance = 0.125,
    hpScale = 8,
    manaScale = 10,
    physicDmgScale = 0.5,
    magicDmgScale = 3.7,
    physicDefScale = 0.2,
    magicDefScale = 0.8,
    accurateScale = 0.035,
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