print("Helloooooo ")
package.path = package.path .. ';./Assets/Lua/characters/?.lua;' .. ';./Assets/Lua/?.lua;' .. './characters/Common/?.lua;' .. './characters/Patchy/?.lua;' .. ';./Assets/Lua/characters/Patchy/?.lua;'

-- gui include
require "IconGui"

-- characters include
require "Patchy"

require "Patchouli"


local characters = {}

local turns = {}

local mainGame = {}

local entityTasks = {}

local t_guiIcons = nil

phase = 1
side = 3

selectedSlot = nil
selectedChar = nil

function setPhase(host,tPhase, tSide)
    phase = tPhase
    side = tSide
    if phase == 1 then
        cppGuiHandlerSetFocusColor(host,255,255,255,255)
    end
    if phase == 2 then
        cppGuiHandlerSetFocusColor(host,0,255,0,255)
    end
end

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
    -- characters["pat"] = Patchy
    -- characters["pat"].init(characters["pat"],host,leftSlots[2][2])

    characters["p1"] = Patchouli:new()
    characters["p1"]:init(host,leftSlots[3][3])
    characters["p1"]:loadCommon(host)

    t_guiIcons = IconGUI
    t_guiIcons:init(host)
    --t_guiIcons:loadIcons(host,characters["p1"])

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
    cppEntityPlayAnimation(host,dyobj,finishedAnimation,1)
    coroutine.yield()
    cppEntityPlayAnimation(host,dyobj,"idle",-1)
    coroutine.yield()
end

function setEntityMoveToSlot(host,dyobj)
    entityTasks[dyobj] = {behavior = coroutine.create(moveToSlotBehavior,host,dyobj)}
    HandleMovingTask(host,dyobj)
end


function handleSlot(host,signal)
    -- if (side & 1) == 1 then
    --     print("handle slot left")
    -- end
    -- if (side & 2) == 2 then
    --     print("handle slot right")
    -- end

    if side == 1 then
        print ("handle slot left")
    end

end
function handleInput(host,signal)
    if phase == 1 then
        t_guiIcons:onSignal(host,signal)
    end
    if phase == 2 then
        if signal == 64 then
           setPhase(host,1,3)
        end
        handleSlot(host,signal)
    end
end

function handleMouse(host,x,y,button)
    if phase == 1 then
        t_guiIcons:onMouseMove(host,x,y,button)
    end
    if phase == 2 then
        if button == 2 then
            setPhase(host,1,3)
        end
    end
end


function gameLoop(host)
    local gameOn = true
    while gameOn do
        sortCharactersTurn()
        
        for i = 1, #turns do
            -- do something
            print("chracter " .. turns[i].Strength .. "turn " )
            currentChar = turns[i]
            cppPickActiveEntity(host,turns[i].dyobj)
            t_guiIcons:loadIcons(host,turns[i])
            coroutine.yield()
            table.remove(turns,1)
        end
        
        print("end")
    end
end



