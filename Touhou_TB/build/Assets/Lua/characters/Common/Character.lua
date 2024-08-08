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
    name = "None",
    lastName = "None",
    title = "None"

}

function Character:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function Character.init(self,host,slot)

    self.dyobj = cppCreateEnity(host,self.animationPath,slot)
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
    cppSetAttribute(self.dyobj,"name",self.name)
    cppSetAttribute(self.dyobj,"lastName",self.lastName)
    cppSetAttribute(self.dyobj,"title",self.title)


end