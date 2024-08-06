local tasks = {}

Patchy = { 
    Strength = 3,
    Vitality = 4,
    Dexterity = 5,
    Agility = 4,
    Intelligence = 22,
    Wisdom = 22,
    dyobj = nil,
    animationPath = "./Assets/F_AObjects/patchouli_tb.xml",
    action = 0
}

function Patchy.init(self,host,slot)
    
    self.dyobj = cppCreateEnity(host,self.animationPath,slot)
    cppSetAttribute(self.dyobj,"Strength",self.Strength)
    cppSetAttribute(self.dyobj,"Vitality",self.Vitality)
    cppSetAttribute(self.dyobj,"Dexterity",self.Dexterity)
    cppSetAttribute(self.dyobj,"Agility",self.Agility)
    cppSetAttribute(self.dyobj,"Intelligence",self.Intelligence)
    cppSetAttribute(self.dyobj,"Wisdom",self.Wisdom)
    self.action = 1 + self.Dexterity * 0.05

end


function Patchy.setMoveToSlot(slot)
    tasks[self.dyobj] = {behavior = coroutine.create(Patchy.moveToSlot,slot)}
    
end

function Patchy.moveToSlot(slot)
    cppMoveToSlot(self.dyobj,slot)

end