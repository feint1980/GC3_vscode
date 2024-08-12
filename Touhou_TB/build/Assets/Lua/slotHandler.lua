package.path = package.path .. ';./Assets/Lua/slots/?.lua;'


require "Slot"

leftSlots  = {}          -- create the matrix
rightSlots = {}          -- create the matrix


SlotHandler = {

    host = nil,
    leftSlots = {},
    rightSlots = {},
    selectedSlots = {}
}


function SlotHandler:init(host,row,col)
    leftSlots  = {}          -- create the matrix
    rightSlots = {}          -- create the matrix

    self.host = host

    for i=1,row do
        leftSlots[i] = {}     -- create a new row
        for j=1,col do
            leftSlots[i][j] = cppCreateSlot(host,i,j,1)
        end
    end

    for i=1,row do
        rightSlots[i] = {}     -- create a new row
        for j=1,col do
            rightSlots[i][j] = cppCreateSlot(host,i,j,2)
        end
    end
end

function SlotHandler:getSlot(tRow,tCol,tSide)
    if tSide == 1 then
        return leftSlots[tRow][tCol]
    elseif tSide == 2 then
        return rightSlots[tRow][tCol]
    end
end