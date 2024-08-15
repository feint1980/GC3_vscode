print("Helloooooo ")
package.path = package.path .. ';./Assets/Lua/characters/?.lua;' .. ';./Assets/Lua/?.lua;' .. './characters/Common/?.lua;' .. './characters/Patchy/?.lua;' .. ';./Assets/Lua/characters/Patchy/?.lua;'

-- gui include
require "IconGui"

require "slotHandler"

-- characters include
require "Patchy"

require "Patchouli"


local characters = {}

local turns = {}

local mainGame = {}

local entityTasks = {}

local t_guiIcons = nil

tasks = {}

t_slotHandler = nil;

phase = 1
side = 3

selectedSlot = nil
selectedChar = nil

function setPhase(host,tPhase, tSide)
    phase = tPhase
    side = tSide
    if phase == 1 then
        cppGuiHandlerSetFocusColor(host,255,255,255,255)
        cppSetSlothandlerActive(t_slotHandler.handlerObject,false)
    end
    if phase == 2 then
        cppGuiHandlerSetFocusColor(host,0,255,0,255)
        t_slotHandler:setSelectedCount(t_guiIcons:getCurrentTTD().requiredSlotCount)
        cppSetSlothandlerActive(t_slotHandler.handlerObject,true)
    end
end

function init(host)
    -- init slots
    -- leftSlots = {}          -- create the matrix
    -- for i=1,3 do
    --     leftSlots[i] = {}     -- create a new row
    --     for j=1,3 do
    --         leftSlots[i][j] = cppCreateSlot(host, i, j,1)
    --     end
    -- end
    -- rightSlots = {}          -- create the matrix
    -- for i=1,3 do
    --     rightSlots[i] = {}     -- create a new row
    --     for j=1,3 do
    --         rightSlots[i][j] = cppCreateSlot(host, i, j,2)
    --     end
    -- end

    t_slotHandler = SlotHandler
    t_slotHandler:init(host,3,3)
   
    -- init characters
 

    characters["pat"] = Patchy:new()
    characters["pat"]:init(host,t_slotHandler:getSlot(1,2,1))
    characters["pat"]:loadCommon(host)

    characters["p1"] = Patchouli:new()
    characters["p1"]:init(host,t_slotHandler:getSlot(3,3,1))
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
        return
    end
    if phase == 2 then
        if signal == 64 then
            setPhase(host,1,3)
        end
      
        t_slotHandler:onSignal(host,signal,t_guiIcons:getCurrentTTD().selectionSide)
        if signal == 32 then
            if t_slotHandler:getCurrentCount() == t_guiIcons:getCurrentTTD().requiredSlotCount then
                t_guiIcons:getCurrentTTD():funct()
            end
        end
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
    totalTurn = tablelength(turns) 
    print("totalTurn " .. totalTurn)
    sortCharactersTurn()
    i = 2
    --while gameOn do
      
            -- do something
        currentChar = turns[i]
        print("chracter " .. turns[i].name .. "turn " )
      
        cppSelectHoverSlot(t_slotHandler.handlerObject,currentChar.currentSlot)

        --cppPickActiveEntity(host,currentChar.dyobj)
        t_guiIcons:loadIcons(host,turns[i])
        --coroutine.yield()
        --i = i + 1
        print("turn " .. currentChar.name .. " ended")
        --turns = table.remove(turns,1)

        print("end")
    --end
end





