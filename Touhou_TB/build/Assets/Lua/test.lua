print("Helloooooo ")
characterPack = require("./Assets/Lua/Patchy.lua")
local characters = {}

local slots = {}



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
   
end


