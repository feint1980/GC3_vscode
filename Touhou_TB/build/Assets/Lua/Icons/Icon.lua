
Icon = {

    asset = "./Assets/TB_GUI/missing.png",
    name = "Icon",
    description = "baseIcon",
    turnCost = 0.5,
    iconObj = nil,
    dyobj = nil,
    specialID = 1,
    funct = nil,
    host = nil,
    index = -1
    
}

function Icon:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function Icon:init(host,dyobj)
    --self.iconObj = 
    print("icon init")
    self.iconObj =  cppCreateIcon(host,self.asset,64,64,self.name,self.description,self.turnCost, self.specialID)
    self.host = host
    self.dyobj = dyobj

end

function Icon:setFunct(funct)
    self.funct = funct
end