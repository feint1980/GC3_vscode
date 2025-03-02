

LabelColor ={}

LabelColor.Red = 1
LabelColor.Green = 2
LabelColor.Blue = 3




Label = {
    host = nil,
    ptr = nil,
    text ="",
    posX = 0,
    posY = 0,
    parent = nil

}

--- Create new instance of TGUI Label
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
    print("label init")
end


--- MARK: Wrapper
--- function wrapper of cpp_Label_Create
---@Description create new tgui label object in cpp
---@param host pointer instance of TGUIScriptingManager
---@text string text to display
---@param posX number x position
---@param posY number y position
---@param parent? pointer instance parent, default nil (main)
function TGUI_Label_Create(host, text, posX, posY,parent)
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

--- function wrapper of cpp_Label_SetText
---@Description set the text of the label
---@param label pointer instance of Label
---@param text string text to display
function TGUI_Label_SetText(label, text)
    cpp_Label_SetText(label, text)
end




