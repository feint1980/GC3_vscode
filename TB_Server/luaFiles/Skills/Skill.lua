




---TGUI text tag 
Tag = {}
Tag.color_red = "<color=#ff1200>"
Tag.color_orange = "<color=#FF5D00>"
Tag.color_green = "<color=#00ff1d>"
Tag.color_blue = "<color=#2B83FF>"
Tag.color_close = "</color>"
Tag.italic_open = "<i>"
Tag.italic_close = "</i>"

Tag.color_TB_VIT = "<color=#FF0800>"
Tag.color_TB_STR = "<color=#FB8C00>"
Tag.color_TB_DEX = "<color=#50FF0A>"
Tag.color_TB_AGI = "<color=#00FFED>"
Tag.color_TB_INT = "<color=#FF00DC>"
Tag.color_TB_WIS = "<color=#0094FF>"
Tag.color_TB_title = "<color=#ADB5FF>"

Tag.icon_soul = "<img=\"./Assets/TB_GUI/icons/soul.png\">"

Tag.iRed = Tag.italic_open .. Tag.color_red
Tag.iOrange = Tag.italic_open .. Tag.color_orange
Tag.iGreen = Tag.italic_open .. Tag.color_green
Tag.iClose = Tag.color_close .. Tag.italic_close

---@class Skill
Skill = {
    name = "Skill",
    description = "Skill Description",
    effectTxt = "Effect",
    quoteTxt = "Quote",
    iconPath =  "./Assets/TB_GUI/faces/missing.png",
    -- special properties
    properties = {}
}

function Skill:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

