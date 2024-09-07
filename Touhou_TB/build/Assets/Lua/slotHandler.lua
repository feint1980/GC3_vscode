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
    turnHandler = nil,
    requiredSlot = 0,
    currentCount = 0,
    row = 0,
    col = 0
}

function SlotHandler:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end



function SlotHandler:init(host,tRow,tCol,tTurnHandler)
    leftSlots  = {}          -- create the matrix
    rightSlots = {}          -- create the matrix

    self.host = host

    self.handlerObject = cppCreateSlotHandler(host)
    self.turnHandler = tTurnHandler

    if(self.turnHandler ~= nil) then
        print("turnHandler is not nil")
    else
        print("turnHandler is nil")
    end

    self.row = tRow
    self.col = tCol

    for i=1,self.row do
        leftSlots[i] = {}     -- create a new row
        for j=1,self.col do
            leftSlots[i][j] = cppCreateSlot(host,i,j,1)--Slot:new()-- cppCreateSlot(host,i,j,1)
            --leftSlots[i][j]:init(host,i,j,1)
        end
    end

    for i=1,self.row do
        rightSlots[i] = {}     -- create a new row
        for j=1,self.col do
            rightSlots[i][j] = cppCreateSlot(host,i,j,2)--Slot:new()--cppCreateSlot(host,i,j,2)
            --rightSlots[i][j]:init(host,i,j,2)
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
   
    cppSelectHoverSlot(self.handlerObject,slot)
    self.current_index_x = cppGetSlotCol(slot)
    self.current_index_y = cppGetSlotRow(slot)
end

function SlotHandler:getSelectedSlots()
    print("check data before turn")
    for i = 1, #self.selectedSlots do
        print("got slot " .. i)
    end
    return self.selectedSlots
end

function SlotHandler:clearSelectedSlots()
    self.selectedSlots = {}
end


-- function SlotHandler:onMouseMove(host,x,y,button)

--     if (side & 1) == 1 then
--         self.currentSide = 1
--     else
--         self.currentSide = 2
--     end
-- end


function SlotHandler:onMouseMove(host,x,y,button,side,flag)

    if side < 0 and side > 3 then
        return
    end

    if side == 1 or side == 3 then
        for i = 1, self.row do
            for j = 1, self.col do
                pos_x, pos_y = cppGetSlotPos(leftSlots[i][j])

                if x > pos_x - 60 and x < pos_x + 60 and y > pos_y - 30 and y < pos_y + 30 then
                    self.current_index_x = j
                    self.current_index_y = i
                    self.currentSlot = self:getSlot(i,j,1)
                    self:selectHover(self.currentSlot)
                    --print("set current slot to " .. self.currentSlot.slotObj)
                end
            end
        end
    end -- if side == 1 or side == 3
    
    if side == 2 or side == 3 then
        for i = 1, self.row do
            for j = 1, self.col do
                pos_x, pos_y = cppGetSlotPos(rightSlots[i][j])

                if x > pos_x - 60 and x < pos_x + 60 and y > pos_y - 30 and y < pos_y + 30 then
                    self.current_index_x = j
                    self.current_index_y = i
                    self.currentSlot = self:getSlot(i,j,2)
                    self:selectHover(self.currentSlot)
                    --print("set current slot to " .. self.currentSlot.slotObj)
                end
            end
        end
    end -- if side == 1 or side == 3

    if flag == 1 then
        if cppIsSlotEmpty(host,self.currentSlot) ~= true then
            cppSlotHandlerSetValidTarget(host,false)
        else
            cppSlotHandlerSetValidTarget(host,true)
        end
    end
end

