package.path = package.path .. ";../luaFiles/?.lua" 

require "SV_global"
require "characterManager"


---@class S_Character
S_Character =  {
    Strength = 10,
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
    price = 25,
    ID = "T_INVALID",
    dyobj = nil
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

---@Description Init update info
---@param userID string
---@param characterID string
---@param statsStr string
function S_Character:init(userID, characterID, statsStr)
    self.dyobj = CharacterManagerCreateCharacter(userID, characterID, statsStr)
    if  self.dyobj ~= nil then
        -- print("character " .. userID .. "|" .. characterID .. " created OK")
        self:updateInformation(self.dyobj)
    else
        -- print("character " .. userID .. "|" .. characterID .. " created failed")
    end
end

---@Description reassign the character by userID and characterID
---@param userID string
---@param characterID string
function S_Character:getCharacterByUserID_CharacterID(userID, characterID)
    self.dyobj = CM_CharacterGetCharacter(userID, characterID)
    self:updateInformation(self.dyobj)
end

---@Description set character strength (in C++ as well)
---@param str number
function S_Character:setStrength(str)
    self.Strength = str
    CM_CharacterSetAttribute(self.dyobj, "str", self.Strength)
end

---@Description set character vitality (in C++ as well)
---@param vit number
function S_Character:setVitality(vit)
    self.Vitality = vit
    CM_CharacterSetAttribute(self.dyobj, "vit", self.Vitality)
end

---@Description set character dexterity (in C++ as well)
---@param dex number
function S_Character:setDexterity(dex)
    self.Dexterity = dex
    CM_CharacterSetAttribute(self.dyobj, "dex", self.Dexterity)
end

---@Description set character agility (in C++ as well)
---@param agi number
function S_Character:setAgility(agi)
    self.Agility = agi
    CM_CharacterSetAttribute(self.dyobj, "agi", self.Agility)
end

---@Description set character intelligence (in C++ as well)
---@param int number
function S_Character:setIntelligence(int)
    self.Intelligence = int
    CM_CharacterSetAttribute(self.dyobj, "int", self.Intelligence)
end

---@Description set character wisdom (in C++ as well)
---@param wis number 
function S_Character:setWisdom(wis)
    self.Wisdom = wis
    CM_CharacterSetAttribute(self.dyobj, "wis", self.Wisdom)
end

---@Description set character action (in C++ as well)
---@param action number
function S_Character:setAction(action)
    self.action = action
    CM_CharacterSetAttribute(self.dyobj, "action", self.action)
end

-- ---@Description set character hp (in C++ as well)
-- ---@param hp number
-- function S_Character:setHP(hp)
--     self.hp = hp
--     CM_CharacterSetAttribute(self.dyobj, "hp", self.hp)
-- end

-- ---@Description set character mana (in C++ as well)
-- ---@param mana number
-- function S_Character:setMana(mana)
--     self.mana = mana
--     CM_CharacterSetAttribute(self.dyobj, "mana", self.mana)
-- end

-- ---@Description set character sp (in C++ as well)
-- ---@param sp number
-- function S_Character:setSP(sp)
--     self.sp = sp
--     CM_CharacterSetAttribute(self.dyobj, "sp", self.sp)
-- end

-- ---@Description set character spCap (in C++ as well)
-- ---@param spCap number
-- function S_Character:setSPCap(spCap)
--     self.spCap = spCap
--     CM_CharacterSetAttribute(self.dyobj, "spCap", self.spCap)
-- end

function S_Character:setXP(xp)
    self.xp = xp
    CM_CharacterSetAttribute(self.dyobj, "xp", self.xp)
end

function S_Character:setLVL( level)
    self.level = level
    CM_CharacterSetAttribute(self.dyobj, "level", self.level)
end

function S_Character:copyForJSON()
    local t = {}
    for k, v in pairs(self) do
        if k ~= "dyobj" then
            t[k] = v
        end
    end
    return t
end

function S_Character:updateInformation(dyobj)
    self.dyobj = dyobj
    self.Strength = CM_CharacterGetAttribute(self.dyobj, "str")
    self.Vitality = CM_CharacterGetAttribute(self.dyobj, "vit") 
    self.Dexterity = CM_CharacterGetAttribute(self.dyobj, "dex")
    self.Agility = CM_CharacterGetAttribute(self.dyobj, "agi")
    self.Intelligence = CM_CharacterGetAttribute(self.dyobj, "int")
    self.Wisdom = CM_CharacterGetAttribute(self.dyobj, "wis")
    self.animationPath = CM_CharacterGetAttributeStr(self.dyobj, "animationPath")
    self.portraitPath = CM_CharacterGetAttributeStr(self.dyobj, "portraitPath")
    self.panelPath = CM_CharacterGetAttributeStr(self.dyobj, "panelPath")
    self.hp = CM_CharacterGetAttribute(self.dyobj, "hp")
    self.mana = CM_CharacterGetAttribute(self.dyobj, "mana")
    self.sp = CM_CharacterGetAttribute(self.dyobj, "sp")
    self.spCap = CM_CharacterGetAttribute(self.dyobj, "spCap")
    self.physicDmg = CM_CharacterGetAttribute(self.dyobj, "physicDmg")
    self.physicDef = CM_CharacterGetAttribute(self.dyobj, "physicDef")
    self.magicDmg = CM_CharacterGetAttribute(self.dyobj, "magicDmg")
    self.magicDef = CM_CharacterGetAttribute(self.dyobj, "magicDef")
    self.accurate = CM_CharacterGetAttribute(self.dyobj, "accurate")
    self.evadeChance = CM_CharacterGetAttribute(self.dyobj, "evadeChance")
    self.critChance = CM_CharacterGetAttribute(self.dyobj, "critChance")
    self.hpScale = CM_CharacterGetAttribute(self.dyobj, "hpScale")
    self.manaScale = CM_CharacterGetAttribute(self.dyobj, "manaScale")
    self.physicDmgScale = CM_CharacterGetAttribute(self.dyobj, "physicDmgScale")
    self.magicDmgScale = CM_CharacterGetAttribute(self.dyobj, "magicDmgScale")
    self.physicDefScale = CM_CharacterGetAttribute(self.dyobj, "physicDefScale")
    self.magicDefScale = CM_CharacterGetAttribute(self.dyobj, "magicDefScale")
    self.accurateScale = CM_CharacterGetAttribute(self.dyobj, "accurateScale")
    self.evadeChanceScale = CM_CharacterGetAttribute(self.dyobj, "evadeChanceScale")
    self.deathDoorSurviveChance = CM_CharacterGetAttribute(self.dyobj, "deathDoorSurviveChance")


    self.price = CM_CharacterGetAttribute(self.dyobj, "price")

    self.name = CM_CharacterGetAttributeStr(self.dyobj, "name")
    self.lastName = CM_CharacterGetAttributeStr(self.dyobj, "lastName")
    self.title = CM_CharacterGetAttributeStr(self.dyobj, "title")
    self.ID = CM_CharacterGetAttributeStr(self.dyobj, "ID")


    self.xp = CM_CharacterGetAttribute(self.dyobj, "xp")
    self.level = CM_CharacterGetAttribute(self.dyobj, "level")

    self:setXP(self.xp)
    self:setLVL(self.level)

end

-- ---@Description wrapper of 
-- function ParseCharacterStatsFromString(statsStr)
--     return 
-- end