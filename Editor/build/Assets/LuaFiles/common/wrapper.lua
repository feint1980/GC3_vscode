
-- Manual wrapper because I want to mark all the function expose by C++
-- OCD warning : this file will contain alot of warning 

--- Create a new object (wrapper of cppCreateFromLua)
---@Description: Creates a new object (F_Lua_GenericObject)
---@param host pointer instance of F_Lua_Boss_Manager
---@param animationPath string The path to the animation file
---@param posX number The x position of the object
---@param posY number The y position of the object
---@param scale number The scale of the object
---@param depth number The depth of the object
---@param angle number The angle of the object
---@return pointer instance of created F_Lua_GenericObject
function W_createObject(host ,animationPath , posX, posY,scale,depth,angle)
    cppCreateFromLua(host,animationPath,posX,posY,scale,depth,angle)
end

--- Move object to specific position (wrapper of cppMoveObject)
---@Description: Move object to specific position
---@param host pointer instance of F_Lua_Boss_Manager
---@param dynamicObject pointer instance of F_Lua_GenericObject to move
---@param posX number The x position of the object
---@param posY number The y position of the object
---@param time number the time to complete the move
---@param isWait boolean If the move should wait for completion (default true)
---@return null void return nothing
function W_moveObject(...)
    local host,dynob,posX,posY,time,isWait = select('#', ...), ...
    isWait = isWait or true
    cppMoveObject(host,dynob,posX,posY,time,isWait)
end

-- MARK: Fire section