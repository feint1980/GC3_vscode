

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
    self.ptr =  TGUI_Label_Create(host, text, posX, posY,parent)
end


---@Description set the position of the label
---@param posX number x position
---@param posY number y position
function Label:setPos(posX, posY)
    TGUI_Label_SetPos(self.ptr, posX, posY)
end

---@Description set the position of the label
---@param posX string x position
---@param posY number y position
function Label:setPosStr(posXStr, posY)
    TGUI_Label_SetPosStr(self.ptr, posXStr, posY)
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

--- MARK: Wrapper
--- function wrapper of cpp_Label_Create
---@Description create new tgui label object in cpp
---@param host pointer instance of TGUIScriptingManager
---@param text string text to display
---@param posX number x position
---@param posY number y position
---@param parent? pointer instance parent, default nil (main)
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

--- function wrapper of cpp_Label_SetPos
--- @Description set the position of the label
---@param label pointer instance of Label
---@param posX string x position
---@param posY number y position
function TGUI_Label_SetPosStr(label, posX, posY)
    cpp_Label_SetPos(label, posX, posY)
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



