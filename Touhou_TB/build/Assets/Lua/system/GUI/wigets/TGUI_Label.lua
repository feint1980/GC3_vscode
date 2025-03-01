

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
--- 