function SlotHandler:onSignal(host,signal,side,flag)

    print("on signal " .. signal .. " side " .. side .. " !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")

    if t_turnHandler:getCurrentCharacter().side == 2 then
        if side == 1 then
            side = 2
        else if side == 2 then
            side = 1
        end
    end
    end

    if side < 0 and side > 3 then
        return
    end

    if side ~= 3 then
        self.currentSide = side
    end

    --print("current side is " .. self.currentSide)
    local tValue = 1
    local invert = 1
    if self.currentSide == 2 then
        invert = -1
    end

    --print("invert is " .. invert)
    if signal == 1 then
        self.current_index_x = self.current_index_x + (tValue * invert)
    end

    if signal == 2 then
        self.current_index_x = self.current_index_x - (tValue * invert)
    end

    if self.currentSide == 1 then
        if self.current_index_x > 3 then
            self.current_index_x = 1
            --print("reset to 1 ")
            if side == 3 then
                self.currentSide = 2
                self.current_index_x = 3
            end
        end
        if self.current_index_x < 1 then
            self.current_index_x = 3
            if side == 3 then
                self.currentSide = 2
                self.current_index_x = 1
            end
        end
    end

    if self.currentSide == 2 then
        if self.current_index_x > 3 then
            self.current_index_x = 1
            if side == 3 then
                self.currentSide = 1
                self.current_index_x = 3
            end
        end
        if self.current_index_x < 1 then
            self.current_index_x = 3
            if side == 3 then
                self.currentSide = 1
                self.current_index_x = 1
            end
        end
    end

    if signal == 4 then
        self.current_index_y = self.current_index_y - 1
        if self.current_index_y < 1 then
            self.current_index_y = 3
        end
    end

    if signal == 8 then
        self.current_index_y = self.current_index_y + 1
        if self.current_index_y > 3 then
            self.current_index_y = 1
        end
    end


    self.currentSlot = self:getSlot(self.current_index_x, self.current_index_y, self.currentSide)
    --self:selectHover)
    if flag == 1 then
        while cppIsSlotEmpty(host,self.currentSlot) ~= true do           
            if signal == 1 then 
                self.current_index_x = self.current_index_x + invert
                if self.current_index_x > 3 then
                    self.current_index_x = 1
                end
            end
            if signal == 2 then
                self.current_index_x = self.current_index_x - invert
                if self.current_index_x < 1 then
                    self.current_index_x = 3
                end
            end
            if signal == 4 then
                self.current_index_y = self.current_index_y - 1
                if self.current_index_y < 1 then
                    self.current_index_y = 3
                end
            end

            if signal == 8 then
                self.current_index_y = self.current_index_y + 1
                if self.current_index_y > 3 then
                    self.current_index_y = 1
                end
            end

            self.currentSlot = self:getSlot(self.current_index_x, self.current_index_y, self.currentSide)
        end
    end 
    self:selectHover(self:getSlot(self.current_index_x, self.current_index_y, self.currentSide))
    
    --print("flag is " .. flag)
    if signal == 32 then
        if flag == 1 then
            if cppIsSlotEmpty(host,self.currentSlot) == true then
                self.selectedSlots[self.currentCount + 1] = self.currentSlot
                self.currentCount = self.currentCount + 1
            end
        elseif flag == 2 then
            if cppIsSlotEmpty(host,self.currentSlot) ~= true then
                self.selectedSlots[self.currentCount + 1] = self.currentSlot
                self.currentCount = self.currentCount + 1
                print("current count is " .. self.currentCount)
            else 
                -- todo add the show require target
                print("require target")
            end
        else
            self.selectedSlots[self.currentCount + 1] = self.currentSlot
            self.currentCount = self.currentCount + 1
        end

        --print("current count is " .. self.currentCount)
        --print("called function " .. self.turnHandler:getCurrentCharacter().name)
        if self.currentCount == t_guiIcons:getCurrentTTD().requiredSlotCount then
            if self.turnHandler:getCurrentCharacter().dyobj ~= nil then

                -- t_guiIcons:getCurrentTTD().funct(host,self.turnHandler:getCurrentCharacter().dyobj)

                tName = t_guiIcons:getCurrentTTD().name
                print("datata " .. tName)
                t_guiIcons:getCurrentTTD():useFunction(host,self.turnHandler:getCurrentCharacter())
                -- if tName == "Move" then
                --     move(host,self.turnHandler:getCurrentCharacter().dyobj)
                -- end

            else
                print("dyobj is nil")
            end
        end
        -- todo fix here
        --icon
        --t_guiIcons:currentTTD.funct(host,t_turnHandler:getCurrentCharacter())

        --print("set current count " .. self.currentCount + 1)

    end

    --cppSelectHoverSlot(self.handlerObject,self.currentSlot)
end

function SlotHandler:getCurrentCount()
    return self.currentCount
end

