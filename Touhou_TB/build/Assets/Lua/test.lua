print("Helloooooo ")
package.path = package.path .. ';./Assets/Lua/characters/?.lua;' .. ';./Assets/Lua/?.lua;' .. './characters/Common/?.lua;' .. './characters/Patchy/?.lua;' .. ';./Assets/Lua/characters/Patchy/?.lua;' .. ';./characters/Reimu/slots/?.lua;' .. ';./Assets/Lua/characters/Reimu/?.lua;' .. ';./characters/Yukari/slots/?.lua;' .. ';./Assets/Lua/characters/Yukari/?.lua;'

-- gui include
require "IconGui"

require "slotHandler"

-- characters include
require "Reimu"

require "Patchouli"

require "Yukari"

require "turnHandler"




local characters = {}

local turns = {}

mainGame = {}

local entityTasks = {}

t_guiIcons = nil

t_turnHandler = nil

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


    cppSetDescriptionBoxPos(host,300,-355);
    cppSetDescriptionBoxDim(host,600,180);

    t_turnHandler = TurnHandler:new()
    t_slotHandler = SlotHandler:new()
    t_slotHandler:init(host,3,3,t_turnHandler)


    -- init characters


    -- characters["pat"] = Patchy:new()
    -- characters["pat"]:init(host,t_slotHandler:getSlot(1,2,1))
    -- characters["pat"]:loadCommon(host)

    p1 = Patchouli:new()
    p1:init(host,t_slotHandler:getSlot(3,3,1),1)
    p1:loadCommon(host)
    --t_slotHandler:getSlot(3,3,1):setDyobj(p1)


    p2 = Reimu:new()
    p2:init(host,t_slotHandler:getSlot(2,2,1),1)
    p2:loadCommon(host)
    p2:loadSkills(host)
    --t_slotHandler:getSlot(2,2,1):setDyobj(p2)

    p3 = Yukari:new()
    p3:init(host,t_slotHandler:getSlot(1,3,1),1)
    p3:loadCommon(host)


    p2a = Reimu:new()
    p2a:init(host,t_slotHandler:getSlot(1,2,2),2)
    p2a:loadCommon(host)
    p2a:loadSkills(host)
    --t_slotHandler:getSlot(2,2,1):setDyobj(p2)

    p3a = Yukari:new()
    p3a:init(host,t_slotHandler:getSlot(2,3,2),2)
    p3a:loadCommon(host)


    t_turnHandler:addCharacter(p1)
    t_turnHandler:addCharacter(p2)
    t_turnHandler:addCharacter(p3)

    t_turnHandler:addCharacter(p2a)
    t_turnHandler:addCharacter(p3a)


    t_guiIcons = IconGUI:new()
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
            t_guiIcons:getCurrentTTD():onCancel(host,t_turnHandler:getCurrentCharacter().dyobj)
        end
      
        t_slotHandler:onSignal(host,signal,t_guiIcons:getCurrentTTD().selectionSide,t_guiIcons:getCurrentTTD().slotFlag)
        if signal == 32 then
            if t_slotHandler:getCurrentCount() == t_guiIcons:getCurrentTTD().requiredSlotCount then
                if selectedChar ~= nil then
                    print(selectedChar.name .. " selected")
                    t_guiIcons:getCurrentTTD():funct(host,selectedChar.dyobj,selectedChar.name)
                else
                    print("no character selected")
                end -- if selectedChar ~= nil
                --t_guiIcons:getCurrentTTD():funct(host,selectedChar.dyobj,selectedChar.name)
            end -- if t_slotHandler:getCurrentCount() == t_guiIcons:getCurrentTTD().requiredSlotCount
        end -- if signal == 32
    end
end

function handleMouse(host,x,y,button)
    if phase == 1 then
        t_guiIcons:onMouseMove(host,x,y,button)
    end
    if phase == 2 then
        t_slotHandler:onMouseMove(host,x,y,button,t_guiIcons:getCurrentTTD().selectionSide,t_guiIcons:getCurrentTTD().slotFlag)
        if button == 2 then
            setPhase(host,1,3)
        end
    end
end

function gameLoop(host)
    local gameOn = true
    -- totalTurn = tablelength(turns) 
    -- print("totalTurn " .. totalTurn)
    -- sortCharactersTurn()
    -- i = 1
    while gameOn do
      

        print("restarting turns")
        t_turnHandler:putCharacterIntoList()
        print("sort turn OK ")

        for i = 1, #t_turnHandler:getActiveList() do 
            print("character " .. t_turnHandler:getCurrentCharacter().name)
            print("yielding !!!!!!!!!")
            cppSelectHoverSlot(t_slotHandler.handlerObject, t_turnHandler:getCurrentCharacter().currentSlot)
            print("select hover done")
            t_guiIcons:loadIcons(host,t_turnHandler:getCurrentCharacter())
            print("load icons done")
            coroutine.yield()
            t_turnHandler:nextTurn()
        end

        print("all of turns are done, reseting !!!!!!!!!!!!!!!!!!!!!!!!!!!")
        -- Old code
            -- do something
        --for i = 1,totalTurn do
            -- selectedChar = turns[i]
            -- --currentChar = turns[i] 
            -- print("chracter " .. turns[i].name .. "turn " )
        
            -- cppSelectHoverSlot(t_slotHandler.handlerObject,selectedChar.currentSlot)
           
            -- --cppPickActiveEntity(host,currentChar.dyobj)
            -- t_guiIcons:loadIcons(host,selectedChar)
           
            -- coroutine.yield()
            
            --coroutine.yield()
            -- i = i + 1
            -- print("turn " .. currentChar.name .. " ended")
            -- --turns = table.remove(turns,1)
            -- print("end")

       -- end
    end
end





