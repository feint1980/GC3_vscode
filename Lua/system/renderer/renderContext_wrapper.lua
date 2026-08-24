
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

---@return pointer instance of created compositeText
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

function CompositeObject_registerSignalUpdate(compositeObject, signalValue)
    cpp_CompositeObject_registerSignalUpdate(compositeObject, signalValue)
end

function CompositeObject_isHovered(compositeObject)    
    return cpp_CompositeObject_isHovered(compositeObject)
end

function CompositeObject_registerCallback(compositeObject, callbackName, callbackFun)
    cpp_CompositeObject_registerCallback(compositeObject, callbackName, callbackFun)
end

function CompositeObject_fireCallback(compositeObject, callbackName)
    cpp_CompositeObject_fireCallback(compositeObject, callbackName)
end

function CompositeObject_setFrameColor(compositeObject, colorR,colorG,colorB,colorA )
    cpp_CompositeObject_setFrameColor(compositeObject, colorR,colorG,colorB,colorA )
end

---- Composite sprite section 

function CompositeObjectSprite_setSprite(compositeSprite, spriteName)
    cpp_CompositeObjectSprite_setSprite(compositeSprite, spriteName)
end

function CompositeObjectSprite_setVisible(compositeSprite, value)
    cpp_CompositeObjectSprite_setVisible(compositeSprite, value)
end

--- Composite text section

function CompositeObjectText_setText(compositeText, text)
    cpp_CompositeObjectText_setText(compositeText, text)
end

function CompositeObjectText_setTextColor(compositeText, colorR,colorG,colorB,colorA )
    cpp_CompositeObjectText_setTextColor(compositeText, colorR,colorG,colorB,colorA )
end

function CompositeObjectText_setScale(compositeText, scale)
    cpp_CompositeObjectText_setScale(compositeText, scale)
end

function CompositeObjectText_setAligment(compositeText, aligment)
    cpp_CompositeObjectText_setAligment(compositeText, aligment)
end

function CompositeObjectText_setPositionOffset(compositeText, posX, posY)
    cpp_CompositeObjectText_setPositionOffset(compositeText, posX, posY)
end


function CompositeObjectText_setTextAllOpt(compositeText, opts)
    opts = opts or {}

    if opts.text      ~= nil then
        CompositeObjectText_setText(compositeText, opts.text)
    end
    if opts.posX      ~= nil or opts.posY ~= nil then
        CompositeObjectText_setPositionOffset(compositeText, opts.posX or 0, opts.posY or 0)
    end
    if opts.alignment ~= nil then
        CompositeObjectText_setAligment(compositeText, opts.alignment)
    end
    if opts.scale     ~= nil then 
        CompositeObjectText_setScale(compositeText, opts.scale)
    end
    if opts.colorR    ~= nil or opts.colorG ~= nil or opts.colorB ~= nil or opts.colorA ~= nil then
        CompositeObjectText_setTextColor(compositeText,
            opts.colorR or 1, opts.colorG or 1, opts.colorB or 1, opts.colorA or 1)
    end
end
