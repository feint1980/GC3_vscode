


---@class pointer



--- @class (exact) Picture
--- @field host pointer instance of TGUIScriptingManager
--- @field ptr pointer instance of TGUI Picture
--- @field path string path to image  
--- @field posX number x position
--- @field posY number y position
--- @field width number width
--- @field height number height
--- @field parent pointer instance of parent, default nil (main)
Picture = {
    
    host = nil,
    ptr = nil,
    path = "",
    posX = 0,
    posY = 0,
    width = 0,
    height = 0,
    parent = nil
    
}


---@class Picture

---@Description created a new picture
---@return Picture
function Picture:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function Picture:init(host,path,posX,posY,width,height,parent) )
    parent = parent or nil

    self.host = host
    self.ptr = TGUI_Picture_Create(host, path, posX, posY, width, height, parent)
    self.path = path
    self.posX = posX
    self.posY = posY
    self.width = width
    self.height = height
    self.parent = parent
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
function TGUI_Picture_Create(host, text, posX, posY,parent)
    parent = parent or nil
    return cpp_Label_Create(host, text, posX, posY,parent)
end




