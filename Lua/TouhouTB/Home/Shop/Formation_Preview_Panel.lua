package.path = package.path .. ';../../Lua/system/GUI/?/?.lua;' .. ';../../Lua/system/GUI/widgets/?.lua;' .. ';../../Lua/TouhouTB/Home/?.lua;'

require "TGUI_Label"
require "TGUI_Panel"
require "TGUI_RTLabel" 
require "TGUI_Editbox"
require "TGUI_Picture"
require "TGUI_TabContainer"
require "TGUI_ScrollablePanel"
require "homeGlobal"
require "Formation_CharInfo"
require "Prompt"

---@class FormationPreviewPanel
FormationPreviewPanel ={
    guiHost = nil,
    mainPanel = nil,
    ---@type table of Picture
    characterPics = {},
    ---@type Label
    formationName = nil,

    ---@type table of Formation_CharInfo
    t_charactersInfo = {},

    tIndex = 0,
    -----@type Label
    -- createFormationBtn = nil,
    isEmpty = true,
    onclickCallBack = nil
}

function FormationPreviewPanel:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function FormationPreviewPanel:init(GUI_host,parentPanel, index)
    self.guiHost = GUI_host
    self.mainPanel = Panel:new()
    self.mainPanel:init(GUI_host,0,0,0,0,parentPanel)
    self.mainPanel:setAlignment(0.5,0.5)

    self.tIndex = index

    local strPosX = ((self.tIndex - 1) * 25) + 12.5
    local strPosXStr = tostring(strPosX) .. "%"
    self.mainPanel:setPosStr(strPosXStr,"50%")
    self.mainPanel:setSizeStr("24%","99%")

    self.mainPanel:setHoverable(0,255,0,255,255,255,255,255)

    self.mainPanel:setOnClickCallback(function()
        self:onClickCallBack()
    end)

    self.formationName = Label:new()
    self.formationName:init(GUI_host,"Create",0,0,self.mainPanel.ptr)
    self.formationName:setPosStr("50%","45%")
    self.formationName:setAlignment(TextAlginment.Center)
    self.formationName:setScale(1.)

    -- local newFormationName = "New_Formation_" .. self.tIndex


    -- Prompt_UI_Table[newFormationName]:show(false)

end

function FormationPreviewPanel:createNewFormation(GUI_host, characterIDTable)
end

function FormationPreviewPanel:update(accountID, formationName)
    self.formationName:setText(formationName)
    self.isEmpty = false
end

function FormationPreviewPanel:addCharacter(GUI_host, characterID, col,row)

end

function FormationPreviewPanel:onClickCallBack()

    Formation_Selection = self.tIndex

    if self.isEmpty == false then
        print("suppose to select ")
    else
        Prompt_UI_Table["New_Formation"]:show(true)
    end
end