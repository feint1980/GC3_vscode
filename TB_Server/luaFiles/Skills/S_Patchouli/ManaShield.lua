package.path = package.path .. ';../luaFiles/Skills/?.lua' .. ';../Skills/?.lua' .. ';../../Lua/system/GUI/widgets/?.lua;'

require "S_Skill"
require "TGUI_RTLabel" 

require "SV_global"

Skill_Table["ManaShield"] = S_Skill:new({
    name = Tag.color_TB_WIS .. "Mana Shield" .. Tag.color_close,
    description = "Fragile, but sustained by a reservoir of magic. Patchouli shrouds herself in layered elemental wards, allowing mana to bear the pain her body cannot. What would fell another becomes a mere fluctuation in her energy flow.",
    effectTxt = "Absorbs " .. Tag.color_TB_WIS .. "80% " .. Tag.color_close .. " of incoming damage, converting it into mana loss instead of HP damage. If her mana is depleted, the shield fails and she begins to take full damage.",
    quoteTxt = "\"The body breaks. Magic doesn't.\"",
    iconPath = "./Assets/TB_GUI/faces/Patchouli_face.png",
    type = Type.innate,
    ID = "Patchy_ManaShield",
    properties = {}
})
