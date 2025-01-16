package.path = package.path .. ';./Assets/Lua/slots/?.lua;'


require "Slot"

leftSlots  = {}
rightSlots = {}

---Description of SlotHandler: TBD 
---@class SlotHandler
SlotHandler = {

    ---@type pointer instace of BattleScene
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

---Create an instace of SlotHandler
---@return SlotHandler 
function SlotHandler:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

---Initialize the SlotHandler (call after create by using "new()" function )
---@param host pointer instace of BattleScene
---@param tCol number The number of column (each side)
---@param tRow number The number of row (each side)
---@param tTurnHandler instance of TurnHandler(lua)
function SlotHandler:init(host,tCol,tRow,tTurnHandler)
    leftSlots  = {}
    rightSlots = {}

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

    for i=1,self.col do
        leftSlots[i] = {}-- create a new rows
        for j=1,self.row do
            leftSlots[i][j] = cppCreateSlot(host,i,j,1)
            --Slot:new()-- cppCreateSlot(host,i,j,1) | old format
            --leftSlots[i][j]:init(host,i,j,1)
        end
    end

    for i=1,self.col do
        rightSlots[i] = {}-- create a new rows
        for j=1,self.row do
            rightSlots[i][j] = cppCreateSlot(host,i,j,2)
            --Slot:new()--cppCreateSlot(host,i,j,2) | old format
            --rightSlots[i][j]:init(host,i,j,2)
        end
    end
end

---Get the slot by column and row index, default side is 1
---@param tCol number The column index
---@param tRow number The row index
---@param tSide number (optional) 1 = left, 2 = right (default is 1)
---@return pointer instance of Slot
function SlotHandler:getSlot(tCol,tRow,tSide)
    tSide = tSide or 1
    if tSide == 1 then
        return leftSlots[tCol][tRow]
    elseif tSide == 2 then
        return rightSlots[tCol][tRow]
    end
end


---Set the required number of slot need to be selected/targeted
---@param tCount number The number of slot
function SlotHandler:setTotalSelectedCount(tCount)
    self.selectedSlots = {}
    self.totalSelectedCount = tCount
    self.currentCount = 0
end


---Set the slot as hovered 
---@param slot pointer instance of Slot
function SlotHandler:selectHover(slot)
    cppSelectHoverSlot(self.handlerObject,slot)
    self.current_index_x = cppGetSlotCol(slot)
    self.current_index_y = cppGetSlotRow(slot)
end

---Return the slots selected/targeted 
---@return table The selected slots
function SlotHandler:getSelectedSlots()
    print("check data before turn")
    for i = 1, #self.selectedSlots do
        print("got slot " .. i)
    end
    return self.selectedSlots
end

---Clear the selected slots
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



--- Handle mouse move event
---@param host pointer instance of BattleScene
---@param x number 
---@param y number
---@param button number
---@param side number |1 = left, 2 = right, 3 = both|
---@param flag number |0 = none|1=empty only|2 has character in slot|
function SlotHandler:onMouseMove(host,x,y,button,side,flag)

    --- check if side is valid
    if side < 0 and side > 3 then
        return
    end

    -- bit 1 has left side
    -- bit 2 has right side
    -- 3 has both bit 1 and bit 2

    -- check for left side
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
    
    -- check for right side
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


    -- Flag: |0 = none|1=empty only|2 has character in slot|
    if flag == SlotFlag.EmptyOnly then 
        if cppIsSlotEmpty(host,self.currentSlot) == true then
            cppSlotHandlerSetValidTarget(host,true)
        else
            cppSlotHandlerSetValidTarget(host,false)
        end
    end
end

--- Revert the targeting side(based on current side ) For example : if a spell/item that is used (left) will target right only, and then that spell/item when used on the right will target left only
---@param side number |1 = left, 2 = right|
function revertSide(side)
    if side == 1 then
        return 2
    elseif side == 2 then
        return 1
    end
end

--- Handle signal (keyboard or gamepad)
---@param host pointer instance of BattleScene
---@param signal number keystroke or gamepad button
---@param side number |1 = left, 2 = right, 3 = both|
---@param flag number |0 = none|1=empty only|2 has character in slot|
function SlotHandler:onSignal(host,signal,side,flag)

    print("on signal " .. signal .. " side " .. side .. " !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")

    -- check if side is valid
    if side < 0 and side > 3 then
        print("side is invalid")
        return
    end



    --- This is the old code, however I decided to keep it as comment because it wasn't tested
    --- throughtly
    -- -- invert side if character on the right
    -- if t_turnHandler:getCurrentCharacter().side == 2 then
    --     if side == 1 then
    --         side = 2
    --     else if side == 2 then
    --         side = 1
    --     end
    -- end
    -- end -- please don't remove this end
    
    -- new invert format
    if t_turnHandler:getCurrentCharacter().side == 2 then
        side = revertSide(side)
    end

    -- I can't remember why
    if side ~= 3 then
        self.currentSide = side
    end

    --print("current side is " .. self.currentSide)
    local tValue = 1
    local invert = 1
    if self.currentSide == 2 then
        invert = -1
    end

    --- Signal chart: 
    --- 1 = left key    || d-pad left
    --- 2 = right key   || d-pad right
    --- 4 = up key      || d-pad up
    --- 8 = down key    || d-pad down
    --- 16 = None -> reserve for now
    --- 32 = enter      || a button
    --- 64 = escape     || b button

    if signal == 1 then 
        -- move the cursor to the left
        self.current_index_x = self.current_index_x + (tValue * invert)
    end

    if signal == 2 then
        -- move the cursor to the right
        self.current_index_x = self.current_index_x - (tValue * invert)
    end

    -- reset the cursor if it goes out of bounds
    if self.currentSide == 1 then
        if self.current_index_x > 3 then
            -- reset from 1 to 3
            self.current_index_x = 1
        
            -- if side is 3 (both side) then reset the cursor to the other side
            if side == 3 then
                self.currentSide = 2
                self.current_index_x = 3
            end
        end
        if self.current_index_x < 1 then
            -- reset from 1 to 3
            self.current_index_x = 3
            -- if side is 3 (both side) then reset the cursor to the other side
            if side == 3 then
                self.currentSide = 2
                self.current_index_x = 1
            end
        end
    end

    -- reset the cursor if it goes out of bounds
    if self.currentSide == 2 then
        if self.current_index_x > 3 then
            -- reset from 3 to 1
            self.current_index_x = 1
            -- if side is 3 (both side) then reset the cursor to the other side
            if side == 3 then
                self.currentSide = 1
                self.current_index_x = 3
            end
        end
        if self.current_index_x < 1 then
            -- reset from 3 to 1
            self.current_index_x = 3
            if side == 3 then
                -- if side is 3 (both side) then reset the cursor to the other side
                self.currentSide = 1
                self.current_index_x = 1
            end
        end
    end

    -- old format
    -- if signal == 4 then
    --     self.current_index_y = self.current_index_y - 1
    --     if self.current_index_y < 1 then
    --         self.current_index_y = 3
    --     end
    -- end

    -- if signal == 8 then
    --     self.current_index_y = self.current_index_y + 1
    --     if self.current_index_y > 3 then
    --         self.current_index_y = 1
    --     end
    -- end

    if signal == 4 then
        self.current_index_y = self.current_index_y - 1
    end

    if signal == 8 then
        self.current_index_y = self.current_index_y + 1
    end

    if self.current_index_y < 1 then
        self.current_index_y = 3
    end
    if self.current_index_y > 3 then
        self.current_index_y = 1
    end

    -- all index ready, get the current slot
    self.currentSlot = self:getSlot(self.current_index_x, self.current_index_y, self.currentSide)

    -- filter with flag
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
            -- get the filtered slot
            self.currentSlot = self:getSlot(self.current_index_x, self.current_index_y, self.currentSide)
        end
    end 
    -- hover the current slot
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

