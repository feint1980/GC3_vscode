package.path = package.path .. ';./Assets/lua/Icons/?.lua;'

require "Icon"

---@type SlotHandler
T_slotHandler = _G["T_slotHandler"]

---@type INPUT_type
T_CurrentInputType = _G["T_CurrentInputType"]

---@class Move: Icon

---@Description Move inherits from Icon
---@return Move
Move = Icon:new({
    asset = "./Assets/TB_GUI/move.png",
    name = "Move",
    description = "Move character to selected position",
    turnCost = 0.5,
    manaCost = 0,
    iconObj = nil,
    dyobj = nil,
    specialID = 1,
    selectedFunct = function() Move:selected(Move.host,Move.dyobj) end,
    funct = function() print("move") end,
    ---@type pointer instance of BattleScene
    host = nil,
    selectionSide = 1,
    index = 1,
    requiredSlotCount = 1,
    slotFlag = 1, --  0 = none, 1 = empty only,2 = has character in slot
    charName = "None",
    turnCostStr = "turn per<i><color=#00ff1d>1 </color></i>distance",
    manaCostStr = ""
})

---@type SlotHandler
---T_slotHandler

---@Description: Set the function to be called when the icon is selected/clicked
---@param host pointer instance of BattleScene
---@param dyobj pointer instance of F_Lua_BaseEntity
function Move:selected(host,dyobj)
    print("move selected called")
    SetPhase(host,2,1) -- move selected, now switch to select target

    if T_CurrentInputType == INPUT_type.Keyboard then 
        T_slotHandler:onSignal(host,2,self.selectionSide,self.slotFlag)
    end

end

function MoveToSlotBehavior(host, dyobj)

    print("moveToSlotBehavior called" )
    --- basics procedure, get all slot first
    local slots = T_slotHandler:getSelectedSlots()

    -- check if there is only only the slot you need
    local count =  tablelength(slots)
    print("slot count " .. count)
    if count ~= Move.requiredSlotCount then
        print("wrong number of slots selected")
        return --- avoid strange behavior 
    end
    
    local slot = slots[1] -- target what you need
    
    local currentSlot = cppGetEntitySlot(dyobj)
    print("ok ")
    local currentCol = cppGetSlotCol(currentSlot)
    print("current col " .. currentCol)
    if(slot ~= nil) then
        print("slot not nil")
    else
        print("slot is nil")
    end
    local targetCol = cppGetSlotCol(slot)
    local dashAnimation = "dash_fw"
    if currentCol < targetCol then
        dashAnimation = "dash_bw"
    end

    local currentRow = cppGetSlotRow(currentSlot)
    local targetRow = cppGetSlotRow(slot)


    local result = math.abs(currentRow - targetRow) + math.abs(currentCol - targetCol)

    cppEntityPlayAnimation(host,dyobj,dashAnimation,false,-1)
    cppEntityMoveToslot(host,dyobj,slot,result * 25)
    coroutine.yield()

    finishedAnimation = dashAnimation .. "_end"
    cppEntityPlayAnimation(host,dyobj,finishedAnimation,true,1)
    coroutine.yield()
    cppEntityPlayAnimation(host,dyobj,"idle",false,-1)
    coroutine.yield()
    -- cppClearEntityTasks(host,dyobj)
    -- coroutine.yield()

end


function Move:useFunction(host,character)
    print("MOVE CALLED ")

    if(host == nil) then
        print("host is nil")
        return
    end

    if character.dyobj == nil then
        print("move character.dyobj is nil")
        return
    end

    tasks[character.dyobj] = {behavior = coroutine.create(MoveToSlotBehavior,host,character.dyobj)}
    HandleSkillTasks(host,character.dyobj)
    SetPhase(host,1,3)

    print("!!!! set slot start ")
    slots = T_slotHandler:getSelectedSlots()

    count =  tablelength(slots)
    print("slot count " .. count)
    print("testttt ")
    if count ~= 1 then
        print("wrong number of slots selected")
        return
    end
    --slot = slots[1]
    print("reach here 5 ")
    --count = 1
    --tempSlots = {}
    for k,v in pairs(slots) do
        slot = v
    end
    print("reach here ")
    character.currentSlot = slot
    slot:setDyobj(character.dyobj)
    print("!!!! set slot end ")


    print("MOVE CALLED END")
end


function Move:onCancel(host,character)
    print("onCancel Move called")
    -- todo : inherits and override
end