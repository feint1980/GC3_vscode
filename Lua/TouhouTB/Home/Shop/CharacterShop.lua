package.path = package.path .. ';../../Lua/system/GUI/?/?.lua;' .. ';../../Lua/system/GUI/widgets/?.lua;' .. ';../../Lua/TouhouTB/Home/?.lua;'

require "TGUI_Label"
require "TGUI_Panel"
require "TGUI_RTLabel" 
require "TGUI_Editbox"
require "TGUI_Picture"
require "TGUI_TabContainer"
require "TGUI_ScrollablePanel"
require "homeGlobal"
require "CharacterPanel"
require "CharacterDetailPanel"

---@class (exact) CharacterShop
---@field mainPanel pointer instance of Panel
---@field charactersPanel ScrollablePanel
---@field characterDetailPanel CharacterDetailPanel
---@field characterPanels table 
---@field t_characters table
CharacterShop = {
    ---@type pointer
    mainPanel = nil,
    ---@type ScrollablePanel
    charactersPanel = nil,
    ---@type CharacterDetailPanel
    characterDetailPanel = nil,
    ---@type table of CharacterPanel
    characterPanels = {},

    ---@type table
    t_characters = {}
}

---@Description create new instance of CharacterShop
---@return CharacterShop
function CharacterShop:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

---@Description init CharacterShop
---@param GUI_host pointer instance of TGUIScriptingManager
---@param posX number x position
---@param posY number y position
---@param width number width
---@param height number height
---@param parent pointer instance of parent
function CharacterShop:init(GUI_host, posX, posY,
    width, height, parent)
    print("init called ")
    self.mainPanel = parent
    if self.mainPanel == nil then
        print(" mainPanel is nil")
    else
        print(" mainPanel is not nil")
    end
    self.charactersPanel = ScrollablePanel:new()
    self.charactersPanel:init(GUI_host,posX,posY,width,height, self.mainPanel)
    self.charactersPanel:setAlignment(0.5,0.5)
    self.charactersPanel:setPosStr("50%","50%")
    self.charactersPanel:setSizeStr("95%","90%")
    local refreshButton= Label:new()
    refreshButton:init(GUI_host,"Refresh",100,0,self.mainPanel)
    refreshButton:setPosStr("95%","95%")
    refreshButton:setAlignment(TextAlginment.Center)
    refreshButton:setHoverable(0,255,0,255,255,255,255,255)
    refreshButton:setOnClickCallback(function()
        self:requestCharacterList(Home_ClientScriptingPtr)
    end)

    self.characterDetailPanel = CharacterDetailPanel:new()
    self.characterDetailPanel:init(GUI_host,self.mainPanel)

    self:requestCharacterList(Home_ClientScriptingPtr)
end

local function round(num, numDecimalPlaces, displayNum)
    displayNum = displayNum or 2
    local mult = 10^(numDecimalPlaces or 0)
    return string.format("%.".. tostring(displayNum) .. "f",  math.floor(num * mult + 0.5) / mult)
end

local function num_2_str(num, displayNum)
    displayNum = displayNum or 2
    return string.format("%.".. tostring(displayNum) .. "f", num)
end

