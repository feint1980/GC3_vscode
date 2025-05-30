package.path = package.path .. ';../../luaFiles/Skills/?.lua'

require "Skill"

FateFavor = Skill:new({
    name = Tag.color_TB_VIT .. "Fate's Favor" .. Tag.color_close,
    description = "Blessed, cursed, or simply chosen — Reimu Hakurei never asks. When others fall to chance, she floats through battles with uncanny timing and impossible grace. As her life wanes, the hand of fate draws nearer, weaving miracles just long enough to turn death into another resolved incident.",
    effectTxt = "At the start of each turn, Reimu has a " .. Tag.color_TB_VIT .. "5% " .. Tag.color_close .. "base chance, plus a bonus equal to her missing HP percentage, to gain 1 of these random buffs below, lasts 1 round.\n\
    > Heal " .. Tag.color_TB_VIT .. "20% " .. Tag.color_close .. "max HP.\n\
    > Gain " .. Tag.color_TB_DEX .. "40% " .. Tag.color_close .. "crit chance (only 1).\n\
    > Gain " .. Tag.color_TB_AGI .. "30% " .. Tag.color_close .. "evade chance.\n\
    > Remove all debuffs.";
    quoteTxt = "Fate protects me. Not out of kindness, but out of obligation to my duty.",
    iconPath = "./Assets/TB_GUI/faces/Reimu_face.png",
    properties = {}
})
