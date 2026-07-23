
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


function LRC_RemoveCompositeObject(host, compositeObject)
    cpp_LRC_RemoveCompositeObject(host, compositeObject)
end

--- Composite Object

---@Description: Adds a sprite to the composite object
---@param compositeObject pointer instance of F_CompositeObject
---@param spriteName string name of the sprite
---@param posX number x position
---@param posY number y position
---@param dimX number width
---@param dimY number height
---@param colorR number red
---@param colorG number green
---@param colorB number blue
---@param colorA number alpha
---@param angle number angle
---@param depth number depth
---@
function CompositeObject_addSprite(compositeObject,spriteName, posX, posY, dimX, dimY, colorR,colorG,colorB,colorA , angle, depth)
    return cpp_CompositeObject_addSprite(compositeObject,spriteName, posX, posY, dimX, dimY, colorR,colorG,colorB,colorA , angle, depth)
end


---@Description: Adds an animated object to the composite object
---@param compositeObject pointer instance of F_CompositeObject
---@param filePath string path to the animation file
---@param startAnim string name of the animation to start
---@param posX number x position
---@param posY number y position
---@param scaleX number width
---@param scaleY number height
---@param colorR number red
---@param colorG number green
---@param colorB number blue
---@param colorA number alpha
---@param angle number angle
---@param depth number depth
---@return pointer instance of created tAObject
function CompositeObject_addAnimatedObject(compositeObject,filePath, startAnim, posX, posY, scaleX, scaleY, colorR,colorG,colorB,colorA , angle, depth)
    return cpp_CompositeObject_addAnimatedObject(compositeObject,filePath, startAnim, posX, posY, scaleX, scaleY, colorR,colorG,colorB,colorA , angle, depth)
end


---@Description Adds a panel to the composite object

function CompositeObject_addPanel(compositeObject, panelName, scale)
    cpp_CompositeObject_addPanel(compositeObject, panelName, scale)
end

function CompositeObject_addEmblem(compositeObject, type, emblemName, placeFlag, hideFlag, offsetX, offsetY, scale)
    cpp_CompositeObject_addEmblem(compositeObject, type, emblemName, placeFlag, hideFlag, offsetX, offsetY, scale)
end

function CompositeObject_setAngle(compositeObject, angle)
    cpp_CompositeObject_setAngle(compositeObject, angle)
end

function CompositeObject_addLine(compositeObject, offsetX, offsetY, width, depth)
    cpp_CompositeObject_addLine(compositeObject, offsetX, offsetY, width, depth)
end


function CompositeObject_addText(compositeObject, text, posX, posY, aligment, scale, colorR,colorG,colorB,colorA , angle )
    return cpp_CompositeObject_addText(compositeObject, text, posX, posY, aligment, scale, colorR,colorG,colorB,colorA , angle )
end

function CompositeObject_showPanelBG(compositeObject, value)
    cpp_CompositeObject_showPanelBG(compositeObject, value)
end

function CompositeObject_setPanelBGColor(compositeObject, colorR,colorG,colorB,colorA )
    cpp_CompositeObject_setPanelBGColor(compositeObject, colorR,colorG,colorB,colorA )
end

function CompositeObject_setPanelBGScale(compositeObject, scale)
    cpp_CompositeObject_setPanelBGScale(compositeObject, scale)
end

function CompositeObject_setVisible(compositeObject, value)
    cpp_CompositeObject_setVisible(compositeObject, value)
end