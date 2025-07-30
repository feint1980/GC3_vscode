
---@class (exact) Canvas
---@field host pointer instance of TGUIScriptingManager
---@field ptr pointer instance of TGUI Canvas
---@field posX number x position
---@field posY number y position
---@field width number width
---@field height number height
---@field parent? pointer instance of parent, default nil (main)

Canvas = {
    ---@type pointer
    host = nil,
    ---@type pointer
    ptr = nil,
    posX = 0,
    posY = 0,
    width = 0,
    height = 0,
    ---@type pointer
    parent = nil
    ---@type pointer
}

---@Description create new instance of Canvas
---@return Canvas
function Canvas:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

-- ---@Description create new instance of Canvas

function Canvas:init(host,name , posX, posY, width, height, parent)
    self.host = host
    -- self.ptr = --
    self.posX = posX
    self.posY = posY
    self.width = width
    self.height = height
    self.parent = parent
    self.ptr = TGUI_Canvas_Create(host,name, posX, posY, width, height, parent)
end

---@Description set the position of the canvas
---@param posX number x position
---@param posY number y position
function Canvas:setPos(posX, posY)
    TGUI_Canvas_SetPos(self.ptr, posX, posY)
    self.posX = posX
    self.posY = posY
end

---@Description set the position of the canvas (string version)
---@param posXStr string x position
---@param posYStr string y position
function Canvas:setPosStr(posXStr, posYStr)
    TGUI_Canvas_SetPosStr(self.ptr, posXStr, posYStr)
end

---@Description set the size of the canvas
---@param width number width
---@param height number height
function Canvas:setSize(width, height)
    TGUI_Canvas_SetSize(self.ptr, width, height)
    self.width = width
    self.height = height
end

---@Description set the size of the canvas (string version)
---@param widthStr string width
---@param heightStr string height
function Canvas:setSizeStr(widthStr, heightStr)
    TGUI_Canvas_SetSizeStr(self.ptr, widthStr, heightStr)
end


---@Description wrapper of cpp_Canvas_BindDrawCall
---@param callback function
---@return pointer
function Canvas:bindDrawCall(callback)
    TGUI_Canvas_BindDrawCall(self.host, self.ptr, callback)
end


---@Description wrapper of cpp_Canvas_Create
---@param host pointer instance of TGUIScriptingManager
---@param name string name of the canvas
---@param posX number x position
---@param posY number y position
---@param width number width
---@param height number height
---@param parent? pointer instance of parent, default nil (main)
function TGUI_Canvas_Create(host,name, posX,
    posY, width, height, parent)
    return cpp_Canvas_Create(host,name, posX, posY, width, height, parent)
end

---@Description wrapper of cpp_Canvas_SetPos
---@param canvas pointer instance of TGUI Canvas
---@param posX number x position
---@param posY number y position
function TGUI_Canvas_SetPos(canvas, posX, posY)
    cpp_Canvas_SetPos(canvas, posX, posY)
end

---@Description wrapper of cpp_Canvas_SetPosStr
---@param canvas pointer instance of TGUI Canvas
---@param posXStr string x position
---@param posYStr string y position
function TGUI_Canvas_SetPosStr(canvas, posXStr, posYStr)
    cpp_Canvas_SetPosStr(canvas, posXStr, posYStr)
end

---@Description wrapper of cpp_Canvas_SetSize
---@param canvas pointer instance of TGUI Canvas
---@param width number width
---@param height number height
function TGUI_Canvas_SetSize(canvas, width, height)
    cpp_Canvas_SetSize(canvas, width, height)
end

---@Description wrapper of cpp_Canvas_SetSizeStr
---@param canvas pointer instance of TGUI Canvas
---@param widthStr string width
---@param heightStr string height
function TGUI_Canvas_SetSizeStr(canvas, widthStr, heightStr)
    cpp_Canvas_SetSizeStr(canvas, widthStr, heightStr)
end

---@Description wrapper of cpp_Canvas_BindDrawCall
---@param host pointer instance of TGUIScriptingManager
---@param canvasName string name of the canvas
---@param callbackName string name of the callback
function TGUI_Canvas_BindDrawCall(host,canvasName, callbackName)
    cpp_Canvas_BindDrawCall(host, canvasName, callbackName)
end

---@Description wrapper of cpp_Add_DrawCall
---@param host pointer instance of TGUIScriptingManager
---@param name string name of the canvas
---@param callback function
function TGUI_Add_DrawCall(host,name,callback)
    cpp_Add_DrawCall(host,name, callback)
end
