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

---@class (exact) CharacterShop
---@field mainPanel pointer instance of Panel
---@field charactersPanel ScrollablePanel
---@field characterDetailPanel ScrollablePanel
---@field t_characters table
CharacterShop = {
    ---@type pointer
    mainPanel = nil,
    ---@type ScrollablePanel
    charactersPanel = nil,
    ---@type ScrollablePanel
    characterDetailPanel = nil,

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
    self.charactersPanel:setAligment(0.5,0.5)
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

    self.characterDetailPanel = ScrollablePanel:new()
    self.characterDetailPanel:init(GUI_host,posX,posY,width,height, self.mainPanel)
    self.characterDetailPanel:setAligment(0.5,0.5)
    self.characterDetailPanel:setPosStr("50%","50%")
    self.characterDetailPanel:setSizeStr("95%","90%")
    self.characterDetailPanel:setVisible(false)

    self:requestCharacterList(Home_ClientScriptingPtr)
end

function CharacterShop:addCharPanel(GUI_host,x,y,width,height,panelPath,name,price)
    self.charactersPanel[name] = CharacterPanel:new()
    self.charactersPanel[name]:init(GUI_host,self.charactersPanel.ptr,x,y,width,height,panelPath,name,price)
end

---@Description request character list
---@param clientSideHost pointer instance of ClientScriptingManager
function CharacterShop:requestCharacterList(clientSideHost)
    self.charactersPanel:clearItems()
    Client_SendData(clientSideHost,"|REQUEST_CHARACTERLIST|")
    -- Client_send
end