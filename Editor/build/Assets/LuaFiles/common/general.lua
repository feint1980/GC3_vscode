
math.randomseed(os.time())

--- get a random number (float)
---@Description: Creates a new object (F_Lua_GenericObject)
---@param low number the min of the random value
---@param high number the max of the random value
---@return number a random number between low and high
function G_randomFloat(lower, greater)
    return lower + math.random()  * (greater - lower);
end