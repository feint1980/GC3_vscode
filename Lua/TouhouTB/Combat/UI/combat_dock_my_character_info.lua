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

    lineDock = nil,

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

    print("init called")
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

    self.lineDock = L_compositeObject:new()

    self.lineDock:init(self.renderContextHost,
    -posX , -posY,width ,height, 0,12)
    self.lineDock:addPanel("Basic_border",0.25)

    self.mainDock:showPanelBG(true)
    self.mainDock:setPanelBGColor(8,10,15,255)
    self.mainDock:setPanelBGScale(0.95)

    local avatarWidth = 140 -- square 
    local textLineWidth = 190

    local diff = (width - avatarWidth ) - (width * 0.5)
    local linePosX = (width * 0.5) + (diff * 0.5) - (textLineWidth * 0.5)

    -- decorative lines

    self.lineDock:addLine(linePosX - 25 , 120 , textLineWidth, 66)

    self.lineDock:addLine(linePosX - 125 , 20 , 300, 66)

    -- separator under the name/level block
    self.lineDock:addLine(linePosX - 25 , 95 , textLineWidth, 50)

    -- separator under HP row
    self.lineDock:addLine(linePosX - 25 , 70 , textLineWidth, 40)

    -- separator under MP row
    self.lineDock:addLine(linePosX - 25 , 50 , textLineWidth, 40)

    -- short accent line near avatar bottom
    self.lineDock:addLine(linePosX - 125 , -10 , 120, 30)

    --- internal update
    self.posX = posX
    self.posY = posY
    self.mWidth = width
    self.mHeight = height

    -- character avatar
    self.currentCharacterAvatar = Dock_character_avatar:new()
    self.currentCharacterAvatar:init(renderHost, (-self.posX) - (width * 0.5) + avatarWidth * 0.5  , (-self.posY) + (height * 0.5) - avatarWidth * 0.5, avatarWidth, avatarWidth)


    print("init end ")
end