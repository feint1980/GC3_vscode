print("Test run started")
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

T_guiIcons = nil

T_turnHandler = nil

tasks = {}

T_slotHandler = nil;

phase = 1
side = 3

selectedSlot = nil
selectedChar = nil

function setPhase(host,tPhase, tSide)
    phase = tPhase
    side = tSide
    if phase == 1 then
        cppGuiHandlerSetFocusColor(host,255,255,255,255)
        cppSetSlothandlerActive(T_slotHandler.handlerObject,false)
    end
    if phase == 2 then
        cppGuiHandlerSetFocusColor(host,0,255,0,255)
        T_slotHandler:setTotalSelectedCount(T_guiIcons:getCurrentTTD().requiredSlotCount)
        cppSetSlothandlerActive(T_slotHandler.handlerObject,true)
    end
end

function init(host)


    -- Init GUI
    cppSetDescriptionBoxPos(host,300,-355);
    cppSetDescriptionBoxDim(host,600,180);

    -- init random seed
    math.randomseed(114514)

    -- 
    T_turnHandler = TurnHandler:new()
    T_slotHandler = SlotHandler:new()


    T_slotHandler:init(host,3,3,T_turnHandler)

    -- init characters
    -- Patchouli, left
    local p1 = Patchouli:new()

    p1:init(host,T_slotHandler:getSlot(1,1,1),1)
    p1:loadCommon(host)

    -- Yukari, left
    local p2 = Reimu:new()
    p2:init(host,T_slotHandler:getSlot(1,2,1),1)
    p2:loadCommon(host)
    p2:loadSkills(host)

    -- Reimu, left
    local p3 = Yukari:new()
    p3:init(host,T_slotHandler:getSlot(1,3,1),1)
    p3:loadCommon(host)

    -- Reimu, right
    local p2a = Reimu:new()
    p2a:init(host,T_slotHandler:getSlot(1,2,2),2)
    p2a:loadCommon(host)
    p2a:loadSkills(host)

    -- Yukari, right
    local p3a = Yukari:new()
    p3a:init(host,T_slotHandler:getSlot(2,3,2),2)
    p3a:loadCommon(host)

    T_turnHandler:addCharacter(p1)
    T_turnHandler:addCharacter(p2)
    T_turnHandler:addCharacter(p3)

    T_turnHandler:addCharacter(p2a)
    T_turnHandler:addCharacter(p3a)

    T_guiIcons = IconGUI:new()
    T_guiIcons:init(host)
    --T_guiIcons:loadIcons(host,characters["p1"])

    -- start the main game loop
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


function Battle_HandleInput(host,signal)
    if phase == 1 then
        T_guiIcons:onSignal(host,signal)
        return
    end
    if phase == 2 then
        if signal == 64 then
            setPhase(host,1,3)
            T_guiIcons:getCurrentTTD():onCancel(host,T_turnHandler:getCurrentCharacter())
        end
        T_slotHandler:onSignal(host,signal,T_guiIcons:getCurrentTTD().selectionSide,T_guiIcons:getCurrentTTD().slotFlag)
        if signal == 32 then
            if T_slotHandler:getCurrentCount() == T_guiIcons:getCurrentTTD().requiredSlotCount then
                if selectedChar ~= nil then
                    print(selectedChar.name .. " selected")
                    T_guiIcons:getCurrentTTD():funct(host,selectedChar.dyobj,selectedChar.name)
                else
                    print("no character selected")
                end -- if selectedChar ~= nil
                --T_guiIcons:getCurrentTTD():funct(host,selectedChar.dyobj,selectedChar.name)
            end -- if T_slotHandler:getCurrentCount() == T_guiIcons:getCurrentTTD().requiredSlotCount
        end -- if signal == 32
    end
end

function Battle_HandleMouse(host,x,y,button)
    if button == 1 then
        print("left click")
    elseif button == 2 then
        print("right click")
    end
    
    if phase == 1 then
        T_guiIcons:onMouseMove(host,x,y,button)
    end
    if phase == 2 then
        T_slotHandler:onMouseMove(host,x,y,button,T_guiIcons:getCurrentTTD().selectionSide,T_guiIcons:getCurrentTTD().slotFlag)
        if button == 2 then
            setPhase(host,1,3)
        end
    end
end

function gameLoop(host)
    local gameOn = true
    -- totalTurn = tablelength(turns) 
    -- print("totalTurn " .. totalTurn)
    -- i = 1
    while gameOn do
        print("restarting turns")
        T_turnHandler:putCharacterIntoList()
        print("sort turn OK ")

        for i = 1, #T_turnHandler:getActiveList() do 
            print("character " .. T_turnHandler:getCurrentCharacter().name)
            print("yielding !!!!!!!!!")
            cppSelectHoverSlot(T_slotHandler.handlerObject, T_turnHandler:getCurrentCharacter().currentSlot)
            print("select hover done")
            T_guiIcons:loadIcons(host,T_turnHandler:getCurrentCharacter())
            print("load icons done")
            coroutine.yield()
            T_turnHandler:nextTurn()
        end

        print("all of turns are done, reseting !!!!!!!!!!!!!!!!!!!!!!!!!!!")

    end
end





