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
require "controlHandler"
require "lobbyFormationUI"
require "math"

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
    self.parentPanel = parentPanel or nil

    if self.mainPanel == nil then
        self.mainPanel = Panel:new()
    end
    self.mainPanel:init(tLobbyGUIHost,0,0,0,0,parentPanel)
    self.mainPanel:setSizeStr("33%","44%")
    self.mainPanel:setAlignment(0.5,0.5)

    self:setIndex(index)

    print("Lobby formation selector initialized")

    self.mainPanel:hideWithEffect(PanelShowType.Fade,1)
    ControlHandler_reciever_remove(tLobbyGUIHost, self.parentPanel)
    ControlHandler_reciever_remove(tLobbyGUIHost, self.mainPanel.ptr)
    -- self.mainPanel:setVisible(false)

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

    local yPos = 62
    if self.mainPanel ~= nil then
        self.mainPanel:setPosStr(tostring(xPos + additionPos) .. "%",tostring(yPos) .. "%")
    end
end

function Lobby_Formation_Selector:setVisible(value)
    if self.mainPanel ~= nil then
        if value == true then
            self.mainPanel:showWithEffect_NoFocus(PanelShowType.Fade,250)
        else
            self.mainPanel:hideWithEffect(PanelShowType.Fade,250)
        end
    end
end

function Lobby_Formation_Selector:resetList()
    for i = 1, #self.formationList do
        self.formationList[i]:clear()
    end
end

function Lobby_Formation_Selector:updateUIList(keyword, pageIndex)

    -- local currentFormation = pageIndex * 0
    
    print("update with keyword " .. keyword)
    print("update with pageIndex " .. pageIndex)


    for k , v in pairs(Lobby_Formations_Info) do
        print("k " .. k )
        print("formation name " .. v.name)
        print("index " .. v.index)
    end

    self:resetList()

    self.formationList = {}

    local filteredList = {}

    local filteredIDList = {}

    if keyword ~= "" then 
        for k,v in pairs(Lobby_Formations_Info) do
            if string.find(string.lower(v.name),string.lower(keyword)) ~= nil then
                table.insert(filteredList,v)
                table.insert(filteredIDList,k)
            end
        end
    else
        -- filteredList = Table_DeepCopy(Lobby_Formations_Info)
        for k,v in pairs(Lobby_Formations_Info) do
            table.insert(filteredList,v)
            table.insert(filteredIDList,k)
        end
    end
    local modPage = tonumber(self.tIndex)

    -- if (modPage * 4) > #filteredList  then
    modPage = math.max(1, math.ceil(#filteredList / 4))
    
    self.tIndex = modPage

    print("filteredList")
    print(#filteredList)

    local resultList = {}
    local resultIDList = {}
    Lobby_Formation_Show = _G.Lobby_Formation_Show
    Lobby_Formation_Show = {}
    print( tonumber(modPage))

    if self.tIndex < 1 then
        self.tIndex = 1
    end

    for i = (self.tIndex * 4 - 3), (self.tIndex * 4) do
        print("filter index" .. i)
        if filteredList[i] ~= nil then
            table.insert(resultList,filteredList[i])
            table.insert(resultIDList,filteredIDList[i])
            -- table.insert(resultIDList,filteredList[i].index)
        end
    end

    print("result list ")
    print(#resultList)

    for i = 1, #resultList do
        local formation = Formation_Panel:new()
        formation:init(self.lobbyGUIHost, self.mainPanel.ptr, i,resultIDList[i])
        table.insert(self.formationList, formation)
    end

end