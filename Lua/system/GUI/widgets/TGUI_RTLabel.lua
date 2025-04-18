

TextAlginment = {
    Left = 0,
    Center = 1,
    Right = 2
}


LabelColor ={}

LabelColor.Red = 1
LabelColor.Green = 2
LabelColor.Blue = 3


--- @class pointer

--- @class (exact) RTLabel
--- @field host pointer instance of TGUIScriptingManager
--- @field ptr pointer instance of TGUI RTLabel
--- @field text string text to display
--- @field posX number x position
--- @field posY number y position
--- @field parent? pointer instance parent, default nil (main)
RTLabel = {
    host = nil,
    ptr = nil,
    text ="",
    posX = 0,
    posY = 0,
    parent = nil

}

---@Description create new instance of RTLabel
---@return RTLabel
function RTLabel:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

--- Init TGUI RTLabel
---@Description create new tgui rtlabel object in lua
---@param host pointer instance of TGUIScriptingManager
---@text string text to display
---@param posX number x position
---@param posY number y position
---@param parent? pointer instance parent, default nil (main)
function RTLabel:init(host, text, posX, posY,parent)
    parent = parent or nil
    self.ptr =  TGUI_Label_Create(host, text, posX, posY,parent)
    self.text = text
    self.posX = posX
    self.posY = posY    
    self.parent = parent
    
end


---@Description set the position of the rtlabel
---@param posX number x position
---@param posY number y position
function RTLabel:setPos(posX, posY)
    TGUI_Label_SetPos(self.ptr, posX, posY)
end

---@Description set the position of the rtlabel
---@param posXStr string x position
---@param posYStr string y position
function RTLabel:setPosStr(posXStr, posYStr)
    TGUI_Label_SetPosStr(self.ptr, posXStr, posYStr)
end

---@Description set the text of the rtlabel
---@param text string text to display
function RTLabel:setText(text)
    TGUI_Label_SetText(self.ptr, text)
end

---@Description set the alignment of the rtlabel
---@param alignment number alignment (0 = left, 1 = center, 2 = right)
function RTLabel:setAlignment(alignment)
    TGUI_Label_SetAlignment(self.ptr, alignment)
end

---@Description set the color of the rtlabel
---@param r number red
---@param g number green
---@param b number blue
---@param a? number alpha
function RTLabel:setColor(r,g,b,a)
    a = a or 255
    TGUI_Label_SetTextColor(self.ptr, r,g,b,a)
end

---@Description set the callback of the rtlabel on hover
---@param func function
function RTLabel:setOnHoverCallback(func)
    TGUI_Label_setOnHoverCallback(self.ptr, func)
end

---@Description set the callback of the rtlabel off hover
---@param func function
function RTLabel:setOffHoverCallback(func)
    TGUI_Label_setOffHoverCallback(self.ptr, func)
end

---@Description set the callback of the rtlabel on click
---@param func function
function RTLabel:setOnClickCallback(func)
    TGUI_Label_setOnClickCallBack(self.ptr, func)
end


---@Description set the rtlabel change color on Hover : on -> green | off ->white
function RTLabel:setHoverable( hR, hG, hB, hA, oR, oG, oB, oA)
    self:setOnHoverCallback(function() self:setColor(hR,hG,hB,hA) end)
    self:setOffHoverCallback(function() self:setColor(oR,oG,oB,oA) end)
end


--- MARK: Wrapper
--- function wrapper of cpp_RTLabel_Create
---@Description create new tgui rtlabel object in cpp
---@param host pointer instance of TGUIScriptingManager
---@param text string text to display
---@param posX number x position
---@param posY number y position
---@param parent? pointer instance of parent, default nil (main)
---@return pointer instance of TGUI RTLabel
function TGUI_RTLabel_Create(host, text, posX, posY,parent)
    parent = parent or nil
    return cpp_RTLabel_Create(host, text, posX, posY,parent)
end

--- function wrapper of cpp_RTLabel_SetPos
--- @Description set the position of the rtlabel
---@param rtlabel pointer instance of RTLabel
---@param posX number x position
---@param posY number y position
function TGUI_RTLabel_SetPos(rtlabel, posX, posY)
    cpp_RTLabel_SetPos(rtlabel, posX, posY)
end

--- function wrapper of cpp_RTLabel_SetPosStr
--- @Description set the position of the rtlabel
---@param rtlabel pointer instance of RTLabel
---@param posXStr string x position
---@param posYStr string y position
function TGUI_RTLabel_SetPosStr(rtlabel, posXStr, posYStr)
    cpp_RTLabel_SetPosStr(rtlabel, posXStr, posYStr)
end


--- function wrapper of cpp_RTLabel_SetText
---@Description set the text of the rtlabel
---@param rtlabel pointer instance of RTLabel
---@param text string text to display
function TGUI_RTLabel_SetText(rtlabel, text)
    cpp_RTLabel_SetText(rtlabel, text)
end

--- function wrapper of cpp_RTLabel_SetAlignment
---@Description set the alignment of the rtlabel
---@param rtlabel pointer instance of RTLabel
---@param aligmentType number 0 left, 1 center, 2 right
function TGUI_RTLabel_SetAlignment(rtlabel, aligmentType)
    cpp_RTLabel_SetAlignment(rtlabel, aligmentType)
end

--- function wrapper of cpp_RTLabel_SetTextColor
---@Description set the text color of the rtlabel
---@param rtlabel pointer instance of RTLabel
---@param r number red (0-255)
---@param g number green (0-255)
---@param b number blue (0-255)
---@param a? number alpha (0-255) default 255
function TGUI_RTLabel_SetTextColor(rtlabel, r, g, b,a)
    a = a or 255
    cpp_RTLabel_SetTextColor(rtlabel, r, g, b, a)
end


--- function wrapper of cpp_RTLabel_SetOnHoverCallback
---@Description set the on hover callback of the rtlabel
---@param rtlabel pointer instance of RTLabel
---@param callback function
function TGUI_RTLabel_setOnHoverCallback(rtlabel, callback)
    cpp_RTLabel_SetOnHoverCallback(rtlabel, callback)
end

--- function wrapper of cpp_RTLabel_SetOffHoverCallback
---@Description set the off hover callback of the rtlabel
---@param rtlabel pointer instance of RTLabel
---@param callback function
function TGUI_RTLabel_setOffHoverCallback(rtlabel, callback)
    cpp_RTLabel_SetOffHoverCallback(rtlabel, callback)
end

--- function wrapper of cpp_RTLabel_SetOnClickCallBack
---@Description set the on click callback of the rtlabel
---@param rtlabel pointer instance of RTLabel
---@param callback function
function TGUI_RTLabel_setOnClickCallBack(rtlabel, callback)
    cpp_RTLabel_SetOnClickCallback(rtlabel, callback)
end