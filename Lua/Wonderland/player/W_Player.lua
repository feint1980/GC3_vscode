function _G.is_bit_set(value, bit_index)
    return (value & (1 << (bit_index ))) ~= 0
end

---@class pointer


---@class W_Player
W_Player = {
    animationPath = "",
    hp = 100,
    hpCap = 100,
    stamina = 100,
    staminaCap = 100,
    walkSpeed = 2.5,
    runSpeedScale = 2.25,
    currentFacing = 0, -- facing : 0-down, 1-up, 2-left, 3-right
    previousFacing = 0,
    moveFlag = 0, -- 1 = left, 2 = right, 4 = up, 8 = down
    ---@type pointer instance of W_Player
    dyobj = nil
}

---@Description create a new instance of Player
---@param o? table
---@return W_Player
function W_Player:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

---@Description initialize a new instance of Player
---@param host pointer instance of Wonderland_Base
---@param t_animationPath string
---@param t_hpCap number
---@param t_staminaCap number
---@param walkSpeed number
---@param runSpeedScale number
function W_Player:init(host, t_animationPath,t_hpCap, t_staminaCap,
walkSpeed, runSpeedScale)

    self.animationPath = t_animationPath
    self.hpCap = t_hpCap
    self.staminaCap = t_staminaCap
    self.walkSpeed = walkSpeed
    self.runSpeedScale = runSpeedScale
    self.hp = self.hpCap
    self.stamina = self.staminaCap
    self.dyobj = cppCreatePlayer(host, t_animationPath,t_hpCap, t_staminaCap)
    self:setAttribute("hp", self.hp)
    self:setAttribute("hpCap", self.hpCap)
    self:setAttribute("stamina", self.stamina)
    self:setAttribute("staminaCap", self.staminaCap)
    self:setAttribute("walkSpeed", self.walkSpeed)
    self:setAttribute("runSpeedScale", self.runSpeedScale)
    self.currentFacing = 0
    self.previousFacing = self.currentFacing
end

---@Description set the attribute of the player
---@param att string
---@param value number
function W_Player:setAttribute(att, value)
    cppPlayerSetAttribute(self.dyobj, att, value)
end

---@Description play an animation
---@param animationPath string
---@param time number
function W_Player:playAnimation(animationPath, time)
    cppPlayerPlayAnimation(self.dyobj, animationPath, time)
end

function W_Player:setMovement(flag)
    cppPlayerSetMovement(self.dyobj, flag)
end

function W_Player:inputHandling(signal)
    --- Input chart 
    --- 1 left 
    --- 2 right 
    --- 4 up 
    --- 8 down

    -- instead of using bit 1 2 4 8, it now use 0 1 2 3 
    -- as for |0 |0 |0 |0
    ---is     |0 |1 |2 |3 (Lua)
    ---is     |1 |2 |4 |8 (C++) 

    if  is_bit_set(signal,2) then -- meaning bit 4 
        self.currentFacing = 1
    elseif  is_bit_set(signal, 3) then -- meaning bit 8
        self.currentFacing = 0
    end
    -- prioritize side walk animation
    if  is_bit_set(signal, 0) then -- meaning bit 1
        self.currentFacing = 2
    elseif  is_bit_set(signal,1) then -- meaning bit 2
        self.currentFacing = 3
    end

    if self.currentFacing ~= self.previousFacing then 
        self.previousFacing = self.currentFacing
        -- facing : 0-down, 1-up, 2-left, 3-right
        if self.currentFacing == 0 then
            self:playAnimation("walk_down", -1)
        elseif self.currentFacing == 1 then
            self:playAnimation("walk_up", -1)
        elseif self.currentFacing == 2 then
            self:playAnimation("walk_side_left", -1)
        elseif self.currentFacing == 3 then
            self:playAnimation("walk_side_right", -1)
        end
    end
    if signal == 0 then
        if self.currentFacing == 0 then
            self:playAnimation("idle_down", -1)
        elseif self.currentFacing == 1 then
            self:playAnimation("idle_up", -1)
        elseif self.currentFacing == 2 then
            self:playAnimation("idle_side_left", -1)
        elseif self.currentFacing == 3 then
            self:playAnimation("idle_side_right", -1)
        end
    end
    self:setMovement(signal)
end
