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
require "Formation_Slot"


---@class Formation_Edit
Formation_Edit = {
    ---@type Panel
    mainPanel = nil,
    ---@type table Formation_Slot
    formationSlot = {},
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
    local picSize = (sizeY/ 3) * 0.85

    for i = 1, 3 do
        self.formationSlot[i] = {}
        for j = 1, 3 do
            self.formationSlot[i][j] = Formation_Slot:new()
            self.formationSlot[i][j]:init(host,self.mainPanel.ptr,sizeX / 3 * (j - 1) + (picSize *0.9) , sizeY / 3  *( i - 1) + (picSize *0.55) ,picSize,picSize,"./Assets/TB_GUI/slide/plus.png")
        end
    end
end

function Formation_Edit:resetSelections()
    for i = 1, 3 do
        for j = 1, 3 do
            self.formationSlot[i][j]:setSelected(false)
        end
    end
end