function CharacterShop:addCharPanel(GUI_host,x,y,width,height,panelPath,name,price)
    self.characterPanels[name] = CharacterPanel:new()
    self.characterPanels[name]:init(GUI_host,self.charactersPanel.ptr,x,y,width,height,panelPath,name,price)

    CharacterDetailPanelVal = _G.CharacterDetailPanelVal
    self.characterPanels[name].panel:setOnClickCallback(function()

        print("Click called")
        self.characterDetailPanel:setVal(CharacterDetailPanelVal.str,  tostring(Shop_CharacterTable[name].Strength))
        self.characterDetailPanel:setVal(CharacterDetailPanelVal.vit,  tostring(Shop_CharacterTable[name].Vitality))
        self.characterDetailPanel:setVal(CharacterDetailPanelVal.dex,  tostring(Shop_CharacterTable[name].Dexterity))
        self.characterDetailPanel:setVal(CharacterDetailPanelVal.agi,  tostring(Shop_CharacterTable[name].Agility))
        self.characterDetailPanel:setVal(CharacterDetailPanelVal.int,  tostring(Shop_CharacterTable[name].Intelligence))
        self.characterDetailPanel:setVal(CharacterDetailPanelVal.wis,  tostring(Shop_CharacterTable[name].Wisdom))
        self.characterDetailPanel:setVal(CharacterDetailPanelVal.hp,  round(Shop_CharacterTable[name]:getHP(),1,1))
        self.characterDetailPanel:setVal(CharacterDetailPanelVal.mana,  round(Shop_CharacterTable[name]:getMana(),1,1))
        self.characterDetailPanel:setVal(CharacterDetailPanelVal.physicDmg,  round(Shop_CharacterTable[name]:getPhysicDmg(),2))
        self.characterDetailPanel:setVal(CharacterDetailPanelVal.physicDef,  round(Shop_CharacterTable[name]:getPhysicDef(),2))
        self.characterDetailPanel:setVal(CharacterDetailPanelVal.magicDmg,  round(Shop_CharacterTable[name]:getMagicDmg(),2))
        self.characterDetailPanel:setVal(CharacterDetailPanelVal.magicDef,  round(Shop_CharacterTable[name]:getMagicDef(),2))
        self.characterDetailPanel:setVal(CharacterDetailPanelVal.accurate,  round(Shop_CharacterTable[name]:getAccurate(),3,2))
        self.characterDetailPanel:setVal(CharacterDetailPanelVal.evadeChance,  round(Shop_CharacterTable[name]:getEvadeChance(),3,2))
        self.characterDetailPanel:setVal(CharacterDetailPanelVal.critChance,  round(Shop_CharacterTable[name]:getCritChance(),3,2))
        self.characterDetailPanel:setVal(CharacterDetailPanelVal.speed,  round(Shop_CharacterTable[name]:getSpeed(),2,1))
        -- self.characterDetailPanel:setVal(CharacterDetailPanelVal.hpScale,  tostring(Shop_CharacterTable[name].hpScale))
        -- self.characterDetailPanel:setVal(CharacterDetailPanelVal.manaScale,  tostring(Shop_CharacterTable[name].manaScale))
        -- self.characterDetailPanel:setVal(CharacterDetailPanelVal.physicDmgScale,  round(Shop_CharacterTable[name].physicDmgScale,4))
        -- self.characterDetailPanel:setVal(CharacterDetailPanelVal.physicDefScale,  round(Shop_CharacterTable[name].physicDefScale,4))
        -- self.characterDetailPanel:setVal(CharacterDetailPanelVal.magicDmgScale,  round(Shop_CharacterTable[name].magicDmgScale,4))
        -- self.characterDetailPanel:setVal(CharacterDetailPanelVal.magicDefScale,  round(Shop_CharacterTable[name].magicDefScale,4))
        -- self.characterDetailPanel:setVal(CharacterDetailPanelVal.accurateScale,  round(Shop_CharacterTable[name].accurateScale,4))
        -- self.characterDetailPanel:setVal(CharacterDetailPanelVal.evadeChanceScale,  round(Shop_CharacterTable[name].evadeChanceScale,4))
        self.characterDetailPanel:setVal(CharacterDetailPanelVal.deathDoorSurviveChance,  num_2_str(Shop_CharacterTable[name]:getDeathDoorSurviveChance(),3))

        self.characterDetailPanel:setVal(CharacterDetailPanelVal.name,  Shop_CharacterTable[name].lastName .. " " .. Shop_CharacterTable[name].name)
        self.characterDetailPanel:setVal(CharacterDetailPanelVal.title,
        Tag.color_TB_title .. Shop_CharacterTable[name].title .. Tag.color_close)

        self.characterDetailPanel:setVal(CharacterDetailPanelVal.panelPath,  Shop_CharacterTable[name].panelPath)
        self.characterDetailPanel:setVisible(true)
    end)
end

---@Description request character list
---@param clientSideHost pointer instance of ClientScriptingManager
function CharacterShop:requestCharacterList(clientSideHost)
    self.charactersPanel:clearItems()
    Client_SendData(clientSideHost,"|REQUEST_CHARACTERLIST|")
    -- Client_send
end