
Icon = {

    asset = "./Assets/TB_GUI/missing.png",
    name = "Icon",
    description = "baseIcon",
    turnCost = 0.5,
    manaCost = 0,
    iconObj = nil,
    dyobj = nil,
    specialID = 1,
    selectedFunct = nil,
    funct = nil,
    host = nil,
    selectionSide = 3,
    index = -1,
    requiredSlotCount = 1,
    slotFlag = 0, --  0 = none, 1=empty only, 2 has character in slot
    character = nil,
    turnCostStr = "",
    manaCostStr = ""
}


function Icon:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function Icon:init(host,dyobj,tCharacter)
    --self.iconObj = 
    print("icon init")
    self.iconObj =  cppCreateIcon(host,self.asset,64,64,self.name,self.description,self.turnCost,self.manaCost,self.turnCostStr,self.manaCostStr, self.specialID)
    self.host = host
    self.dyobj = dyobj
    self.character = tCharacter

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

function HandleSkillTasks(host,dyobj)
    print("HandleSkillTasks called")
    if coroutine.status(tasks[dyobj].behavior) ~= 'dead' then
        coroutine.resume(tasks[dyobj].behavior, host, dyobj)
    else
        print(coroutine.status(tasks[dyobj].behavior))
    end
end

function Icon:useFunction(host,dyobj)
    -- todo : inherits and override 
end

function Icon:onCancel(host,dyobj)
    print("onCancel base called")
    -- todo : inherits and override
end