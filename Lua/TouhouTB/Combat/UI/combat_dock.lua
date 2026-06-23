
package.path = package.path ..';../../Lua/TouhouTB/Combat/?.lua' .. ';../../Lua/system/objects/?.lua;'

require "combat_dock_my_character_info"


---@class (exact) Combat_dock 
---@field renderContexthost? pointer instance of RenderContext
---@field characterDock? pointer instance of combat_dock_my_character_info
---@field windowWidth number
---@field windowHeight number
Combat_dock = {
    renderContexthost = nil,
    characterDock = nil,
    windowWidth = 0,
    windowHeight = 0
}

function Combat_dock:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function Combat_dock:init(renderHost,tWindowWidth, tWindowHeight)
    self.renderContexthost = renderHost
    self.windowWidth = tWindowWidth
    self.windowHeight = tWindowHeight

    print("window reso is " .. self.windowWidth .. " " .. self.windowHeight)
    self.characterDock = Combat_dock_my_character_info:new()
    self.characterDock:init(renderHost,tWindowWidth, tWindowHeight)

    
end
