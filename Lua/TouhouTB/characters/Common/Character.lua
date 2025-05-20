package.path = package.path .. ';../../Lua/TouhouTB/Icons/?.lua;' .. ';../../Lua/TouhouTB/system/?.lua;'
require "Move"
require "End"

require "system"

---@class pointer

--[[
> Strength (STR)
Primary Influence: Physical Damage | scale value is 3
Other Effects: Increases the damage dealt by physical attacks, heavy weapons, or abilities that rely on raw power. Could also contribute to the character's ability to break through shields or armor.

> Vitality (VIT)
Primary Influence: Health & Physical Defense | scale value is 1 
Other Effects: Determines max HP, physical defense, and resistance to status ailments related to physical endurance (such as bleeding, poison, or stun). It could also reduce incoming physical damage by a percentage.

> Dexterity (DEX)
Primary Influence: Accuracy & Critical Hit Chance (Physical) 
Other Effects: Increases hit chance with physical attacks, and could also raise the chance for critical strikes. Dexterity could also enhance skills or abilities that require precision, such as archery or certain melee attacks.

> Agility (AGI)
Primary Influence: Speed & Evasion
Other Effects: Determines turn order (faster characters act first) and increases evasion against physical attacks. Higher agility could also reduce the chance of getting hit by slower enemies and allow characters to reposition more easily.

> Intelligence (INT)
Primary Influence: Magic Damage
Other Effects: Increases the damage dealt by magical attacks and spells. It could also affect the potency of debuffs, the number of targets a spell can hit, or even mana regeneration rates.

> Wisdom (WIS)
Primary Influence: Magic Defense & Mana Pool
Other Effects: Determines resistance to magical attacks and could increase max mana. Wisdom could also affect healing abilities, status effect resistance (such as confusion or charm), and reduce the cooldowns on certain spells or abilities.

Derived Stats:
> Hit Chance: Primarily influenced by Dexterity, could be affected by Agility for ranged or fast attacks.

Evasion: Influenced by Agility, with a potential bonus from Wisdom (to dodge magical effects).

Critical Hit Chance: Influenced by Dexterity (for physical attacks) and possibly Intelligence (for magical criticals).

Physical Defense: Primarily governed by Vitality, with some influence from Strength for sturdier builds.

Magic Defense: Primarily governed by Wisdom, with a potential small influence from Intelligence for spellcasters.

Speed: Purely determined by Agility; affects turn order in combat.]]--

---@class (exact) Character
---@field Strength number
---@field Vitality number
---@field Dexterity number
---@field Agility number
---@field Intelligence number
---@field Wisdom number
---@field Evasion number
---@field PhysicalDefense number
---@field MagicDefense number
---@field Speed number 
---@field dyobj? pointer instance of F_Lua_BaseEntity
---@field animationPath string
---@field portraitPath string
---@field panelPath string
---@field action number
---@field hp number
---@field mana number
---@field sp number
---@field spCap number
---@field physicDmg number
---@field physicDef number
---@field magicDmg number
---@field magicDef number
---@field accurate number
---@field evadeChance number
---@field hitChance number
---@field critChance number
---@field hpScale number
---@field manaScale number
---@field physicDmgScale number
---@field magicDmgScale number
---@field physicDefScale number
---@field magicDefScale number
---@field accurateScale number
---@field evadeChanceScale number
---@field deathDoorSurviveChance number
---@field name string
---@field lastName string
---@field title string
---@field side number
---@field common_actions table
---@field items table   
---@field skills table
---@field currentSlot pointer slot object
Character = {
    ---@type number Strength(STR) Primary Influence: Physic dmg (scale : 2) | Physical displace chance/resistant  
    Strength = 8,

    ---@type number Vitality(VIT) Primary Influence: Health (HP), Status resistance, Last stance resistance, Physic def, Crit resistance 
    Vitality = 8,

    ---@type number Dexterity(DEX) Primary Influence: Accuracy (Physic) & Critical Hit Chance (Physical) Other Effects: Increases hit chance with physical attacks, and could also raise the chance for critical strikes.
    Dexterity = 8,

    ---@type number Agility(AGI) Primary Influence: Speed & Evasion |Other Effects: Determines turn order (faster characters act first) and increases evasion against physical attacks. Higher agility could also reduce the chance of getting hit by slower enemies and allow characters to reposition more easily.
    Agility = 8,

    ---@type number Intelligence (INT) Primary Influence: Magic Damage scale value by 3|Other Effects: Increases the damage dealt by magical attacks and spells. It could also affect the potency of debuffs, the number of targets a spell can hit, or even mana regeneration rates.
    Intelligence = 8,

    ---@type number Wisdom (WIS) Primary Influence: Magic Defense & Mana Pool|Other Effects: Determines resistance to magical attacks and could increase max mana. Wisdom could also affect healing abilities, status effect resistance (such as confusion or charm), and reduce the cooldowns on certain spells or abilities.
    Wisdom = 8,

    ---@type pointer instance of F_Lua_BaseEntity
    dyobj = nil,
    ---@type string The path to the animation file
    animationPath = "./Assets/F_AObjects/patchouli_tb.xml",
    ---@type string The path to the portrait file
    portraitPath  = "./Assets/TB_GUI/faces/missing.png",
    ---@type string The path to the panel file
    panelPath = "./Assets/TB_GUI/panels/missing.png",
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
    evadeChance = 0.1,
    critChance = 0.125,
    hpScale = 8,
    manaScale = 7,
    physicDmgScale = 2,
    magicDmgScale = 3,
    physicDefScale = 1,
    magicDefScale = 1,
    accurateScale = 0.3,
    evadeChanceScale = 0.2,
    deathDoorSurviveChance = 0.25,
    name = "Nameless",
    lastName = "None",
    title = "None",
    ---@type number The side of the character |1 = left, 2 = right|
    side = 1,
    ---@type table The list of common actions
    common_actions = {},
    ---@type table The list of items
    items = {},
    ---@type table The list of skills
    skills = {},
    ---@type pointer? instance of Slot 
    currentSlot = nil
}

