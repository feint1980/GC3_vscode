package.path = package.path .. ';../../Lua/system/GUI/?/?.lua;' .. ';../../Lua/system/GUI/widgets/?.lua;' .. ';../../Lua/TouhouTB/Home/?.lua;'

require "TGUI_Label"
require "TGUI_Panel"
require "TGUI_RTLabel" 
require "TGUI_Editbox"
require "TGUI_Picture"
require "TGUI_TabContainer"
require "TGUI_ScrollablePanel"
require "clientGlobal"

local GameStorage = require "clientDataStorage"

Formation_Panel = {
    mainPanel = nil,
    parentPanel = nil,
    nameLabel = nil,
    pictures = {},
    isSelected = false,
    formationID = 0, ---- data from server
}

function Formation_Panel:new(o)
    o = o or {}
    o.pictures = {}
    setmetatable(o, self)
    setmetatable(o.pictures, self)
    self.__index = self
    return o
end

function Formation_Panel:init(host, parentPanel,index,formationID)
    print("Formation_Panel called " .. index)
    if self.mainPanel == nil then
        self.mainPanel = Panel:new()
    end

    -- print("formation ID ")
    self.mainPanel:init(host,0,0,0,0,parentPanel)
    local yPos = 25 * (index -1)
    self.mainPanel:setSizeStr("100%", "25%")
    self.mainPanel:setPosStr("0%",tostring(yPos) .. "%")

    if self.nameLabel == nil then
        self.nameLabel = Label:new()
    end
    self.nameLabel:init(host,Lobby_Formations_Info[formationID].name,0,0,self.mainPanel.ptr)
    self.nameLabel:setPosStr("50%","5%")
    self.nameLabel:setAlignment(TextAlginment.Center)
    self.nameLabel:setScale(.7)

    self.mainPanel:setHoverable(0,255,0,255,125,125,125,255)

    self.mainPanel:setOnClickCallback(function()
        Formation_Selector:deselectAllItem()
        self:toggleSelection()
        LobbyScene_selectedFormation = _G.LobbyScene_selectedFormation
        LobbyScene_selectedFormation = self.formationID
        print("selected " .. LobbyScene_selectedFormation)
    end)

    self.mainPanel:setOnRightClickCallback(function()
        -- Formation_Selector:deselectAllItem()
        self:setSelected(false)
    end)

    self.formationID = formationID

    for i = 1, 4 do
        local tPicture = Picture:new()
        tPicture = Picture:new()
        tPicture:init(host,"Assets/TB_GUI/faces/nothing.png",0,0,50,50,self.mainPanel.ptr)
        -- tPicture:setTexture("Assets/TB_GUI/faces/Reimu_face.png")
        local pos = ((i - 1) * 25) + 2.5
        tPicture:setSize(65,65)
        -- tPicture:setSizeStr("23%","23%")
        tPicture:setPosStr( tostring(pos) .. "%","25%")
        table.insert(self.pictures,tPicture)
    end

    print("total character size " .. #Lobby_Formations_Info[formationID].characters)

    -- print("charactersTable " .. charactersTable)
    Lobby_User_Owned_Characters = _G.Lobby_User_Owned_Characters

    print("Lobby_User_Owned_Characters check ")
    for k,v in pairs(Lobby_User_Owned_Characters) do
        print("Lobby_User_Owned_Characters " .. k)
    end

    for i = 1, #Lobby_Formations_Info[formationID].characters do
        local characterID = Lobby_Formations_Info[formationID].characters[i].id
        print("character ID " .. characterID)
        -- print(charactersTable[characterID].portraitPath)
        print("end")
        if Lobby_User_Owned_Characters[characterID] ~= nil then
            self.pictures[i]:setTexture(Lobby_User_Owned_Characters[characterID].portraitPath)
        else
            self.pictures[i]:setTexture("Assets/TB_GUI/faces/missing.png")
        end
    end

    print("Formation " .. self.formationID .. " initialized")

    -- for k,v in pairs(GameStorage.clientSideLoadedInfo.Character_Data_Tables) do
    --     print("GameStorage.clientSideLoadedInfo.Character_Data_Tables " .. k )
    -- end
    -- for i = 1, #Lobby_Formations_Info[formationID].characters do
    --     local characterID = Lobby_Formations_Info[formationID].characters[i].id
    --     print("character ID " .. characterID)

    -- end

    -- for i = 1, #Lobby_Formation_Show[formationID].characters do
    --     local characterID = Lobby_Formation_Show[formationID].characters[i].id
    --     self.pictures[i]:setTexture(Shop_CharacterTable[characterID].portraitPath)
    -- end
    -- self.nameLabel:setText(Lobby_Formation_Show[formationID].name)

end


function Formation_Panel:setSelected(selected)
    self.isSelected = selected
    self:updateSelectionStatus()
end

function Formation_Panel:toggleSelection()
    self.isSelected = not self.isSelected
    self:updateSelectionStatus()
end

function Formation_Panel:updateSelectionStatus()
    if self.isSelected == true then
        self.mainPanel:setHoverableStop()
        self.mainPanel:setBorderColor(255,255,0,255)
    else
        self.mainPanel:setHoverable(0,255,0,255,125,125,125,125)
        self.mainPanel:setBorderColor(125,125,125,125)
    end
    Formation_Selector:updateStatus()
end

function Formation_Panel:clear()

    print("clear called")
    self.mainPanel:remove()
    -- for i = 1, #self.pictures do
    --     self.pictures[i]:remove()
    -- end

    -- if self.nameLabel ~= nil then
    --     self.nameLabel:remove()
    -- end
    -- if self.mainPanel ~= nil then
    --     self.mainPanel:remove()
    -- end

end