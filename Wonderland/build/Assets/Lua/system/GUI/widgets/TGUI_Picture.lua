


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

function Picture:init(host,path,posX,posY,width,height,parent)
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


---@Description set the position of the picture
---@param posX number x position
---@param posY number y position
function Picture:setPos(posX, posY)
    TGUI_Picture_SetPos(self.ptr, posX, posY)
    self.posX = posX
    self.posY = posY
end

---@Description set the position of the picture (string version)
---@param posXStr string x position
---@param posYStr string y position
function Picture:setPosStr(posXStr, posYStr)
    TGUI_Picture_SetPosStr(self.ptr, posXStr, posYStr)
    
end

---@Description set the size of the picture
---@param width number width
---@param height number height
function Picture:setSize(width, height)
    TGUI_Picture_SetSize(self.ptr, width, height)
    self.width = width
    self.height = height
end

---@Description set the size of the picture (string version)
---@param width string width
---@param height string height
function Picture:setSizeStr(width, height)
    TGUI_Picture_SetSizeStr(self.ptr, width, height)
end

---@Description set the texture of the picture
---@param path string path
function Picture:setTexture(path)
    TGUI_Picture_SetTexture(self.ptr, path)
    self.path = path
end


--- MARK: Wrapper
--- function wrapper of cpp_Label_Create
---@Description create new tgui label object in cpp
---@param host pointer instance of TGUIScriptingManager
---@param path string path to texture file
---@param posX number x position
---@param posY number y position
---@param width number width
---@param height number height
---@param parent? pointer instance parent, default nil (main)
---@return pointer instance of TGUI Label
function TGUI_Picture_Create(host, path, posX, posY,    width, height,parent)
    parent = parent or nil
    return cpp_Picture_Create(host, path, posX, posY, width, height,parent)
end

--- function wrapper of cpp_Picture_SetPos
--- @Description set the position of the picture
--- @param picture pointer instance of TGUI Picture
--- @param posX number x position
--- @param posY number y position
function TGUI_Picture_SetPos(picture, posX, posY)
    cpp_Picture_SetPos(picture, posX, posY)
end

--- function wrapper of cpp_Picture_SetPosStr
--- @Description set the position of the picture (string version)
--- @param picture pointer instance of TGUI Picture
--- @param posXStr string x position
--- @param posYStr string y position
function TGUI_Picture_SetPosStr(picture, posXStr, posYStr)
    cpp_Picture_SetPosStr(picture, posXStr, posYStr)
end

--- function wrapper of cpp_Picture_SetSize
--- @Description set the size of the picture
--- @param picture pointer instance of TGUI Picture
--- @param width number width
--- @param height number height
function TGUI_Picture_SetSize(picture, width, height)
    cpp_Picture_SetSize(picture, width, height)
end

--- function wrapper of cpp_Picture_SetSizeStr
--- @Description set the size of the picture (string version)
--- @param picture pointer instance of TGUI Picture
--- @param width string width
--- @param height string height
function TGUI_Picture_SetSizeStr(picture, width, height)
    cpp_Picture_SetSizeStr(picture, width, height)
end

--- function wrapper of lua_Picture_SetTexture
---@Description set the texture of the picture
---@param picture pointer instance of TGUI Picture
---@param texturePath string path to texture
function TGUI_Picture_SetTexture(picture, texturePath)
    lua_Picture_SetTexture(picture, texturePath)
end