---@Description create a new instance of Character
---@param o? table
---@return Character
function Character:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

---@Description set the character desc from C++ side
---@param desc pointer instance of CharacterDesc
function Character:setDesc(desc)
    Character_SetDesc(self.dyobj, desc)

    self.Strength = Character_GetAttribute(self.dyobj, "str")
    self.Vitality = Character_GetAttribute(self.dyobj, "vit") 
    self.Dexterity = Character_GetAttribute(self.dyobj, "dex")
    self.Agility = Character_GetAttribute(self.dyobj, "agi")
    self.Intelligence = Character_GetAttribute(self.dyobj, "int")
    self.Wisdom = Character_GetAttribute(self.dyobj, "wis")
    self.animationPath = Character_GetAttributeStr(self.dyobj, "animationPath")
    self.portraitPath = Character_GetAttributeStr(self.dyobj, "portraitPath")
    self.panelPath = Character_GetAttributeStr(self.dyobj, "panelPath")
    self.hp = Character_GetAttribute(self.dyobj, "hp")
    self.mana = Character_GetAttribute(self.dyobj, "mana")
    self.sp = Character_GetAttribute(self.dyobj, "sp")
    self.spCap = Character_GetAttribute(self.dyobj, "spCap")
    self.physicDmg = Character_GetAttribute(self.dyobj, "physicDmg")
    self.physicDef = Character_GetAttribute(self.dyobj, "physicDef")
    self.magicDmg = Character_GetAttribute(self.dyobj, "magicDmg")
    self.magicDef = Character_GetAttribute(self.dyobj, "magicDef")
    self.accurate = Character_GetAttribute(self.dyobj, "accurate")
    self.evadeChance = Character_GetAttribute(self.dyobj, "evadeChance")
    self.critChance = Character_GetAttribute(self.dyobj, "critChance")
    self.hpScale = Character_GetAttribute(self.dyobj, "hpScale")
    self.manaScale = Character_GetAttribute(self.dyobj, "manaScale")
    self.physicDmgScale = Character_GetAttribute(self.dyobj, "physicDmgScale")
    self.magicDmgScale = Character_GetAttribute(self.dyobj, "magicDmgScale")
    self.physicDefScale = Character_GetAttribute(self.dyobj, "physicDefScale")
    self.magicDefScale = Character_GetAttribute(self.dyobj, "magicDefScale")
    self.accurateScale = Character_GetAttribute(self.dyobj, "accurateScale")
    self.evadeChanceScale = Character_GetAttribute(self.dyobj, "evadeChanceScale")
    self.deathDoorSurviveChance = Character_GetAttribute(self.dyobj, "deathDoorSurviveChance")
    
    self.name = Character_GetAttributeStr(self.dyobj, "name")
    self.lastName = Character_GetAttributeStr(self.dyobj, "lastName")
    self.title = Character_GetAttributeStr(self.dyobj, "title")
    -- self.hp = 
end

--------------------------------------------------------


---@Description Get the turn of the character
---@return number The turn of the character | Fomula 1 + (Agility/7 * 0.25) |
function Character:getTurn()
    local count = math.modf(self.Agility / 7)
    return 1 +( count * 0.25)
