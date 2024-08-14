
Icon = {

    asset = "./Assets/TB_GUI/missing.png",
    name = "Icon",
    description = "baseIcon",
    turnCost = 0.5,
    iconObj = nil,
    dyobj = nil,
    specialID = 1,
    selectedFunct = nil,
    funct = nil,
    host = nil,
    selectionSide = 3,
    index = -1,
    requiredSlotCount = 1
}

tasks = {}

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

function tablelength(T)
    local count = 0
    for _ in pairs(T) do count = count + 1 end
    return count
  end

function Icon:getPos()
    cppGetIconPos(self.iconObj)
end

function Icon:setFunct(funct)
    self.funct = funct
end

function HandleSkillTasks(host,dynob)
    if coroutine.status(tasks[dynob].behavior) ~= 'dead' then
        coroutine.resume(tasks[dynob].behavior, host, dynob)
    else
        print(coroutine.status(tasks[dynob].behavior))
    end
end