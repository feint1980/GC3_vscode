package.path = package.path .. ";../luaFiles/?.lua" 

require "SV_global"

---@class S_Character
S_Character =  {
    Strenth = 10,
    Vitality = 10,
    Dexterity = 10,
    Agility = 10,
    Intelligence = 10,
    Wisdom = 10,
    animationPath = "No",
    portraitPath  = "No",
    panelPath = "No",
    action = 0,
    hp = 100,
    mana = 100,
    sp = 0,
    spCap = 100,
    physicDmg = 10,
    physicDef = 10,
    magicDmg = 10,
    magicDef = 10,
    accurate = 0.5,
    evadeChance = 0.25,
    critChance = 0.125,
    hpScale = 9,
    manaScale = 7,
    physicDmgScale = 1,
    magicDmgScale = 1,
    physicDefScale = 1,
    magicDefScale = 1,
    accurateScale = 0.03,
    evadeChanceScale = 0.02,
    deathDoorSurviveChance = 0.3,
    name = "Nameless",
    lastName = "the Nameless",
    title = "Titleless",
    side = 1,
    level = 1,
    xp = 0,
    ID = "T_INVALID"
}


---@Description create a new instance of Character
---@param o? table
---@return S_Character
function S_Character:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