end

---@Description Get the HP of the character
---@return number The HP of the character
function Character:getHP()
    local additionHP = self.Vitality * self.hpScale
    return self.hp + additionHP
end

---@Description Get the Mana of the character
---@return number The Mana of the character
function Character:getMana()
    local additionMana = self.Wisdom * self.manaScale
    return self.mana + additionMana
end

---@Description Get the Physical Damage of the character
---@return number The Physical Damage of the character
function Character:getPhysicDmg()
    return self.physicDmg +  self.Strength * self.physicDmgScale
end

---@Description Get the Magic Damage of the character
---@return number The Magic Damage of the character
function Character:getMagicDmg()
    local additionDmg = self.Intelligence * self.magicDmgScale
    return self.magicDmg + additionDmg
end

---@Description Get the Physical Defense of the character
---@return number The Physical Defense of the character
function Character:getPhysicDef()
    local additionDef = self.Vitality * self.physicDefScale
    return self.physicDef + additionDef
end

---@Description Get the Magic Defense of the character
---@return number The Magic Defense of the character
function Character:getMagicDef()
    local additionDef = self.Wisdom * self.magicDefScale
    return self.magicDef + additionDef
end

---@Description Get the Accuracy of the character
---@param additionalRoll? number
---@return number The Accuracy of the character
function Character:getAccurate(additionalRoll)
    additionalRoll = additionalRoll or 0
    local additionAcc = (additionalRoll+ self.Dexterity ) * self.accurateScale
    return self.accurate + additionAcc
end

---@Description Get the Evasion of the character
---@param additionalRoll? number
---@return number The Evasion of the character
function Character:getEvadeChance(additionalRoll)
    additionalRoll = additionalRoll or 0
    local additionEvade = (self.Agility + additionalRoll) * self.evadeChanceScale
    return self.evadeChance + additionEvade
end

---@Description Get the Critical Chance of the character
---@return number The Critical Chance of the character
function Character:getCritChance()
    local additionCrit = self.Dexterity * 0.027
    return self.critChance + additionCrit
end

function Character:getDeathDoorSurviveChance(additonalRoll)
    additonalRoll = additonalRoll or 0
    local additionSurvive = (self.Vitality + additonalRoll) * 0.03
    return self.deathDoorSurviveChance + additionSurvive
end

---@Description Initialize the character Non CB
---@param host pointer instance of ClientCharacterHandler
---@param name string
---@param desc pointer instance of CharacterDesc
---@return pointer instance of F_Lua_BaseEntity
function Character:initNonCB(host,name,desc)
    self.dyobj=  cpp_CreateCharacterNon_CB(host,name,desc)
    self:setDesc(desc)
    return self.dyobj
end

---@Description Initialize the character
---@param host pointer instance of BattleScene
---@param slot pointer The slot where the character is created
---@param tSide number 1 = left, 2 = right
function Character:init(host,slot,tSide)

    self.dyobj = TB_CreateEntity(host,self.animationPath,slot,self.portraitPath,tSide)
    self.currentSlot = slot
    self.side = tSide
    -- set attributes
    TB_SetAttribute(self.dyobj,"Strength",self.Strength)
    TB_SetAttribute(self.dyobj,"Vitality",self.Vitality)
    TB_SetAttribute(self.dyobj,"Dexterity",self.Dexterity)
    TB_SetAttribute(self.dyobj,"Agility",self.Agility)
    TB_SetAttribute(self.dyobj,"Intelligence",self.Intelligence)
    TB_SetAttribute(self.dyobj,"Wisdom",self.Wisdom)

    TB_SetStrAttribute(self.dyobj, "animationPath", self.animationPath)
    TB_SetStrAttribute(self.dyobj, "portraitPath    ", self.portraitPath)
    TB_SetStrAttribute(self.dyobj, "panelPath", self.panelPath)

    TB_SetAttribute(self.dyobj,"action",self:getTurn())
    TB_SetAttribute(self.dyobj,"hp",self:getHP())
    TB_SetAttribute(self.dyobj,"mana",self:getMana())
    TB_SetAttribute(self.dyobj,"sp",self.sp)
    TB_SetAttribute(self.dyobj,"spCap",self.spCap)

    TB_SetAttribute(self.dyobj,"physicDmg",self:getPhysicDmg())
    TB_SetAttribute(self.dyobj,"physicDef",self:getPhysicDef())
    TB_SetAttribute(self.dyobj,"magicDmg",self:getMagicDmg())
    TB_SetAttribute(self.dyobj,"magicDef",self:getMagicDef())
    TB_SetAttribute(self.dyobj,"accurate",self:getAccurate())

    TB_SetAttribute(self.dyobj,"evadeChance",self:getEvadeChance())
    TB_SetAttribute(self.dyobj,"critChance",self:getCritChance())
    TB_SetAttribute(self.dyobj, "hpScale", self.hpScale)
    TB_SetAttribute(self.dyobj, "manaScale", self.manaScale)
    TB_SetAttribute(self.dyobj, "physicDmgScale", self.physicDmgScale)
    TB_SetAttribute(self.dyobj, "physicDefScale", self.physicDefScale)
    TB_SetAttribute(self.dyobj, "magicDmgScale", self.magicDmgScale)
    TB_SetAttribute(self.dyobj, "magicDefScale", self.magicDefScale)
    TB_SetAttribute(self.dyobj, "accurateScale", self.accurateScale)
    TB_SetAttribute(self.dyobj, "evadeChanceScale", self.evadeChanceScale)
    TB_SetAttribute(self.dyobj, "deathDoorSurviveChance", self.deathDoorSurviveChance)

    TB_SetStrAttribute(self.dyobj,"name",self.name)
    TB_SetStrAttribute(self.dyobj,"lastName",self.lastName)
    TB_SetStrAttribute(self.dyobj,"title",self.title)

    --return self
