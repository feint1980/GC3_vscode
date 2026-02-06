package.path = package.path .. ';../../Lua/system/GUI/?/?.lua;' .. ';../../Lua/system/GUI/widgets/?.lua;' .. ';../../Lua/TouhouTB/Home/?.lua;'

require "TGUI_Label"
require "TGUI_Panel"
require "TGUI_RTLabel" 
require "TGUI_Editbox"
require "TGUI_Picture"
require "TGUI_TabContainer"
require "TGUI_ScrollablePanel"
require "lobby_global"
require "Prompt"

LobbyMenuPanels = _G.LobbyMenuPanels

-- ---@type Panel
-- Lobby_Formation_Panel = nil

-- ---@type number
-- Lobby_Formation_Number = 0


---@class Lobby_Formation_Selector
Lobby_Formation_Selector = {
    lobbyHost = nil,
    lobbyGUIHost = nil,
    lobbyNetworkHost = nil,

    parentPanel = nil,
    mainPanel = nil,
    ---@type table
    formationList = {},
    tIndex = 1
}

function Lobby_Formation_Selector:new(o)
    o = o or {}
    o.formationList = {}
    setmetatable(o, self)
    setmetatable(o.formationList, self)
    self.__index = self
    return o
end

function Lobby_Formation_Selector:init(tLobbyHost, tLobbyGUIHost, tLobbyNetworkHost,parentPanel, index, showOnInit)
    self.lobbyHost = tLobbyHost
    self.lobbyGUIHost = tLobbyGUIHost
    self.lobbyNetworkHost = tLobbyNetworkHost
    self.parentPanel = parentPanel --- (ptr)

    if self.mainPanel == nil then
        self.mainPanel = Panel:new()
    end
    self.mainPanel:init(tLobbyGUIHost,0,0,0,0,parentPanel)
    self.mainPanel:setSizeStr("33%","30%")
    self.mainPanel:setAlignment(0.5,0.5)

    self:setIndex(index)

    print("Lobby formation selector initialized")
    self.mainPanel:hideWithEffect(PanelShowType.Fade,1)
    -- if showOnInit == true then
    --     self.mainPanel:showWithEffect(PanelShowType.Fade,1)
    -- else 
    --     self.mainPanel:hideWithEffect(PanelShowType.Fade,1)
    -- end

    -- self.mainPanel:hideWithEffect(PanelShowType.Fade,250)
end

function Lobby_Formation_Selector:setIndex(index)
    if index < 1 then 
        index = 1
    end
    if index > 2 then
        index = 2
    end
    self.tIndex = index
    self:onIndexChangeUpdate()
end


function Lobby_Formation_Selector:onIndexChangeUpdate()
    local xPos = 26
    local additionPos = 50 * (self.tIndex -1) 
    
    local yPos = 50

    if self.mainPanel ~= nil then
        self.mainPanel:setPosStr(tostring(xPos + additionPos) .. "%",tostring(yPos) .. "%")
    end

end

function Lobby_Formation_Selector:setVisible(value)
    if self.mainPanel ~= nil then
        if value == true then
            self.mainPanel:showWithEffect(PanelShowType.Fade,250)
        else
            self.mainPanel:hideWithEffect(PanelShowType.Fade,250)
        end
    end
end