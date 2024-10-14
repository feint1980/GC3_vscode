package.path = package.path .. ';./Assets/lua/Icons/?.lua;'
require "Move"
require "End"

--[[
> Strength (STR)
Primary Influence: Physical Damage
Other Effects: Increases the damage dealt by physical attacks, heavy weapons, or abilities that rely on raw power. Could also contribute to the character's ability to break through shields or armor.


> Vitality (VIT)
Primary Influence: Health & Physical Defense
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

Character = {

    Strength = 8,
    Vitality = 8,
    Dexterity = 8,
    Agility = 8,
    Intelligence = 8,
    Wisdom = 8,
    dyobj = nil,
    animationPath = "./Assets/F_AObjects/patchouli_tb.xml",
    portraitPath  = "./Assets/TB_GUI/faces/Patchouli_face.png",
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
    name = "Nameless",
    lastName = "None",
    title = "None",
    side = 1,
    common_actions = {},
    items = {},
    skills = {},
    currentSlot = nil

}

function Character:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function Character:getTurn()

    
    local count = self.Agility / 5
    

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
    cppSetAttribute(self.dyobj,"action",self.action)
    cppSetAttribute(self.dyobj,"hp",self.hp)
    cppSetAttribute(self.dyobj,"mana",self.mana)
    cppSetAttribute(self.dyobj,"sp",self.sp)
    cppSetAttribute(self.dyobj,"spCap",self.spCap)
    cppSetAttribute(self.dyobj,"physicDmg",self.physicDmg)
    cppSetAttribute(self.dyobj,"physicDef",self.physicDef)
    cppSetAttribute(self.dyobj,"magicDmg",self.magicDmg)
    cppSetAttribute(self.dyobj,"magicDef",self.magicDef)
    cppSetAttribute(self.dyobj,"accurate",self.accurate)
    cppSetAttribute(self.dyobj,"evadeChance",self.evadeChance)
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


