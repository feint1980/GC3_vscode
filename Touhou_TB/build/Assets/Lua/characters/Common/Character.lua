package.path = package.path .. ';./Assets/lua/Icons/?.lua;' .. ';./Assets/lua/system/?.lua;'
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
---@field HitChance number
---@field Evasion number
---@field CriticalHitChance number
---@field PhysicalDefense number
---@field MagicDefense number
---@field Speed number 
Character = {

    ---@type number Strength(STR) Primary Influence: Physic dmg (scale : 2) | Carry weight(not implemented yet)
    Strength = 8,

    ---@type number Vitality(VIT) Primary Influence: Health (HP), Status resistant
    Vitality = 8,

    ---@type number Dexterity(DEX) Primary Influence: Accuracy & Critical Hit Chance (Physical) Other Effects: Increases hit chance with physical attacks, and could also raise the chance for critical strikes. Dexterity could also enhance skills or abilities that require precision, such as archery or certain melee attacks.
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
    currentSlot = nil

}

function Character:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

---@return number The turn of the character | Fomula 1 + (Agility/7 * 0.25) |
function Character:getTurn()
    local count = math.modf(self.Agility / 7)
    return 1 +( count * 0.25)
end

function Character:getHP()
    local additionHP = self.Vitality * 8
    return self.hp + additionHP
end

function Character:getMana()
    local additionMana = self.Wisdom * 7
    return self.mana + additionMana
end

function Character:getPhysicDmg()
    return 5 +  self.Strength * 2
end

function Character:getMagicDmg()
    local additionDmg = self.Intelligence * 3
    return 10 + additionDmg
end

function Character:getPhysicDef()
    local additionDef = self.Vitality * 1
    return 10 + additionDef
end

function Character:getMagicDef()
    local additionDef = self.Wisdom * 1
    return 10 + additionDef
end

function Character:getAccurate(additionalRoll)
    local additionalRoll = additionalRoll or 0
    local additionAcc = (additionalRoll+ self.Dexterity ) * 0.03
    return 0.5 + additionAcc
end

function Character:getEvadeChance(additionalRoll)
    local additionalRoll = additionalRoll or 0
    local additionEvade = (self.Agility + additionalRoll) * 0.02
    return 0.25 + additionEvade
end

function Character:getCritChance()
    local additionCrit = self.Dexterity * 0.013
    return 0.125 + additionCrit
end

function Character:init(host,slot,tSide)

    self.dyobj = cppCreateEnity(host,self.animationPath,slot,self.portraitPath,tSide)
    self.currentSlot = slot
    self.side = tSide
    -- set attributes
    cppSetAttribute(self.dyobj,"Strength",self.Strength)
    cppSetAttribute(self.dyobj,"Vitality",self.Vitality)
    cppSetAttribute(self.dyobj,"Dexterity",self.Dexterity)
    cppSetAttribute(self.dyobj,"Agility",self.Agility)
    cppSetAttribute(self.dyobj,"Intelligence",self.Intelligence)
    cppSetAttribute(self.dyobj,"Wisdom",self.Wisdom)

    cppSetAttribute(self.dyobj,"action",self:getTurn())
    cppSetAttribute(self.dyobj,"hp",self:getHP())
    cppSetAttribute(self.dyobj,"mana",self:getMana())
    cppSetAttribute(self.dyobj,"sp",self.sp)
    cppSetAttribute(self.dyobj,"spCap",self.spCap)

    cppSetAttribute(self.dyobj,"physicDmg",self:getPhysicDmg())
    cppSetAttribute(self.dyobj,"physicDef",self:getPhysicDef())
    cppSetAttribute(self.dyobj,"magicDmg",self:getMagicDmg())
    cppSetAttribute(self.dyobj,"magicDef",self:getMagicDef())
    cppSetAttribute(self.dyobj,"accurate",self:getAccurate())
    cppSetAttribute(self.dyobj,"evadeChance",self:getEvadeChance())
    cppSetStrAttribute(self.dyobj,"name",self.name)
    cppSetStrAttribute(self.dyobj,"lastName",self.lastName)
    cppSetStrAttribute(self.dyobj,"title",self.title)

    --return self
end

function Character:loadCommon(host)

    print("load common call")
    self.common_actions = {}
    self.common_actions["Move"] = Move
    self.common_actions["Move"]:init(host,self.dyobj,self)

    self.common_actions["End"] = End
    self.common_actions["End"]:init(host,self.dyobj,self)

    print("sort skills called")
    --self.common_actions = sortData(self.common_actions)
    t_common_actions = {}
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

