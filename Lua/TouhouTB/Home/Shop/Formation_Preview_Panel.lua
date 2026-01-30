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
require "clientGlobal"

---@class FormationPreviewPanel
FormationPreviewPanel ={
    guiHost = nil,
    mainPanel = nil,
    ---@type table of Picture
    characterPics = {},
    ---@type Label
    formationLabel = nil,
    formationName = "",

    ---@type table of Formation_CharInfo
    formationCharacters = {},

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

    self.formationLabel = Label:new()
    self.formationLabel:init(GUI_host,"Create",0,0,self.mainPanel.ptr)
    self.formationLabel:setPosStr("50%","25%")
    self.formationLabel:setAlignment(TextAlginment.Center)
    self.formationLabel:setScale(1.)

    for i = 1, 4 do 
        print("init pic index " .. i)
        self.characterPics[i] = Picture:new()
        self.characterPics[i]:init(GUI_host,"Assets/TB_GUI/faces/missing.png",0,0,50,50,self.mainPanel.ptr)
        local pos = ((i - 1) * 25) + 2.5
        self.characterPics[i]:setPosStr( tostring(pos) .. "%","50%")

        -- self.characterPics[i]:setAlignment(0.5,0.5)
    end

end

function FormationPreviewPanel:createNewFormation(GUI_host, characterIDTable)
end

function FormationPreviewPanel:update(accountID, formationName)
    self.formationName =  formationName
    self.formationLabel:setText(self.formationName)
    self.isEmpty = false
end

function FormationPreviewPanel:addCharacter(GUI_host, characterID, col,row)

end

function FormationPreviewPanel:onClickCallBack()

    Formation_Selection = self.tIndex

    if self.isEmpty == false then
        -- Formation_Edit_Panel:setVisible(true)
        _G.Formation_Edit_Instance:setVisible(true)
        print("suppose to selected " .. self.formationName)

        _G.Formation_Edit_Instance:loadFormation(self.formationCharacters)

    else
        Prompt_UI_Table["New_Formation"]:show(true)
        _G.Formation_Edit_Instance:setVisible(false)
    end
end

function FormationPreviewPanel:reset()
    self.formationName = ""
    self.formationLabel:setText("Create")
    self.isEmpty = true
end

function FormationPreviewPanel:setInfo(t_formationCharacters)
    self.formationCharacters = t_formationCharacters

    if self.formationCharacters == nil then
        -- print("FormationPreviewPanel:setInfo t_formationCharacters is nil")
        return
    end
    for k,v in pairs(self.formationCharacters) do
        print("k " .. k )
        print("row " .. v.row)
        print("col " .. v.col)
        print("index " .. v.tIndex)
        if self.characterPics[v.tIndex] ~= nil then
            self.characterPics[v.tIndex]:setPicturePath(Shop_CharacterTable[v.characterID].portraitPath)
        
        else 
            print("self.characterPics[" .. v.tIndex .. "] is nil ")
        end
        print("characterID " .. v.characterID)
    end

    -- for i = 1 , #self.formationCharacters do
    --     print("index " .. i .. self.formationCharacters[i].characterID)
    -- end

end