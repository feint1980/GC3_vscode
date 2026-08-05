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
    o.width = 0
    o.height = 0

    o.mainPanel = nil
    o.sides = {}

    return o
end

function Combat_dock_right_panel:init(renderHost,tPosX, tPosY, panelWidth, panelHeight, tWindowWidth, tWindowHeight)
    self.renderContextHost = renderHost
    self.posX = tPosX
    self.posY = tPosY
    self.windowWidth = tWindowWidth
    self.windowHeight = tWindowHeight
    self.width = panelWidth
    self.height = panelHeight

    self.mainPanel = L_compositeObject:new()
    self.mainPanel:init(self.renderContextHost, self.posX, self.posY,
        self.width, self.height , 0, 10)

    self.mainPanel:addPanel("Simple_border", 0.25)

    self.mainPanel:addEmblem(0,"emblem_pack.xml/corner_c_25.png", 1 ,0, 0,
        10, 0.5)

    self.mainPanel:addEmblem(1,"emblem_pack.xml/corner_b_12.png", 3,3, 33,
        -32, 0.75)

    self.mainPanel:addEmblem(1,"emblem_pack.xml/corner_b_06.png", 12,12, 33,
        -32, 0.75)

    self.sides["skill_des"] = L_compositeObject:new()
    self.sides["skill_des"]:init(self.renderContextHost, self.posX, self.posY,
        self.width * 0.99, self.height * 0.99 , 0, 10)
    self.sides["skill_des"]:addPanel("Basic_border", 0.25)
    self.sides["skill_des"]:showPanelBG(true)
    self.sides["skill_des"]:addEmblem(1,"emblem_pack.xml/corner_b_05.png", 15,15, 0,
        10, 0.0)
    self.sides["skill_des"]:addLine(0,  100, self.width * 0.5, 40)
    self.sides["skill_des"]:setVisible(false)


    
    self.sides["item_des"] = L_compositeObject:new()
    self.sides["item_des"]:init(self.renderContextHost, self.posX, self.posY,
        self.width * 0.99, self.height * 0.99 , 0, 10)
    self.sides["item_des"]:addPanel("Basic_border", 0.25)
    self.sides["item_des"]:showPanelBG(true)
    self.sides["item_des"]:addEmblem(1,"emblem_pack.xml/corner_b_05.png", 15,15, 0,
        10, 0.0)
    self.sides["item_des"]:addLine(0,  150, self.width * 0.5, 40)
    -- self.sides["item_des"]:setVisible(false)

end

-- function Combat_dock_right_panel:updateInfo(side,  )

-- end



return Combat_dock_right_panel