package.path = package.path .. ";../../luaFiles/?.lua" .. ";../luaFiles/Skills/?.lua"

require "BS_Skill"

-- BS_Skill_HakureiKick = 

---@class BS_Skill_HakureiKick : BS_Skill
BS_Skill_HakureiKick = setmetatable({}, {__index = BS_Skill})
BS_Skill_HakureiKick.__index = BS_Skill_HakureiKick

---@param character BS_Character
---@---@return BS_Skill_HakureiKick
function BS_Skill_HakureiKick:create(character)

    local o = BS_Skill:new()

    o.dmg = BS_DMG:new({
        dmgValue = character:getPhysicDmg() * 0.5 + (character:getAgility() + character:getDexterity() * 0.75),
        dmgType = BS_DMG_Type.PHYSICAL
    })

    o.cost = BS_SkillCost:new({
        apCost = 1,
        manaCost = 25,
        spCost = 0,
        hpCost = 0,
        manaPercentCost = 0,
        hpPercentCost = 0
    })

    o.id          = "SKILL_HAKUREI_KICK"
    o.name        = "Hakurei's Kick"

    o.isPassive = false

    o.description = "A swift kick infused with faint spirit energy.\nDisplace target, deal " .. TextColor.color_red .. tostring(o.dmg.dmgValue) .. TextColor.color_close .. " damage and \napply a " .. TextColor.color_TB_DEX .. "weak push 1" .. TextColor.color_close .. " cell.\nReimu moves forward 1 cell"

    o.costText =TextColor.color_orange .. "AP: " ..  tostring(o.cost.apCost) .. TextColor.color_close .. TextColor.color_TB_WIS .. " Mana: "  .. tostring(o.cost.manaCost) .. TextColor.color_close

    o.requiredPosition =  BS_Required_Position.MIDDLE

    o.targetPosition    = BS_Target_Position:new(BS_Required_Position.FRONT | BS_Required_Position.MIDDLE, true)

    return o
end


---@return BS_Skill_HakureiKick