end

---@Description Load the common actions of the character
---@param host pointer instance of BattleScene
---@return table The common actions
function Character:loadCommon(host)

    print("load common call")
    self.common_actions = {}
    self.common_actions["Move"] = Move
    self.common_actions["Move"]:init(host,self.dyobj,self)

    self.common_actions["End"] = End
    self.common_actions["End"]:init(host,self.dyobj,self)

    print("sort skills called")
    --self.common_actions = sortData(self.common_actions)
    local t_common_actions = {}
    for k,v in pairs(self.common_actions) do
        table.insert(t_common_actions, v)
    end
    table.sort(t_common_actions, function(a,b) return a.index < b.index end)
    print("sort skills ended")
    self.common_actions = {}
    self.common_actions = t_common_actions
    --table.shallow_copy(self.common_actions, t_common_actions)
    print("common action size (common) " .. #self.common_actions)
    return self.common_actions

end

---@function Character:determineEvade
---@param enemy Character The enemy character
---@return boolean
function Character:determineEvade(enemy)
    print("determine evade called")
    local selfRoll = roll(1,6) 
    local enemyRoll = roll(1,6)
    local evd = self:getEvadeChance(selfRoll)
    local att = enemy:getAccurate(enemyRoll)
    local hitchance = att - evd
    local rollchance = roll(1,100)
    rollchance = rollchance / 100
    print("rollchance " .. rollchance .. "/ hitchance " .. hitchance)

    if rollchance > hitchance then
        return true -- target evaded
    else
        return false -- target not evaded
    end
end


---@Description Load the skills of the character
---@function Character:loadSkills
---@param host pointer instance of BattleScene
function Character:loadSkills(host)
    --todo : inherits and override
end

--- Wrappers
---wrapper of cpp_setEntityCharacterDesc
---@Description set the character desc
---@param dyobj pointer instance of F_Lua_BaseEntity
---@param desc pointer instance of CharacterDesc
function Character_SetDesc(dyobj, desc)
    cpp_setEntityCharacterDesc(dyobj, desc)
end

---wrapper of cpp_setCharactercAttribute
---@Description set the character desc
---@param dyobj pointer instance of F_Lua_BaseEntity
---@param name string The name of the attribute
---@param value number The value of the attribute
function Character_SetAttribute(dyobj, name, value)
    cpp_setCharactercAttribute(dyobj, name, value)
end

---wrapper of cpp_setCharactercAttributeStr
---@Description set the character desc
---@param dyobj pointer instance of F_Lua_BaseEntity
---@param name string The name of the attribute
---@param value string The value of the attribute
function Character_SetAttributeStr(dyobj, name, value)
    cpp_setCharactercAttributeStr(dyobj, name, value)
end

---wrapper of cpp_getEntityCharacterAttribute
---@Description set the character desc
---@param dyobj pointer instance of F_Lua_BaseEntity
---@param name string The name of the attribute
function Character_GetAttribute(dyobj, name)
    return cpp_getEntityCharacterAttribute(dyobj, name)
end


---wrapper of cpp_getEntityCharacterAttributeStr
---@Description set the character desc
---@param dyobj pointer instance of F_Lua_BaseEntity
---@param name string The name of the attribute
function Character_GetAttributeStr(dyobj, name)
    return cpp_getEntityCharacterAttributeStr(dyobj, name)
end

