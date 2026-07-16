package.path = package.path .. ';../../Lua/system/objects/?.lua;' .. ';../../Lua/TouhouTB/Combat/UI/?.lua;'

require "compositeObject"

Combat_dock_right_panel = {}
Combat_dock_right_panel.__index = Combat_dock_right_panel

function Combat_dock_right_panel:new()

    local o = setmetatable({}, self)

    o.renderContextHost = nil
    o.windowWidth = 0
    o.windowHeight = 0
    o.posX = 0
    o.posY = 0

    o.mainPanel = nil

    return o
end

function Combat_dock_right_panel:init(renderHost,tPosX, tPosY, tWindowWidth, tWindowHeight)
    self.renderContextHost = renderHost
    self.posX = tPosX
    self.posY = tPosY
    self.windowWidth = tWindowWidth
    self.windowHeight = tWindowHeight

    self.mainPanel = L_compositeObject:new()
    self.mainPanel:init(self.renderContextHost, self.posX, self.posY,
    self.windowWidth, self.windowHeight, 0, 10)

    self.mainPanel:addPanel("Simple_border", 0.25)

    self.mainPanel:addEmblem(0,"emblem_pack.xml/corner_c_25.png", 15,0, 0,
        10, 0.5)

    self.mainPanel:addEmblem(1,"emblem_pack.xml/corner_a_07_2.png", 15,15, 20,
        -20, 0.5)


end


