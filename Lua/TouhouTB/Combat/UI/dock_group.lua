package.path = package.path .. ';../../Lua/system/objects/?.lua;' .. ';../../Lua/TouhouTB/Combat/UI/?.lua;'

require "compositeObject"

---@class (exact) Dock_group
---@field renderContextHost? pointer instance of RenderContext
---@field posX number x position
---@field posY number y position
---@field mWidth number width
---@field mHeight number height
---@field buttons table array of buttons
Dock_group = {
    renderContextHost = nil,
    posX = 0,
    posY = 0,
    mWidth = 0,
    mHeight = 0,

    buttons = {},
}


function Dock_group:new()
    local o = {}
    setmetatable(o, self)
    setmetatable(o.buttons, {})    
    self.__index = self
    return o
end