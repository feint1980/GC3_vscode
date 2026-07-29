package.path = package.path .. ';../../Lua/system/renderer/?.lua;'


---@class (exact) L_compositeObject
---@field host pointer? instance of F_LuaRenderContext
---@field ptr pointer? instance of F_CompositeObject 
---@field posX number x position
---@field posY number y position
---@field width number width
---@field height number height
---@field depth number depth
---@field angle number angle
L_compositeObject = {}
L_compositeObject.__index = L_compositeObject

---@Description create new instance of L_compositeObject
---@return L_compositeObject
function L_compositeObject:new()

    local o = setmetatable({}, self)

    o.host = nil
    o.ptr = nil
    o.posX = 0
    o.posY = 0
    o.width = 0
    o.height = 0
    o.depth = 0
    o.angle = 0

    self.__index = self
    return o
end


function L_compositeObject:addChild(child)

end


---@Description Init L_compositeObject
---@param F_LuaRendererContext_ptr pointer instance of F_LuaRendererContext
---@param t_posX number x position
---@param t_posY number y position
---@param t_width number width
---@param t_height number height
---@param t_angle number angle
---@param t_depth number depth
function L_compositeObject:init (F_LuaRendererContext_ptr, t_posX, t_posY, t_width, t_height,t_angle,t_depth)

    self.posX = t_posX
    self.posY = t_posY
    self.width = t_width
    self.height = t_height
    self.angle = t_angle
    self.depth = t_depth
    self.host = F_LuaRendererContext_ptr

    self.ptr = LRC_CreateCompositeObject(F_LuaRendererContext_ptr, self.posX, self.posY, self.width, self.height, self.angle, self.depth)
end

---@Description remove L_compositeObject
function L_compositeObject:remove()
    if self.ptr == nil or self.host == nil then
        return
    end
    LRC_RemoveCompositeObject(self.host,self.ptr)
end

---@Description get pointer of L_compositeObject
---@return pointer instance of F_CompositeObject
function L_compositeObject:getPtr()
    return self.ptr
end

---@Description add sprite
---@param spriteName string name of the sprite
---@param posX number x position
---@param posY number y position
---@param dimX number width
---@param dimY number height
---@param r number red
---@param g number green
---@param b number blue
---@param a number alpha
---@param angle number angle
---@param depth number depth
---@return pointer instance of created tObject
function L_compositeObject:addSprite(spriteName, posX, posY, dimX, dimY, r,
g, b, a,angle, depth)
    if self.ptr == nil then
        return nil
    end
    return CompositeObject_addSprite(self.ptr, spriteName, posX, posY, dimX, dimY, r, g, b, a,angle, depth)
end

---@Description add animated object
---@param animationFile string path to the animation file
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
function L_compositeObject:addAnimatedObject(animationFile, startAnim, posX, posY, scaleX, scaleY, colorR, colorG, colorB, colorA, angle, depth)
    if self.ptr == nil then
        return nil
    end
    return CompositeObject_addAnimatedObject(self.ptr, animationFile, startAnim, posX, posY, scaleX, scaleY, colorR, colorG, colorB, colorA, angle, depth)
end

---@Description add panel (only 1 panel exist at the time)
---@param panelName string name of the panel
---@param scale number scale
function L_compositeObject:addPanel(panelName, scale)
    if self.ptr == nil then
        return
    end
    CompositeObject_addPanel(self.ptr, panelName, scale)
end

---@Description add emblem
---@param type number type of the emblem 0 - line, 1 - corner
---@param emblemName string name of the emblem
---@param placeFlag number place flag
---@param hideFlag number hide flag
---@param offsetX number x offset
---@param offsetY number y offset
---@param scale number scale
function L_compositeObject:addEmblem(type, emblemName, placeFlag, hideFlag, offsetX, offsetY, scale)
    if self.ptr == nil then
        return nil
    end
    return CompositeObject_addEmblem(self.ptr, type, emblemName, placeFlag, hideFlag, offsetX, offsetY, scale)
end

function L_compositeObject:setAngle(angle)
    if self.ptr == nil then
        return
    end
    CompositeObject_setAngle(self.ptr, angle)
end

function L_compositeObject:addLine(offsetX, offsetY, width, depth)
    if self.ptr == nil then
        return
    end

    CompositeObject_addLine(self.ptr, offsetX, offsetY, width, depth)
end

---@Description add text
---@param text string text
---@param posX number x position
---@param posY number y position
---@param aligment number aligment 1 - left | 2 - right | 3 - center
---@param scale number scale
---@param colorR number red
---@param colorG number green
---@param colorB number blue
---@param colorA number alpha
---@param angle number angle
---@return pointer? instance of created tText
function L_compositeObject:addText(text, posX, posY, aligment, scale, colorR
,colorG,colorB,colorA , angle )
    if self.ptr == nil then
        return nil
    end
    -- print("Lua object")
    -- print(self.ptr)
    return CompositeObject_addText(self.ptr, text, posX, posY, aligment, scale,
    colorR,colorG,colorB,colorA , angle)

end

---@Description show panel background
---@param value boolean 
function L_compositeObject:showPanelBG(value)
    if self.ptr == nil then
        return
    end
    CompositeObject_showPanelBG(self.ptr, value)
end

---@Description set panel background color
---@param colorR number red
---@param colorG number green
---@param colorB number blue
---@param colorA number alpha
function L_compositeObject:setPanelBGColor(colorR,colorG,colorB,colorA )
    if self.ptr == nil then
        return
    end
    CompositeObject_setPanelBGColor(self.ptr, colorR,colorG,colorB,colorA )
end

---@Description set panel background scale
---@param scale number
function L_compositeObject:setPanelBGScale(scale)
    if self.ptr == nil then
        return
    end
    CompositeObject_setPanelBGScale(self.ptr, scale)
end

function L_compositeObject:setVisible(value)
    if self.ptr == nil then
        return
    end
    CompositeObject_setVisible(self.ptr, value)
end

function L_compositeObject:setRegisterFlag(value)
    if self.ptr == nil then
        return
    end
    CompositeObject_registerSignalUpdate(self.ptr, value)
end

function L_compositeObject:isHovered() -- this is where I regcognize that I am stupid
    if self.ptr == nil then
        return false
    end
    return CompositeObject_isHovered(self.ptr)
end

function L_compositeObject:fireCallback(name)
    if self.ptr == nil then
        return
    end
    CompositeObject_fireCallback(self.ptr, name)
end


---[ List of alread existed template functions
--- onHoverEnter ---> mouse enter
--- onHoverLeave ---> mouse leave
---]

function L_compositeObject:registerCallback(name, callback)
    if self.ptr == nil then
        return
    end
    CompositeObject_registerCallback(self.ptr, name, callback)
end

function L_compositeObject:setFrameColor(colorR,colorG,colorB,colorA )
    if self.ptr == nil then
        return
    end
    CompositeObject_setFrameColor(self.ptr, colorR,colorG,colorB,colorA )
end