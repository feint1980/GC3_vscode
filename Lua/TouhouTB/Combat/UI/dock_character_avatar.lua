package.path = package.path .. ';../../Lua/system/objects/?.lua;'

require "compositeObject"

Dock_character_avatar = {
    ---@type pointer? F_LuaRenderContext
    renderContextHost = nil,

    ptr = nil,
    avatarObject = nil,
    posX = 0,
    posY = 0,
    mWidth = 0,
    mHeight = 0,

}

function Dock_character_avatar:new()
    local o = {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function Dock_character_avatar:init(tRenderContextHost, tPosX, tPosY, tWidth, tHeight)
    self.renderContextHost = tRenderContextHost
    self.posX = tPosX
    self.posY = tPosY
    self.mWidth = tWidth
    self.mHeight = tHeight

    self.ptr = L_compositeObject:new()
    self.ptr:init(tRenderContextHost, self.posX, self.posY, self.mWidth, self.mHeight,0,6)

    self.ptr:addPanel("Basic_border", 0.4)
    self.ptr:addEmblem(1,"emblem_pack.xml/corner_b_01.png", 3,0, 8,
    -15, 0.4)

    self.avatarObject = self.ptr:addSprite("avatars.xml/Reimu.png", 0,0, .39, .39 ,255,255,255,255,0,6)

    self.ptr:addText("test text",100, -100,3,1.0, 255,255, 255,255,0 )

end

function Dock_character_avatar:changeAvatar(tAvatarName)

    -- self.avatarObject:setSprite(tAvatarName)
end