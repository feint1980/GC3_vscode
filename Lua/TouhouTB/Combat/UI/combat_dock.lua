
package.path = package.path ..';../../Lua/TouhouTB/Combat/?.lua' .. ';../../Lua/system/objects/?.lua;'

require "combat_dock_my_character_info"
require "combat_dock_middle_panel"
require "combat_dock_right_panel"

---@class (exact) Combat_dock 
---@field renderContexthost? pointer instance of RenderContext
---@field characterDock? pointer instance of combat_dock_my_character_info
---@field middleDock? pointer instance of combat_dock_
---@field rightDock? pointer instance of combat_dock_
---@field windowWidth number
---@field windowHeight number
Combat_dock = {}
Combat_dock.__index = Combat_dock

function Combat_dock:new()
    local o = setmetatable({}, self)
    o.renderContexthost = nil
    o.characterDock = nil
    o.middleDock = nil
    o.rightDock = nil
    o.windowWidth = 0
    o.windowHeight = 0

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
    print("tsew")
    self.middleDock = Combat_dock_middle_panel:new()
    self.middleDock:init(renderHost,tWindowWidth * 0.5, 0 - (tWindowHeight * 0.5) + 200,  tWindowWidth, tWindowHeight)

    -- right dock 
    self.rightDock = Combat_dock_right_panel:new()
    local rightDockWidth = 450
    local rightDockHeight = 420
    self.rightDock:init(renderHost, 565, -240,  rightDockWidth, rightDockHeight, tWindowWidth, tWindowHeight)

    
end
