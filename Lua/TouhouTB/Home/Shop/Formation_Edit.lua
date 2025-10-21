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
    ---@type pointer instance of TGUI_Panel
    parentPanel = nil,
    ---@type Panel
    mainPanel = nil,
    ---@type table Formation_Slot
    formationSlot = {},
    ---@type table Formation_CharacterInfo
    saveButton = nil,
    resetAllButton = nil,
    renameButton = nil,
    deleteButton = nil,
    formationCharacterCount  = 0

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

---@Description init the formation edit panel 
---@param host pointer instance of TGUIScriptingManager
---@param parentPanel pointer instance of Panel
function Formation_Edit:init(host,parentPanel)
    self.parentPanel = parentPanel
    self.mainPanel = Panel:new()
    self.mainPanel:init(host,0,0,0,0,parentPanel)

    self.mainPanel:setAlignment(0.5,0.5)
    self.mainPanel:setSizeStr("99%","99%")
    self.mainPanel:setPosStr("50%","50%")

    local sizeX, sizeY = self.mainPanel:getSize()
    local picSize = (sizeY/ 3) * 0.8

    for i = 1, 3 do
        self.formationSlot[i] = {}
        for j = 1, 3 do
            self.formationSlot[i][j] = Formation_Slot:new()
            self.formationSlot[i][j]:init(host,self.mainPanel.ptr,sizeX / 3 * (j - 1) + (picSize *0.9), -- x pos
            ((picSize * (i - 1)) + 10) + picSize * 0.5 , -- y pos
            picSize, -- width
            picSize, -- height
            "./Assets/TB_GUI/slide/plus.png", -- picture path
            i,j)
            
        end
    end

    --- button inits
    self.saveButton = Label:new()
    self.saveButton:init(host,"Save",0,0,self.mainPanel.ptr)
    self.saveButton:setPosStr("18%","90%")
    self.saveButton:setAlignment(TextAlginment.Center)
    self.saveButton:setHoverable(0,255,0,255,255,255,255,255)
    self.saveButton:setOnClickCallback(function()
        print("save hit")
        self:updateToServer()
    end)

    self.renameButton = Label:new()
    self.renameButton:init(host,"Rename",0,0,self.mainPanel.ptr)
    self.renameButton:setPosStr("38%","90%")
    self.renameButton:setAlignment(TextAlginment.Center)
    self.renameButton:setHoverable(0,255,0,255,255,255,255,255)
    self.renameButton:setOnClickCallback(function()
        Prompt_UI_Table["Formation_Rename"]:show(true)
    end)

    self.resetAllButton = Label:new()
    self.resetAllButton:init(host,"Reset",0,0,self.mainPanel.ptr)
    self.resetAllButton:setPosStr("58%","90%")
    self.resetAllButton:setAlignment(TextAlginment.Center)
    self.resetAllButton:setHoverable(0,255,0,255,255,255,255,255)
    self.resetAllButton:setOnClickCallback(function()
        print("reset all hit")
    end)

    self.deleteButton = Label:new()
    self.deleteButton:init(host,"Delete",0,0,self.mainPanel.ptr)
    self.deleteButton:setPosStr("78%","90%")
    self.deleteButton:setAlignment(TextAlginment.Center)
    self.deleteButton:setHoverable(0,255,0,255,255,255,255,255)
    self.deleteButton:setOnClickCallback(function()
        print("delete hit, selection " ..Formation_Selection)
        -- print(Formation_PreviewPanel[Formation_Selection].formationName)
        -- Formation_PreviewPanel[Formation_Selection]
        Prompt_UI_Table["Delete_Formation_Confirm"]:show(true)
    end)

    ControlHandler_reciever_remove(host,self.mainPanel.ptr)

    self.mainPanel:setVisible(false)

end

function Formation_Edit:resetSelections()
    for i = 1, 3 do
        for j = 1, 3 do
            self.formationSlot[i][j]:setSelected(false)
        end
    end
end

---@Description check if any slot is selected
---@return boolean 
function Formation_Edit:hasSelected()
    for i = 1, 3 do
        for j = 1, 3 do
            if self.formationSlot[i][j]:getIsSelected() == true then
                return true
            end
        end
    end
    return false
end

---@return Formation_Slot?
function Formation_Edit:getSelected()
    for i = 1, 3 do
        for j = 1, 3 do
            if self.formationSlot[i][j]:getIsSelected() == true then
                return self.formationSlot[i][j]
            end
        end
    end
    return nil
end

function Formation_Edit:updateList(characterID, row,col)
    print("updateList called " .. row .. " " .. col .. " value " .. characterID)
    --- reposition
    for i = 1, 3 do
        for j = 1, 3 do
            -- print("slot " .. self.formationSlot[i][j].picturePath)
            if self.formationSlot[i][j].assignedCharacterID == characterID then
                self.formationSlot[i][j]:removeAssignment()
                break
            end
        end
    end

    -- if #self.formationCharacterCount < 4 then
    --     self.formationCharacterCount  = self.formationCharacterCount + 1
        
    -- else
    --     Prompt_UI_Table["Formation_Noti"]:setMsg("Formation is full, clear a slot ! ")
    --     Prompt_UI_Table["Formation_Noti"]:show(true)
    --     return
    -- end
    self.formationSlot[row][col]:setCharacterID(characterID)
end

function Formation_Edit:loadFormation(formationCharacters)

    for i = 1, 3 do
        for j = 1, 3 do
            -- print("slot " .. self.formationSlot[i][j].picturePath)
                self.formationSlot[i][j]:setSelected(false)
                self.formationSlot[i][j]:removeAssignment()
        end
    end

    self.formationCharacters = {}

    for k,v in pairs(formationCharacters) do
        self.formationSlot[tonumber(v.row)][tonumber(v.col)]:setCharacterID(v.characterID)
    end
    -- print("loaded ")
end

function Formation_Edit:setVisible(value)
    self.mainPanel:setVisible(value)
end

function Formation_Edit:updateToServer()
    local updateBuffer = "#"
    local tSlotIndex = 1
    for i = 1, 3 do
        for j = 1, 3 do
            if self.formationSlot[i][j]:getIsAssigned() == true then                
                updateBuffer = updateBuffer .. self.formationSlot[i][j].assignedCharacterID .. "@" .. tSlotIndex .. "@" .. i .. "@" .. j .. "@"
                tSlotIndex = tSlotIndex + 1
            end
        end
    end
    updateBuffer = updateBuffer .. "#"
    Formation_Request_InfoUpdate(Formation_PreviewPanel[Formation_Selection].formationName, updateBuffer, tSlotIndex - 1)
end