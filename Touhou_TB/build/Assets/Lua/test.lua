print("Helloooooo ")
package.path = package.path .. ';./Assets/lua/?.lua;'
require "Patchy"
local characters = {}

local turns = {}

local mainGame = {}

local entityTasks = {}


function init(host)
    -- init slots
    leftSlots = {}          -- create the matrix
    for i=1,3 do
        leftSlots[i] = {}     -- create a new row
        for j=1,3 do
            leftSlots[i][j] = cppCreateSlot(host, i, j,1)
        end
    end
    rightSlots = {}          -- create the matrix
    for i=1,3 do
        rightSlots[i] = {}     -- create a new row
        for j=1,3 do
            rightSlots[i][j] = cppCreateSlot(host, i, j,2)
        end
    end
    -- init characters
    characters["pat"] = Patchy
    characters["pat"].init(characters["pat"],host,leftSlots[3][2])
    mainGame["main"] = {behavior = coroutine.create(gameLoop,host)} 
    IssueNextPhase(host)
end


function IssueNextPhase(host)
    if coroutine.status(mainGame["main"].behavior) ~= 'dead' then
		coroutine.resume(mainGame["main"].behavior, host)
	else
		print(coroutine.status(mainGame["main"].behavior))
	end
end

function HandleMovingTask(host,dynob,slot)
    if coroutine.status(entityTasks[dynob].behavior) ~= 'dead' then
        coroutine.resume(entityTasks[dynob].behavior, host, dynob)
    else
        print(coroutine.status(entityTasks[dynob].behavior))
    end
end


function sortCharactersTurn()
    print("sort turn started")
    -- empty the list
    turns = {}
    for k,v in pairs(characters) do
        -- insert character on the list based on Dexterity 
        table.insert(turns, v)
    end

    -- sort the list
    table.sort(turns, function(a,b) return a.Dexterity > b.Dexterity end)

    print("sort turn ended")
end

function moveToSlotBehavior(host,dyobj)
    -- cppEntityPlayAnimation(host,dyobj,"dash_fw",-1)
    -- coroutine.yield()
    -- print("called 2")
    slot = cppEntityGetTargetSlot(dyobj)
    currentSlot = cppGetEntitySlot(dyobj)
    print("ok ")
    currentCol = cppGetSlotCol(currentSlot)
    print("current col " .. currentCol)
    targetCol = cppGetSlotCol(slot)
    dashAnimation = "dash_fw"
    if currentCol < targetCol then
        dashAnimation = "dash_bw"
    end

    cppEntityPlayAnimation(host,dyobj,dashAnimation,-1)
    cppEntityMoveToslot(host,dyobj,slot,50)
    coroutine.yield()

    finishedAnimation = dashAnimation .. "_end"
    cppEntityPlayAnimation(host,dyobj,finishedAnimation,1,18)
    coroutine.yield()
    cppEntityPlayAnimation(host,dyobj,"idle",-1)
    coroutine.yield()
end

function setEntityMoveToSlot(host,dyobj)
    entityTasks[dyobj] = {behavior = coroutine.create(moveToSlotBehavior,host,dyobj)}
    HandleMovingTask(host,dyobj)
end


function gameLoop(host)
    local gameOn = true
    while gameOn do
        sortCharactersTurn()
        
        for i = 1, #turns do
            -- do something
            print("chracter " .. turns[i].Strength .. "turn " )
            cppPickActiveEntity(host,turns[i].dyobj)
            coroutine.yield()
            table.remove(turns,1)
        end
        print("end")
    end
end



