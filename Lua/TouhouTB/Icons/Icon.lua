
---Skill/Item filter flag
SlotFlag = {
    None = 0,
    EmptyOnly = 1,
    HasCharacter = 2
}

---@class Icon
Icon = {

    asset = "./Assets/TB_GUI/missing.png",
    name = "Icon",
    description = "baseIcon",
    turnCost = 0.5,
    manaCost = 0,
    ---@type pointer instance of GUI_icon
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
    -- Why turn cost and mana cost also have strings?
    -- It use to further detail the turn cost or mana cost (sth sth per turn/mana)
    -- default will be display the turnCost/manaCost 
}


---@Descriptiopn Creates a new Icon
---@param o table Icon The Icon to create
function Icon:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

---@Description: Initialize the Icon
---@param host pointer instance of BattleScene
---@param dyobj pointer instance of F_Lua_BaseEntity 
---@param tCharacter Character instance of character 
function Icon:init(host,dyobj,tCharacter)
    --self.iconObj = 
    print("icon init")
    self.iconObj = TB_CreateIcon(host,self.asset,64,64,self.name,
    self.description,self.turnCost,self.manaCost,self.turnCostStr,
    self.manaCostStr, self.specialID)
    self.host = host
    self.dyobj = dyobj
    self.character = tCharacter
end

function tablelength(T)
    local count = 0
    for _ in pairs(T) do count = count + 1 end
    return count
end

---@Description: Get the position of the Icon
---@return vec2 position
function Icon:getPos()
    return TB_GetIconPos(self.iconObj)
end

---@Description: Set the function to be called when the icon is selected/clicked
---@param funct function The function to be called
function Icon:setFunct(funct)
    self.funct = funct
end

---@Desciption : Handle coroutine
---@param host pointer instance of BattleScene
---@param dyobj pointer instance of F_Lua_BaseEntity
function HandleSkillTasks(host,dyobj)
    print("HandleSkillTasks called")
    if coroutine.status(tasks[dyobj].behavior) ~= 'dead' or coroutine.status(tasks[dyobj].behavior) ~= 'suspended' then
        coroutine.resume(tasks[dyobj].behavior, host, dyobj)
    else
        print(coroutine.status(tasks[dyobj].behavior))
    end
end

---@Description: Use the function of the icon
---@param host pointer instance of BattleScene
---@param character Character instance of character
function Icon:useFunction(host,character)
    -- todo : inherits and override 
end

---@Description: Use the function of the icon
---@param host pointer instance of BattleScene
---@param character Character instance of character
function Icon:selected(host, character)
    -- todo : inherits and override
end 

---@Description: On cancel
---@param host pointer instance of BattleScene
---@param character Character instance of character
function Icon:onCancel(host,character)
    print("onCancel base called")
    -- todo : inherits and override
end