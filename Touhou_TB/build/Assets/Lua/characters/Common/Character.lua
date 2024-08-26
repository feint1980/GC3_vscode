package.path = package.path .. ';./Assets/lua/Icons/?.lua;'
require "Move"
require "End"

Character = {

    Strength = 5,
    Vitality = 5,
    Dexterity = 5,
    Agility = 5,
    Intelligence = 5,
    Wisdom = 5,

    dyobj = nil,
    animationPath = "./Assets/F_AObjects/patchouli_tb.xml",
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

function Character:init(host,slot)

    self.dyobj = cppCreateEnity(host,self.animationPath,slot)
    self.currentSlot = slot
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

