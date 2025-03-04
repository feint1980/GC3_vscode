


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