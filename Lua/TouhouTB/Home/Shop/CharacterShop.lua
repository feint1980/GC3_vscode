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

---@Description set CharacterDetailPanel visible
---@param value boolean
function CharacterShop:setDetailVisible(value)
    if self.characterDetailPanel ~= nil then
        self.characterDetailPanel:setVisible(value)
    end
end

---@Description init CharacterShop
---@param GUI_host pointer instance of TGUIScriptingManager
---@param posX number x position
---@param posY number y position
---@param width number width
---@param height number height
---@param parent pointer instance of parent
function CharacterShop:init(GUI_host, posX, posY,
    width, height, parent,clientHost, ip)
    -- print("init called ")
    self.mainPanel = parent
    -- if self.mainPanel == nil then
    --     print(" mainPanel is nil")
    -- else
    --     print(" mainPanel is not nil")
    -- end
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
    
    -- self.charactersPanel:setVisible(false)

    ControlHandler_reciever_remove(GUI_host,self.mainPanel)

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

---@Description add a character panel
---@param GUI_host pointer instance of TGUIScriptingManager
---@param x number x position
---@param y number y position
---@param width number width
---@param height number height
---@param panelPath string path to the image file
---@param characterID number id of the character
---@param price number price
---@param isOwn boolean if the character is owned
function CharacterShop:addCharPanel(GUI_host,x,y,width,height,
    panelPath,characterID,price,isOwn)
    
    self.characterPanels[characterID] = CharacterPanel:new()
    self.characterPanels[characterID]:init(GUI_host,self.charactersPanel.ptr,x,y,width,height,panelPath,Shop_CharacterTable[characterID].name,price,isOwn)

    CharacterDetailPanelVal = _G.CharacterDetailPanelVal
    self.characterPanels[characterID].panel:setOnClickCallback(function()

        print("Click called")
        self.characterDetailPanel:setVal(CharacterDetailPanelVal.str,  tostring(Shop_CharacterTable[characterID].Strength))
        self.characterDetailPanel:setVal(CharacterDetailPanelVal.vit,  tostring(Shop_CharacterTable[characterID].Vitality))
        self.characterDetailPanel:setVal(CharacterDetailPanelVal.dex,  tostring(Shop_CharacterTable[characterID].Dexterity))
        self.characterDetailPanel:setVal(CharacterDetailPanelVal.agi,  tostring(Shop_CharacterTable[characterID].Agility))
        self.characterDetailPanel:setVal(CharacterDetailPanelVal.int,  tostring(Shop_CharacterTable[characterID].Intelligence))
        self.characterDetailPanel:setVal(CharacterDetailPanelVal.wis,  tostring(Shop_CharacterTable[characterID].Wisdom))
        self.characterDetailPanel:setVal(CharacterDetailPanelVal.hp,  round(Shop_CharacterTable[characterID]:getHP(),1,1))
        self.characterDetailPanel:setVal(CharacterDetailPanelVal.mana,  round(Shop_CharacterTable[characterID]:getMana(),1,1))
        self.characterDetailPanel:setVal(CharacterDetailPanelVal.physicDmg,  round(Shop_CharacterTable[characterID]:getPhysicDmg(),2))
        self.characterDetailPanel:setVal(CharacterDetailPanelVal.physicDef,  round(Shop_CharacterTable[characterID]:getPhysicDef(),2))
        self.characterDetailPanel:setVal(CharacterDetailPanelVal.magicDmg,  round(Shop_CharacterTable[characterID]:getMagicDmg(),2))
        self.characterDetailPanel:setVal(CharacterDetailPanelVal.magicDef,  round(Shop_CharacterTable[characterID]:getMagicDef(),2))
        self.characterDetailPanel:setVal(CharacterDetailPanelVal.accurate,  round(Shop_CharacterTable[characterID]:getAccurate(),3,2))
        self.characterDetailPanel:setVal(CharacterDetailPanelVal.evadeChance,  round(Shop_CharacterTable[characterID]:getEvadeChance(),3,2))
        self.characterDetailPanel:setVal(CharacterDetailPanelVal.critChance,  round(Shop_CharacterTable[characterID]:getCritChance(),3,2))
        self.characterDetailPanel:setVal(CharacterDetailPanelVal.speed,  round(Shop_CharacterTable[characterID]:getSpeed(),2,1))
        -- self.characterDetailPanel:setVal(CharacterDetailPanelVal.hpScale,  tostring(Shop_CharacterTable[characterID].hpScale))
        -- self.characterDetailPanel:setVal(CharacterDetailPanelVal.manaScale,  tostring(Shop_CharacterTable[characterID].manaScale))
        -- self.characterDetailPanel:setVal(CharacterDetailPanelVal.physicDmgScale,  round(Shop_CharacterTable[characterID].physicDmgScale,4))
        -- self.characterDetailPanel:setVal(CharacterDetailPanelVal.physicDefScale,  round(Shop_CharacterTable[characterID].physicDefScale,4))
        -- self.characterDetailPanel:setVal(CharacterDetailPanelVal.magicDmgScale,  round(Shop_CharacterTable[characterID].magicDmgScale,4))
        -- self.characterDetailPanel:setVal(CharacterDetailPanelVal.magicDefScale,  round(Shop_CharacterTable[characterID].magicDefScale,4))
        -- self.characterDetailPanel:setVal(CharacterDetailPanelVal.accurateScale,  round(Shop_CharacterTable[characterID].accurateScale,4))
        -- self.characterDetailPanel:setVal(CharacterDetailPanelVal.evadeChanceScale,  round(Shop_CharacterTable[characterID].evadeChanceScale,4))
        self.characterDetailPanel:setVal(CharacterDetailPanelVal.deathDoorSurviveChance,  num_2_str(Shop_CharacterTable[characterID]:getDeathDoorSurviveChance(),3))

        self.characterDetailPanel:setVal(CharacterDetailPanelVal.name,  Shop_CharacterTable[characterID].lastName .. " " .. Shop_CharacterTable[characterID].name)
        self.characterDetailPanel:setVal(CharacterDetailPanelVal.title,
        Tag.color_TB_title .. Shop_CharacterTable[characterID].title .. Tag.color_close)

        self.characterDetailPanel:setVal(CharacterDetailPanelVal.panelPath,  Shop_CharacterTable[characterID].panelPath)

        self.characterDetailPanel:setVal(CharacterDetailPanelVal.id,  Shop_CharacterTable[characterID].ID)
        self.characterDetailPanel:setVal(CharacterDetailPanelVal.isOwn,  isOwn)

        self.characterDetailPanel:setVisible(true)

    end)

    -- for k ,v in pairs(self.characterPanels) do
    --     JSON_Encode(v)
    -- end

end

---@Description request character list
---@param clientSideHost pointer instance of ClientScriptingManager
function CharacterShop:requestCharacterList(clientSideHost)
    -- self.charactersPanel:clearItems()
    -- local tResp = 0
    -- tResp = Client_SendData(clientSideHost,"|REQUEST_CHARACTERLIST|")
    -- while tResp == 0 do
    --     tResp = Client_SendData(clientSideHost,"|REQUEST_CHARACTERLIST|")
    -- end

    SendRequest(PacketChannel.ShopChannel,ShopResponse.ShopChracterInfo , {'get_character_shop_list'}, 5, 0.25)

end