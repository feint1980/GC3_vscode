
-- LRC ( Lua Render Context)

---@Description: Creates a new composite object
---@param host pointer instance of F_LuaRenderContext
---@param posX number x position
---@param posY number y position
---@param dimX number width
---@param dimY number height
---@param angle number angle
---@param depth number depth
---@return pointer instance of created F_CompositeObject
function LRC_CreateCompositeObject(host, posX, posY, dimX, dimY, angle, depth)
    return cpp_LRC_CreateCompositeObject(host, posX, posY, dimX, dimY, angle, depth)
end


--- Composite Object

function CompositeObject_addSprite(compositeObject,spriteName, posX, posY, dimX, dimY, colorR,color)



end



