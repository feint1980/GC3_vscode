package.path = package.path .. ';./Assets/lua/Icons/?.lua;'

require "Icon"

Move = Icon:new({
    asset = "./Assets/TB_GUI/move.png",
    name = "Move",
    description = "Move character to selected position",
    turnCost = 0.5,
    manaCost = 0,
    iconObj = nil,
    dyobj = nil,
    specialID = 1,
    selectedFunct = function() Move:selected() end,
    funct = function() move(host, dyobj) end,
    host = nil,
    selectionSide = 1,
    index = 1,
    requiredSlotCount = 1,
    slotFlag = 1, --  0 = none, 1 = empty only,2 = has character in slot
    charName = "None",
    turnCostStr = "turn per<i><color=#00ff1d>1 </color></i>distance",
    manaCostStr = ""
})


function Move:selected(host,dyobj)
    print("move selected called")
    setPhase(host,2,1)
    --local tSignal = 2 
    --if se
    t_slotHandler:onSignal(host,2,self.selectionSide,self.slotFlag)
    -- todo, make the host now able to select the slot to move
end


function moveToSlotBehavior(host, dyobj)


    print("moveToSlotBehavior called" )
    local slots = t_slotHandler:getSelectedSlots()

    local count =  tablelength(slots)
    print("slot count " .. count)
    if count ~= 1 then
        print("wrong number of slots selected")
        return
    end
    local slot = slots[1]
    
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

    tasks[character.dyobj] = {behavior = coroutine.create(moveToSlotBehavior,host,character.dyobj)}
    HandleSkillTasks(host,character.dyobj)
    setPhase(host,1,3)

    print("!!!! set slot start ")
    slots = t_slotHandler:getSelectedSlots()

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