package.path = package.path .. ';../luaFiles/Skills/?.lua' .. ';../Skills/?.lua' .. ';../../Lua/system/GUI/widgets/?.lua;'

require "S_Skill"
require "TGUI_RTLabel" 

require "SV_global"
--- 两仪桩
--- 仆步
--- 独立步
Skill_Table["LiangYiZhuang"] = S_Skill:new({
    name = Tag.color_TB_VIT .. "Liang Yi Zhuang" .. Tag.color_close,
    description = "Hong Meiling draws upon the ancient martial principle of duality, flowing between \nstances of defense, offense, and balance. Her posture adapts to the flow of battle \nlike Yin and Yang in constant motion.",
    effectTxt = "Meiling begins battle in Liang Yi Zhuang stance, she can switch to other \nstances, Meiling has difference abilities and gain bonuses based on which \nstance is active\n>Liang Yi Zhuang :\n  +" .. Tag.color_green .. "5% " .. Tag.color_close .. Tag.color_TB_STR .. "Physic Attack." ..Tag.color_close .."\n  +" .. Tag.color_green .. "5% " .. Tag.color_close .. Tag.color_TB_AGI .. "Physical Def." .. Tag.color_close .. "\n>Pu Bu:\n  -" .. Tag.color_red .. "35% " .. Tag.color_close .. Tag.color_TB_STR .. "Physic Attack." ..Tag.color_close .."\n  +" .. Tag.color_green .. "25%" .. Tag.color_close .. Tag.color_TB_AGI .. "Physical Def." .. Tag.color_close .. "\n>Du Li Bu:\n  +" .. Tag.color_green .. "25% " .. Tag.color_close .. Tag.color_TB_STR .. "Physic Attack." ..Tag.color_close .."\n  -" .. Tag.color_red .. "40% " .. Tag.color_close .. Tag.color_TB_AGI .. "Physical Def." .. Tag.color_close ,
    quoteTxt = "\"Heaven moves, Earth yields. I stand between.\"",
    iconPath = "./Assets/TB_GUI/faces/Meiling_face.png",
    ID = "Meiling_LiangYiZhuang",
    type = Type.innate,
    properties = {}
})
