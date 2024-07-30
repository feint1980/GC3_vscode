print("Helloooooo ")

local dynamics = {}

local slots = {}



-- function init(host)
--     for i = 1, 3 do
--         for j = 1, 3 do
--             print(i .. " " .. j)
--             cppCreateSlot(host, i, j,1)
--         end
--     end
-- end

function init(host)
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
end

