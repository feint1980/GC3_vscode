package.path = package.path .. ';../../Lua/system/objects/?.lua;' .. ';../../Lua/TouhouTB/Combat/UI/?.lua;'


require "compositeObject"
require "dock_character_avatar"

Combat_dock_my_character_info = {
    renderContextHost = nil,
    mainDock = nil,
    windowWidth = 0,
    windowHeight = 0,
    posX = 0,
    posY = 0,
    mWidth = 0,
    mHeight = 0,

    -- avatar
    currentCharacterAvatar = nil,

    -- texts
    characterNameText = nil,
    characterLevelText = nil,
    
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
    self.mainDock:addEmblem(0,"emblem_pack.xml/corner_c_24.png", 1,0, 0, 25,0.5)
    self.mainDock:addEmblem(1,"emblem_pack.xml/corner_b_01.png", 3,0, 8,
    -15, 0.75)

    self.mainDock:showPanelBG(true)
    self.mainDock:setPanelBGColor(8,10,15,255)
    self.mainDock:setPanelBGScale(0.95)

    local avatarWidth = 140 -- square 
    local textLineWidth = 205

    local diff = (width - avatarWidth ) - (width * 0.5)
    local linePosX = (width * 0.5) + (diff * 0.5) - (textLineWidth * 0.5)




    -- decorative lines
    
    self.mainDock:addLine(linePosX , 120 , textLineWidth, 66)

    --- 


    --- internal update
    self.posX = posX
    self.posY = posY
    self.mWidth = width
    self.mHeight = height

    -- character avatar
    self.currentCharacterAvatar = Dock_character_avatar:new()
    self.currentCharacterAvatar:init(renderHost, (-self.posX) - (width * 0.5) + avatarWidth * 0.5  , (-self.posY) + (height * 0.5) - avatarWidth * 0.5, avatarWidth, avatarWidth)


end