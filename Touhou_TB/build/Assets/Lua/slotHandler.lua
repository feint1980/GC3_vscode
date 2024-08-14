package.path = package.path .. ';./Assets/Lua/slots/?.lua;'


require "Slot"

leftSlots  = {}          -- create the matrix
rightSlots = {}          -- create the matrix


SlotHandler = {

    host = nil,
    leftSlots = {},
    rightSlots = {},
    selectedSlots = {},
    currentChar = nil,
    current_index_x = 1,
    current_index_y = 1,
    isActive = false,
    totalSelectedCount = 1,
    currentSlot = nil,
    currentSide = 1,
    handlerObject = nil,
    requiredSlot = 0,
    currentCount = 0
}

function SlotHandler:init(host,row,col)
    leftSlots  = {}          -- create the matrix
    rightSlots = {}          -- create the matrix

    self.host = host

    self.handlerObject = cppCreateSlotHandler(host)

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

function SlotHandler:setSelectedCount(tCount)
    self.selectedSlots = {}
    self.totalSelectedCount = tCount
    self.currentCount = 0
end

function SlotHandler:selectHover(slot)
    self.currentSlot = slot
    cppSelectHoverSlot(self.handlerObject,slot)
    self.current_index_x = cppGetSlotCol(slot)
    self.current_index_y = cppGetSlotRow(slot)
end

function SlotHandler:getSelectedSlots()
    return self.selectedSlots
end

function SlotHandler:clearSelectedSlots()
    self.selectedSlots = {}
end


function SlotHandler:onSignal(host,signal,side)

    if (side & 1) == 1 then
        self.currentSide = 1
    else
        self.currentSide = 2
    end

    if signal == 1 then
        self.current_index_x = self.current_index_x + 1
        if self.current_index_x > 3 then
            self.current_index_x = 1
            if side == 3 then
                self.currentSide = self.currentSide + 1
            end
            if self.currentSide > 2 then
                self.currentSide = 1
            end
        end
    end

    if signal == 2 then
        self.current_index_x = self.current_index_x - 1
        if self.current_index_x < 1 then
            self.current_index_x = 3
            if side == 3 then
                self.currentSide = self.currentSide + 1
            end
            if self.currentSide > 2 then
                self.currentSide = 1
            end
        end
    end

    if signal == 4 then
        self.current_index_y = self.current_index_y - 1
        if self.current_index_y < 1 then
            self.current_index_y = 1
        end
    end

    if signal == 8 then 
        self.current_index_y = self.current_index_y + 1
        if self.current_index_y > 3 then
            self.current_index_y = 3
        end
    end

    self:selectHover(self:getSlot(self.current_index_x, self.current_index_y, self.currentSide))

    if signal == 32 then
        self.selectedSlots[self.currentCount + 1] = self.currentSlot
        print("set current count " .. self.currentCount + 1)
        self.currentCount = self.currentCount + 1
    end
    
    --cppSelectHoverSlot(self.handlerObject,self.currentSlot)
end

function SlotHandler:getCurrentCount()
    return self.currentCount
end

