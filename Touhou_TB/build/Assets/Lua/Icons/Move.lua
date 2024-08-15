package.path = package.path .. ';./Assets/lua/Icons/?.lua;'

require "Icon"

Move = Icon:new({
    asset = "./Assets/TB_GUI/move.png",
    name = "Move",
    description = "baseIcon",
    turnCost = 0.5,
    iconObj = nil,
    dyobj = nil,
    specialID = 1,
    selectedFunct = function() Move:selected() end,
    funct = function() Move:move(host, dyobj,charName) end,
    host = nil,
    selectionSide = 1,
    index = 1,
    requiredSlotCount = 1,
    charName = "None"
})



function Move:selected()
    print("move selected called")
    setPhase(self.host,2,1)

    -- todo, make the host now able to select the slot to move
end


function moveToSlotBehavior(host, dyobj,charName)


    print("moveToSlotBehavior called" .. charName)
    slots = t_slotHandler:getSelectedSlots()

    count =  tablelength(slots)
    print("slot count " .. count)

    if count ~= 1 then
        print("wrong number of slots selected")
        return
    end
    --slot = slots[1]

    --count = 1
    --tempSlots = {}
    for k,v in pairs(slots) do
        slot = v
    end
    
    currentSlot = cppGetEntitySlot(dyobj)
    print("ok ")
    currentCol = cppGetSlotCol(currentSlot)
    print("current col " .. currentCol)
    if(slot ~= nil) then
        print("slot not nil")
    else 
        print("slot is nil")
    end
    targetCol = cppGetSlotCol(slot)
    dashAnimation = "dash_fw"
    if currentCol < targetCol then
        dashAnimation = "dash_bw"
    end

    cppEntityPlayAnimation(host,dyobj,dashAnimation,-1)
    cppEntityMoveToslot(host,dyobj,slot,50)
    coroutine.yield()

    finishedAnimation = dashAnimation .. "_end"
    cppEntityPlayAnimation(host,dyobj,finishedAnimation,1)
    coroutine.yield()
    cppEntityPlayAnimation(host,dyobj,"idle",-1)
    coroutine.yield()
end

function Move:move(host,dyobj,charName)
    -- count =  tablelength(selectedSlots)
    -- if count ~= 1 then
    --     print("wrong number of slots selected")
    --     return
    -- end
    --slot = selectedSlots[1]
    print("MOVE CALLED ")
    print("charName " .. charName)


    tasks[charName] = {behavior = coroutine.create(moveToSlotBehavior,host,dyobj,charName)}
    HandleSkillTasks(host,dyobj,charName)

    print("MOVE CALLED END")
  
end


