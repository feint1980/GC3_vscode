



LabelColor ={}

LabelColor.Red = 1
LabelColor.Green = 2
LabelColor.Blue = 3


--- @class pointer

--- @class (exact) Label
--- @field host pointer instance of TGUIScriptingManager
--- @field ptr pointer instance of TGUI Label
--- @field text string text to display
--- @field posX number x position
--- @field posY number y position
--- @field parent? pointer instance parent, default nil (main)
Label = {
    host = nil,
    ptr = nil,
    text ="",
    posX = 0,
    posY = 0,
    parent = nil

}

---@Description create new instance of Label
---@return Label
function Label:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

--- Init TGUI Label
---@Description create new tgui label object in lua
---@param host pointer instance of TGUIScriptingManager
---@text string text to display
---@param posX number x position
---@param posY number y position
---@param parent? pointer instance parent, default nil (main)
function Label:init(host, text, posX, posY,parent)
    parent = parent or nil
    self.ptr =  TGUI_Label_Create(host, text, posX, posY,parent)
    self.text = text
    self.posX = posX
    self.posY = posY    
    self.parent = parent    
    
end


---@Description set the position of the label
---@param posX number x position
---@param posY number y position
function Label:setPos(posX, posY)
    TGUI_Label_SetPos(self.ptr, posX, posY)
end

---@Description set the position of the label
---@param posXStr string x position
---@param posYStr string y position
function Label:setPosStr(posXStr, posYStr)
    TGUI_Label_SetPosStr(self.ptr, posXStr, posYStr)
end

---@Description set the text of the label
---@param text string text to display
function Label:setText(text)
    TGUI_Label_SetText(self.ptr, text)
end

---@Description set the alignment of the label
---@param alignment number alignment (0 = left, 1 = center, 2 = right)
function Label:setAlignment(alignment)
    TGUI_Label_SetAlignment(self.ptr, alignment)
end

---@Description set the color of the label
---@param r number red
---@param g number green
---@param b number blue
---@param a? number alpha
function Label:setColor(r,g,b,a)
    a = a or 255
    TGUI_Label_SetTextColor(self.ptr, r,g,b,a)
end

---@Description set the callback of the label on hover
---@param func function
function Label:setOnHoverCallback(func)
    TGUI_Label_setOnHoverCallback(self.ptr, func)
end

---@Description set the callback of the label off hover
---@param func function
function Label:setOffHoverCallback(func)
    TGUI_Label_setOffHoverCallback(self.ptr, func)
end

---@Description set the callback of the label on click
---@param func function
function Label:setOnClickCallback(func)
    TGUI_Label_setOnClickCallBack(self.ptr, func)
end


---@Description set the label change color on Hover : on -> green | off ->white
function Label:setHoverable( hR, hG, hB, hA, oR, oG, oB, oA)
    self:setOnHoverCallback(function() self:setColor(hR,hG,hB,hA) end)
    self:setOffHoverCallback(function() self:setColor(oR,oG,oB,oA) end)
end



--- MARK: Wrapper
--- function wrapper of cpp_Label_Create
---@Description create new tgui label object in cpp
---@param host pointer instance of TGUIScriptingManager
---@param text string text to display
---@param posX number x position
---@param posY number y position
---@param parent? pointer instance parent, default nil (main)
---@return pointer instance of TGUI Label
function TGUI_Label_Create(host, text, posX, posY,parent)
    parent = parent or nil
    return cpp_Label_Create(host, text, posX, posY,parent)
end

--- function wrapper of cpp_Label_SetPos
--- @Description set the position of the label
---@param label pointer instance of Label
---@param posX number x position
---@param posY number y position
function TGUI_Label_SetPos(label, posX, posY)
    cpp_Label_SetPos(label, posX, posY)
end

--- function wrapper of cpp_Label_SetPosStr
--- @Description set the position of the label
---@param label pointer instance of Label
---@param posXStr string x position
---@param posYStr string y position
function TGUI_Label_SetPosStr(label, posXStr, posYStr)
    cpp_Label_SetPosStr(label, posXStr, posYStr)
end


--- function wrapper of cpp_Label_SetText
---@Description set the text of the label
---@param label pointer instance of Label
---@param text string text to display
function TGUI_Label_SetText(label, text)
    cpp_Label_SetText(label, text)
end

--- function wrapper of cpp_Label_SetAlignment
---@Description set the alignment of the label
---@param label pointer instance of Label
---@param aligmentType number 0 left, 1 center, 2 right
function TGUI_Label_SetAlignment(label, aligmentType)
    cpp_Label_SetAlignment(label, aligmentType)
end

--- function wrapper of cpp_Label_SetTextColor
---@Description set the text color of the label
---@param label pointer instance of Label
---@param r number red (0-255)
---@param g number green (0-255)
---@param b number blue (0-255)
---@param a? number alpha (0-255) default 255
function TGUI_Label_SetTextColor(label, r, g, b,a)
    a = a or 255
    cpp_Label_SetTextColor(label, r, g, b, a)
end


--- function wrapper of cpp_Label_SetOnHoverCallback
---@Description set the on hover callback of the label
---@param label pointer instance of Label
---@param callback function
function TGUI_Label_setOnHoverCallback(label, callback)
    cpp_Label_SetOnHoverCallback(label, callback)
end

--- function wrapper of cpp_Label_SetOffHoverCallback
---@Description set the off hover callback of the label
---@param label pointer instance of Label
---@param callback function
function TGUI_Label_setOffHoverCallback(label, callback)
    cpp_Label_SetOffHoverCallback(label, callback)
end

--- function wrapper of cpp_Label_SetOnClickCallBack
---@Description set the on click callback of the label
---@param label pointer instance of Label
---@param callback function
function TGUI_Label_setOnClickCallBack(label, callback)
    cpp_Label_SetOnClickCallback(label, callback)
end