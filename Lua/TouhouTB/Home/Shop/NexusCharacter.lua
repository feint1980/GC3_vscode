package.path = package.path .. ';../../Lua/system/GUI/?/?.lua;' .. ';../../Lua/system/GUI/widgets/?.lua;' .. ';../../Lua/TouhouTB/Home/?.lua;'

require "TGUI_Label"
require "TGUI_Panel"
require "TGUI_RTLabel" 
require "TGUI_Editbox"
require "TGUI_Picture"
require "TGUI_TabContainer"
require "TGUI_ScrollablePanel"
require "homeGlobal"
require "OwnedCharacterPanel"

---@class (exact) CharacterNexus
---@field parentPanel pointer instance of Panel
---@field mainPanel Panel instance of Panel
---@field ownedCharacterPanels table
---@field t_characters table
---@field itemCount number
CharacterNexus = {
    ---@type Panel 
    parentPanel = nil,
    ---@type Panel
    mainPanel = nil,
    ---@type table of OwnedCharacterPanel
    ownedCharacterPanels = {},
    t_characters = {},
    itemCount = 0
}

function CharacterNexus:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    setmetatable(self.ownedCharacterPanels, self.ownedCharacterPanels)
    return o
end

function CharacterNexus:init( GUI_host,parent )
    self.parentPanel = parent
    self.mainPanel = ScrollablePanel:new()
    self.mainPanel:init(GUI_host,0,0,0,0,self.parentPanel)
    self.mainPanel:setAlignment(0.5,0.5)
    self.mainPanel:setPosStr("25%","50%")
    self.mainPanel:setSizeStr("48%","99%")

end

local displayOwnedCharacterTable = {}

function CharacterNexus:updateCharacters()
    print("update character called ")
    for k,v in pairs(Owned_CharacterTable) do
        print(k )
    end
    print("data check done ")

    for k,v in pairs(displayOwnedCharacterTable) do
        table.remove(displayOwnedCharacterTable,k)
    end
    displayOwnedCharacterTable = {}
    self.itemCount = 0

    for k,v in pairs(Owned_CharacterTable) do
        table.insert(displayOwnedCharacterTable,v)
    end

    table.sort(displayOwnedCharacterTable, function(a,b) return a.ID < b.ID end)

    -- for k,v in pairs(displayOwnedCharacterTable) do
    --     print(v.ID )
    -- end

    -- for k,v in pairs(Owned_CharacterPannels) do
    --     table.remove(Owned_CharacterPannels,k)
    -- end
    -- Owned_CharacterPannels = {}

    for k,v in pairs(displayOwnedCharacterTable) do
        self:addCharPanel(Home_GUIScriptingPtr,v.ID)
    end

    print("done update")
end

function CharacterNexus:addCharPanel(GUI_host,characterID)

    print("addCharPanel " .. characterID)
    local panelHeight = 80
    local pWidth, pHeight = self.mainPanel:getSize()

    if  Owned_CharacterPannels[characterID] == nil then
        Owned_CharacterPannels[characterID]= OwnedCharacterPanel:new()
    end
    print("Owned_CharacterPannels[characterID].init")
    Owned_CharacterPannels[characterID]:init(GUI_host,self.mainPanel,0,self.itemCount * panelHeight,pWidth,panelHeight ,characterID)
    self.itemCount = self.itemCount + 1
end