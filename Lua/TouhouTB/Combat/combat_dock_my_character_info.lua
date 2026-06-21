package.path = package.path .. ';../../Lua/system/objects/?.lua;'


require "compositeObject"



Combat_dock_my_character_info = {
    renderContextHost = nil,
    mainDock = nil,
    windowWidth = 0,
    windowHeight = 0
}

function Combat_dock_my_character_info:new()
    local o = {}
    setmetatable(o, self)
    self.__index = self
    return o

end

function Combat_dock_my_character_info:init(renderHost,tWindowWidth, tWindowHeight)
    self.renderContextHost = renderHost
    self.windowWidth = tWindowWidth
    self.windowHeight = tWindowHeight

    -- reso should be 1600 900 (16:9)
    
    self.mainDock = L_compositeObject:new()
    local width = 350
    local height = 350
    local posX = self.windowWidth * 0.5 - width * 0.5
    local posY = self.windowHeight * 0.5 - height * 0.5

    self.mainDock:init(self.renderContextHost, -posX , -posY,width ,height, 0,5)
    self.mainDock:addPanel("Basic_border",0.5)
    self.mainDock:addEmblem(0,"emblem_pack.xml/corner_c_25.png", 15,0, 0, 10,0.5)
    self.mainDock:addEmblem(1,"emblem_pack.xml/corner_a_07_2.png", 15,0, 8, 
    -10, 0.25)



end