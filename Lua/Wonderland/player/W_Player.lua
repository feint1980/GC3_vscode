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
    ---@type pointer instance of W_Player
    dyobj = nil
}

---@Description create a new instance of Player
---@param o? table
---@return Player
function W_Player:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

---@Description initialize a new instance of Player
---@param host pointer instance of Wonderland_Base
---@param player pointer instance of W_Player
---@param t_animationPath string
---@param t_hpCap number
---@param t_staminaCap number
---@param walkSpeed number
---@param runSpeedScale number
function W_Player:init(host, player, t_animationPath,t_hpCap, t_staminaCap,
walkSpeed, runSpeedScale)

    self.animationPath = t_animationPath
    self.hpCap = t_hpCap
    self.staminaCap = t_staminaCap
    self.walkSpeed = walkSpeed
    self.runSpeedScale = runSpeedScale
    self.hp = self.hpCap
    self.stamina = self.staminaCap
    self.dyobj = player
end

