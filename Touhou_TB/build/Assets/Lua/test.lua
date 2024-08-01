print("Helloooooo ")
package.path = package.path .. ';./Assets/lua/?.lua;'
require "Patchy"
local characters = {}

local turns = {}

local mainGame = {}


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
    IssueNextTask(host)
end


function IssueNextTask(host)
    if coroutine.status(mainGame["main"].behavior) ~= 'dead' then
		coroutine.resume(mainGame["main"].behavior, host)
	else
		print(coroutine.status(mainGame["main"].behavior))
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


function gameLoop(host)
    local gameOn = true
    while gameOn do
        sortCharactersTurn()
        
        for i = 1, #turns do
            -- do something
            print("chracter " .. turns[i].Strength .. "turn " )
            cppPickActiveEntity(host,turns[i].dyobj)
            coroutine.yield()
            
        end
    end
end

