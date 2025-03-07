

--- @class (exact) EditBox
--- @field host pointer instance of TGUIScriptingManager
--- @field ptr pointer instance of TGUI Editbox
--- @field posX number x position
--- @field posY number y position
--- @field width number width
--- @field height number height
--- @field parent? pointer instance of parent, default nil (main)
EditBox = {
    host = nil,
    ptr = nil,
    posX = 0,
    posY = 0,
    width = 0,
    height = 0,
    parent = nil
}


---@Description create new instance of EditBox
---@return EditBox
function EditBox:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end


---@Description create an instance of EditBox
---@param host pointer instance of TGUIScriptingManager
---@param posX number x position
---@param posY number y position
---@param width number width
---@param height number height
---@param parent? pointer instance of parent, default nil (main)
function EditBox:init(host,posX, posY, width, height, parent)
    parent = parent or nil
    self.ptr = TGUI_EditBox_Create(host, posX, posY, width, height, parent)
    self.host = host
    self.posX = posX
    self.posY = posY
    self.width = width
    self.height = height
end

---@Description set position of EditBox
---@param posX number x position
---@param posY number y position
function EditBox:setPos(posX, posY)
    TGUI_EditBox_SetPos(self.ptr, posX, posY)
    self.posX = posX
    self.posY = posY    
end



---@Description set position of EditBox (string)
---@param posXStr string x position
---@param posYStr string y position
function EditBox:setPosStr(posXStr, posYStr)
    TGUI_EditBox_SetPosStr(self.ptr, posXStr, posYStr)
end



---@Description set size of EditBox
---@param width number width
---@param height number height
function EditBox:setSize(width, height)
    TGUI_EditBox_SetSize(self.ptr, width, height)
end

---@Description set size of EditBox (string)
---@param widthStr string width
---@param heightStr string height
function EditBox:setSizeStr(widthStr, heightStr)
    TGUI_EditBox_SetSizeStr(self.ptr, widthStr, heightStr)
end

---@Description set the input only show this character for PW
---@param tC string (only first character count)
function EditBox:setPWCharacter(tC)
    TGUI_EditBox_SetPWChar(self.ptr, tC)
end

---@Description set text of EditBox
---@param text string text
function EditBox:setText(text)
    TGUI_EditBox_SetText(self.ptr, text)
end

---@Description get text of EditBox
---@return string text
function EditBox:getText()
    return TGUI_EditBox_GetText(self.ptr)
end


--- MARK: Wrapper

---wrapper of cpp_EditBox_Create
---@Description create an instance of TGUI EditBox
---@param host pointer instance of TGUIScriptingManager
---@param posX number x position
---@param posY number y position
---@param width number width
---@param height number height
---@param parent? pointer instance of parent, default nil (main)
---@return pointer instance of TGUI EditBox
function TGUI_EditBox_Create(host, posX, posY, width, height, parent)
    parent = parent or nil
    return cpp_EditBox_Create(host, posX, posY, width, height, parent)
end

---wrapper of cpp_EditBox_SetPos
---@Description set position of TGUI EditBox
---@param editBox pointer instance of TGUI EditBox
---@param posX number x position
---@param posY number y position
function TGUI_EditBox_SetPos(editBox, posX, posY)
    cpp_EditBox_SetPos(editBox, posX, posY)
end


---wrapper of cpp_EditBox_SetPosStr
---@Description set position of TGUI EditBox
---@param editBox pointer instance of TGUI EditBox
---@param posXStr string x position
---@param posYStr string y position
function TGUI_EditBox_SetPosStr(editBox, posXStr, posYStr)
    cpp_EditBox_SetPosStr(editBox, posXStr, posYStr)
end


---wrapper of cpp_EditBox_SetSize
---@Description set position of TGUI EditBox
---@param editBox pointer instance of TGUI EditBox
---@param width number 
---@param height number 
function TGUI_EditBox_SetSize(editBox, width, height)
    cpp_EditBox_SetSize(editBox, width, height)
end


---wrapper of cpp_EditBox_SetSizeStr
---@Description set position of TGUI EditBox
---@param editBox pointer instance of TGUI EditBox
---@param width string 
---@param height string 
function TGUI_EditBox_SetSizeStr(editBox, width, height)
    cpp_EditBox_SetSizeStr(editBox, width, height)
end

---wrapper of cpp_EditBox_SetPWChar
---@Description set password character of TGUI EditBox
---@param editBox pointer instance of TGUI EditBox
---@param tC string (only first character count)
function TGUI_EditBox_SetPWChar(editBox, tC)
    cpp_EditBox_SetPWChar(editBox, tC)
end

---wrapper of lua_EditBox_SetText
---@Description set text of TGUI EditBox
---@param editBox pointer instance of TGUI EditBox
---@param text string 
function TGUI_EditBox_SetText(editBox, text)
    cpp_EditBox_SetText(editBox, text)
end

---wrapper of lua_EditBox_GetText
---@Description get text of TGUI EditBox
---@param editBox pointer instance of TGUI EditBox
---@return string 
function TGUI_EditBox_GetText(editBox)
    return cpp_EditBox_GetText(editBox)
end
