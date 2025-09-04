package.path = package.path .. ';../../Lua/system/GUI/?/?.lua;' .. ';../../Lua/system/GUI/widgets/?.lua;' .. ';../../Lua/TouhouTB/Home/?.lua;'

require "TGUI_Label"
require "TGUI_Panel"
require "TGUI_RTLabel" 
require "TGUI_Editbox"
require "TGUI_Picture"
require "TGUI_TabContainer"
require "TGUI_ScrollablePanel"
require "homeGlobal"
require "Formation_Preview_Panel"
require "Prompt"
require "Formation_CharInfo"

---@class Formation_Edit
Formation_Edit = {
    ---@type Panel
    mainPanel = nil,
    ---@type table Picture
    characterPics = {},
    ---@type table Formation_CharacterInfo
}

---@Description create a new instance of Formation_Edit
---@param o? table
---@return Formation_Edit
function Formation_Edit:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function Formation_Edit:init(host,parentPanel)
    self.mainPanel = Panel:new()
    self.mainPanel:init(host,0,0,0,0,parentPanel)
    self.mainPanel:setAlignment(0.5,0.5)
    self.mainPanel:setSizeStr("99%","99%")
    self.mainPanel:setPosStr("50%","50%")
    
    local sizeX, sizeY = self.mainPanel:getSize()
    local picSize = (sizeY/ 3) * 0.9
    
    for i = 1, 3 do
        for j = 1, 3 do
            local pic = Picture:new()
            pic:init(host,"./Assets/TB_GUI/slide/plus.png", sizeX / 3 * (j - 1) + (picSize *0.5) , sizeY / 3  *( i - 1),0 ,0,self.mainPanel.ptr)
            
            -- table.insert(self.characterPics,pic)
            -- local strPosX = ((j - 1) * 25) + 12.5
            -- local strPosXStr = tostring(strPosX) .. "%"
            -- local strPosY = ((i - 1) * 25) + 12.5
            -- local strPosYStr = tostring(strPosY) .. "%"
            -- pic:setPosStr(strPosXStr,strPosYStr)
            
            pic:setSize(picSize,picSize)
        end
    end
end