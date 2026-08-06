package.path = package.path .. ';../../Lua/system/objects/?.lua;' .. ';../../Lua/TouhouTB/Combat/UI/?.lua;'

require "compositeObject"
require "dock_description_panel"


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

    self.sides["skill_des"] = Dock_description_panel:new()
    self.sides["skill_des"]:init(self.renderContextHost, self.posX, self.posY,
        self.width * 0.99, self.height * 0.99 , 0, 10)
    self.sides["skill_des"]:getPanel():addPanel("Basic_border", 0.25)
    self.sides["skill_des"]:getPanel():showPanelBG(true)
    self.sides["skill_des"]:getPanel():addEmblem(1,"emblem_pack.xml/corner_b_05.png", 15,15, 0,
        10, 0.0)
    self.sides["skill_des"]:getPanel():addLine(0,  140, self.width * 0.5, 40)
    -- self.sides["skill_des"]:getPanel():setVisible(false)

    self.sides["skill_des"]:addTextInstance("skill_name", "Skill's name", 0, 150 , 3, 0.75, 255,255,255,255)

    self.sides["skill_des"]:addTextInstance("skill_description", "Skill's description", -200, 90 , 1, 0.55, 255,255,255,255)

    self.sides["skill_des"]:addTextInstance("skill_cost", "Skill's cost", 200, -170 , 2, 0.65, 255,255,255,255)

    ------ Item description

    self.sides["item_des"] = Dock_description_panel:new()
    self.sides["item_des"]:init(self.renderContextHost, self.posX, self.posY,
        self.width * 0.99, self.height * 0.99 , 0, 10)
    self.sides["item_des"]:getPanel():addPanel("Basic_border", 0.25)
    self.sides["item_des"]:getPanel():showPanelBG(true)
    self.sides["item_des"]:getPanel():addEmblem(1,"emblem_pack.xml/corner_b_05.png", 15,15, 0,
        10, 0.0)
    self.sides["item_des"]:getPanel():addLine(0,  150, self.width * 0.5, 40)

    self.sides["item_des"]:addTextInstance("item_name", "Item's name", 0, 150 , 3, 0.75, 255,255,255,255)

    self.sides["item_des"]:addTextInstance("item_description", "Item's \n description", 0, 50 , 3, 0.55, 255,255,255,255)

    self.sides["item_des"]:addTextInstance("item_cost", "Item's \n cost", 100, -170 , 3, 0.55, 255,255,255,255)

    self.sides["item_des"]:getPanel():setVisible(false)

end

function Combat_dock_right_panel:showSide(sideName, show)
    if self.sides[sideName] == nil then
        return
    end
    self.sides[sideName]:getPanel():setVisible(show)
end

function Combat_dock_right_panel:getSide(sideName)
    if(self.sides[sideName] == nil) then
        print("side " .. sideName .. " not found")
        return nil
    end
    -- print("returned side " .. sideName) 
    return self.sides[sideName]
end


return Combat_dock_right_panel