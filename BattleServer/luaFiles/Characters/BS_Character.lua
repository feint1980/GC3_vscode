package.path = package.path .. ";../../luaFiles/?.lua" 

require "battleWrapper"
require "BS_global"

BS_Character = {
    userID = "",
    id = "",
    slotIndex = 0,
    rowPos = 0,
    colPos = 0,
    stats = nil,
    cHp = 0,    -- current hp
    cMana = 0,  -- current mana
    cSp = 0,    -- current sp
    cAction = 0,-- current action
    cDeathdoorSurvivalRate = 1.0,
}

function BS_Character:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function BS_Character:init(userID,tId, tSlotIndex, tRowPos, tColPos)
    self.userID = userID
    self.id = tId
    self.slotIndex = tSlotIndex
    self.rowPos = tRowPos
    self.colPos = tColPos

    print("BS_Character stat about to init")
    if ClientOwnedCharacters[userID] == nil then
        print("ClientOwnedCharacters[" .. userID .. "] is nil")
        return
    else
        if ClientOwnedCharacters[userID][tId] == nil then
            print("ClientOwnedCharacters[" .. userID .. "][" .. tId .. "] is nil")
            return
        else
            print("ClientOwnedCharacters[" .. userID .. "][" .. tId .. "] is valid")
            self.stats =  ClientOwnedCharacters[userID][tId]
            -- for k,v in pairs(self.stats) do
            --     print("stat " .. k .. " value " .. v)
            -- end
        end
    end

    print("stat check")
    print("|" .. self.stats.name .. "|")
    print("Physical dmg " .. self:getPhysicDmg())
    print("Magic dmg " .. self:getMagicDmg())
    print("Physical def " .. self:getPhysicDef())
    print("Magic def " .. self:getMagicDef())
    print("Max hp " .. self:getMaxHP())
    print("Max mana " .. self:getMaxMana())
    print("Max sp " .. self:getMaxSP())
    -- print("Max action " .. self:getMaxAction())
    print("Physical Accuracy " .. self:getPhysicalAccuracy())
    print("Magical Accuracy " .. self:getMagicalAccuracy())
    print("Evasion " .. self:getEvasion())
    print("Crit chance " .. self:getCritChance())
    print("Speed " .. self:getSpeed(0))
    print("Death survival " .. self:getDeathDoorSurvival())

end

function BS_Character:getPhysicDmg()
    local strength = self.stats.strength
    local physicDmg = self.stats.physicDmg
    local physicDmgScale = self.stats.physicDmgScale

    return physicDmg + (strength * physicDmgScale)

end

function BS_Character:getMagicDmg()
    local intelligence = self.stats.intelligence
    local magicDmg = self.stats.magicDmg
    local magicDmgScale = self.stats.magicDmgScale

    return magicDmg + (intelligence * magicDmgScale)

end

function BS_Character:getPhysicDef()
    local vitality = self.stats.vitality
    local physicDef = self.stats.physicDef
    local physicDefScale = self.stats.physicDefScale

    return physicDef + (vitality * physicDefScale)
end

function BS_Character:getMagicDef()
    local wisdom = self.stats.wisdom
    local magicDef = self.stats.magicDef
    local magicDefScale = self.stats.magicDefScale

    return magicDef + (wisdom * magicDefScale)
end

function BS_Character:getMaxHP()
    local hp = self.stats.hp
    local vitality = self.stats.vitality
    local hpScale = self.stats.hpScale

    return hp + (vitality * hpScale)
end

function BS_Character:getMaxMana()
    local mana = self.stats.mana
    local wisdom = self.stats.wisdom
    local manaScale = self.stats.manaScale

    return mana + (wisdom * manaScale)
end

function BS_Character:getMaxSP()
    return self.stats.spCap
end

function BS_Character:getPhysicalAccuracy()
    local dexterity = self.stats.dexterity
    local agility = self.stats.agility
    local accurate = self.stats.accurate
    local accurateScale = self.stats.accurateScale
    return accurate + (((dexterity + agility) * 0.5) * accurateScale)
end

function BS_Character:getMagicalAccuracy()
    local intelligence = self.stats.intelligence
    local wisdom = self.stats.wisdom
    local accurate = self.stats.accurate
    local accurateScale = self.stats.accurateScale
    return accurate + (((intelligence + wisdom) *0.5) * accurateScale)
end


function BS_Character:getEvasion()
    local agility = self.stats.agility
    local evadeChance = self.stats.evadeChance
    local evadeChanceScale = self.stats.evadeChanceScale

    return evadeChance + (agility * evadeChanceScale)
end

function BS_Character:getCritChance()
    local dexterity = self.stats.dexterity
    local critChance = self.stats.critChance
    return critChance + (dexterity * 0.005)
end

function BS_Character:getSpeed(speedRoll)
    local agility = self.stats.agility
    return (agility + speedRoll) * 0.9
end

function BS_Character:getDeathDoorSurvival()
    local deathDoorSurviveChance = self.stats.deathDoorSurviveChance
    local vitality = self.stats.vitality
    return (deathDoorSurviveChance + (vitality * 0.025)) * self.cDeathdoorSurvivalRate
end


--[[
stat ref 

title  of Boundaries
hp 
magicDmg 
wisdom 
action 
magicDef
dexterity 
strength 
manaScale 
physicDefScale
intelligence 
panelPath 
critChance
portraitPath 
agility 
side 
physicDmgScale 
hpScale 
exp 
vitality 
accurateScale 
level 
ID 
mana 
evadeChance 
lastName 
xp 
animationPath 
evadeChanceScale 
sp 
magicDefScale 
accurate 
price 
spCap 
magicDmgScale 
physicDmg 
physicDef 
deathDoorSurviveChance
name 
formation 2 has 4 characters

]]--


--[[ stat rule
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
