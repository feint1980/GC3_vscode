package.path = package.path .. ';../luaFiles/Skills/?.lua' .. ';../Skills/?.lua' .. ';../../Lua/system/GUI/widgets/?.lua;'

require "S_Skill"
require "TGUI_RTLabel" 

require "SV_global"

Skill_Table["RedirectiveParadox"] = S_Skill:new({
    name = Tag.color_TB_title .. "Redirective Paradox" .. Tag.color_close,
    description = "Yakumo Yukari, the enigmatic youkai who governs boundaries, bends the threads of fate to her whim. Where others see a straight line from cause to effect, she sees endless branching paths—each one a chance to turn certainty into chaos. \nTo strike her is to gamble with reality itself.",
    effectTxt = "Whenever Yukari get targted she has" .. Tag.color_TB_VIT .. "17% " .. Tag.color_close .. "chance to redirect the spell/attack to a random character (include allies).",
    quoteTxt = "\"Causality is just a polite suggestion, dear. I prefer… alternatives.\"",
    iconPath = "./Assets/TB_GUI/faces/Yukari_face.png",
    ID = "Yukari_RedirectiveParadox",
    type = Type.innate,
    properties = {}
})
