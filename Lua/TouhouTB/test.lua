print("Test run started")
package.path = package.path .. ';../../Lua/TouhouTB/characters/?.lua;' .. ';../../Lua/?.lua;' .. './TouhouTB/characters/Common/?.lua;' .. './TouhouTB/characters/Patchy/?.lua;' .. ';../../Lua/TouhouTB/characters/Patchy/?.lua;' .. ';./TouhouTB/characters/Reimu/slots/?.lua;' .. ';../../Lua/TouhouTB/characters/Reimu/?.lua;' .. ';./TouhouTB/characters/Yukari/slots/?.lua;' .. ';../../Lua/TouhouTB/characters/Yukari/?.lua;' .. ';../../Lua/TouhouTB/?.lua' .. ';../../Lua/TouhouTB/characters/Meiling/?.lua;'

-- gui include
require "IconGui"

require "slotHandler"

-- characters include
require "Reimu"
require "Patchouli"
require "Yukari"
require "turnHandler"
require "Meiling"

local characters = {}
local turns = {}
mainGame = {}
local entityTasks = {}

T_guiIcons = nil

T_turnHandler = nil

tasks = {}

T_slotHandler = nil;

T_phase = 1
T_side = 3

---@Description : Set the gameplay phase
---@param host pointer instance of BattleScene
---@param tPhase number |1 select skills/item phase |2 select targets
---@param tSide number |1 left side |2 right side
function SetPhase(host,tPhase, tSide)
    T_phase = tPhase
    T_side = tSide
    if T_phase == 1 then --handle skill/item selection
        TB_GuiHandlerSetFocusColor(host,255,255,255,255)
        TB_SetSlothandlerActive(T_slotHandler.handlerObject,false)
    end
    if T_phase == 2 then --handle target selection
        TB_GuiHandlerSetFocusColor(host,0,255,0,255)
        T_slotHandler:setTotalSelectedCount(T_guiIcons:getCurrentTTD().requiredSlotCount)
        TB_SetSlothandlerActive(T_slotHandler.handlerObject,true)
    end
end

function init(host)

    -- Init GUI
    ---@diagnostic disable-next-line --- Too lazy to define wrapper
    cppSetDescriptionBoxPos(host,300,-355);
    ---@diagnostic disable-next-line
    cppSetDescriptionBoxDim(host,600,180);

    -- init random seed
    math.randomseed(114514)

    T_turnHandler = TurnHandler:new()
    T_slotHandler = SlotHandler:new()

    T_slotHandler:init(host,3,3,T_turnHandler)

    -- init characters
    -- Patchouli, left
    local p1 = Patchouli:new()
    p1:init(host,T_slotHandler:getSlot(1,1,1),1)
    p1:loadCommon(host)
    p1:loadSkills(host)

    -- Yukari, left
    local p2 = Reimu:new()
    p2:init(host,T_slotHandler:getSlot(1,2,1),1)
    p2:loadCommon(host)
    p2:loadSkills(host)

    -- Reimu, left
    local p3 = Yukari:new()
    p3:init(host,T_slotHandler:getSlot(1,3,1),1)
    p3:loadCommon(host)
    p3:loadSkills(host)

    -- Reimu, right
    local p2a = Reimu:new()
    p2a:init(host,T_slotHandler:getSlot(1,2,2),2)
    p2a:loadCommon(host)
    p2a:loadSkills(host)

    -- Yukari, right
    local p3a = Yukari:new()
    p3a:init(host,T_slotHandler:getSlot(2,3,2),2)
    p3a:loadCommon(host)
    p3a:loadSkills(host)
    
    local p4a = Meiling:new()
    p4a:init(host,T_slotHandler:getSlot(2,2,2),2)
    p4a:loadCommon(host)
    p4a:loadSkills(host)

    T_turnHandler:addCharacter(p1)
    T_turnHandler:addCharacter(p2)
    T_turnHandler:addCharacter(p3)

    T_turnHandler:addCharacter(p2a)
    T_turnHandler:addCharacter(p3a)
    T_turnHandler:addCharacter(p4a)

    T_guiIcons = IconGUI:new()
    T_guiIcons:init(host)

    -- start the main game loop
    ---@diagnostic disable-next-line: redundant-parameter
    mainGame["main"] = {behavior = coroutine.create(TBgameLoop,host)} 
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
    if T_phase == 1 then
        T_guiIcons:onSignal(host,signal)
        return
    end
    if T_phase == 2 then
        if signal == 64 then
            SetPhase(host,1,3)
            T_guiIcons:getCurrentTTD():onCancel(host,T_turnHandler:getCurrentCharacter())
        end
        T_slotHandler:onSignal(host,signal,T_guiIcons:getCurrentTTD().selectionSide,T_guiIcons:getCurrentTTD().slotFlag)

    end
end

function Battle_HandleMouse(host,x,y,button)
    if button == 1 then
        print("left click")
    elseif button == 2 then
        print("right click")
    end

    if T_phase == 1 then
        T_guiIcons:onMouseMove(host,x,y,button)
    end
    if T_phase == 2 then
        if button == 2 then -- right click 
            SetPhase(host,1,3)
            T_guiIcons:getCurrentTTD():onCancel(host,T_turnHandler:getCurrentCharacter())
            T_slotHandler.currentSlot = nil
            return
        end

        T_slotHandler:onMouseMove(host,x,y,button,T_guiIcons:getCurrentTTD().selectionSide,T_guiIcons:getCurrentTTD().slotFlag)
        if button == 2 then
            SetPhase(host,1,3)
        end
    end
end

function TBgameLoop(host)
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
            TB_SelectHoverSlot(T_slotHandler.handlerObject, T_turnHandler:getCurrentCharacter().currentSlot)
            print("select hover done")
            T_guiIcons:loadIcons(host,T_turnHandler:getCurrentCharacter())
            print("load icons done")
            coroutine.yield()
            T_turnHandler:nextTurn()
        end

        print("all of turns are done, reseting !!!!!!!!!!!!!!!!!!!!!!!!!!!")

    end
end





