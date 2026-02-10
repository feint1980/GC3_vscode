package.path = package.path .. ';../../Lua/system/GUI/?/?.lua;' .. ';../../Lua/system/GUI/widgets/?.lua;' .. ';../../Lua/TouhouTB/Home/?.lua;'

require "TGUI_Label"
require "TGUI_Panel"
require "TGUI_RTLabel" 
require "TGUI_Editbox"
require "TGUI_Picture"
require "TGUI_TabContainer"
require "TGUI_ScrollablePanel"


Formation_Panel = {
    mainPanel = nil,
    parentPanel = nil,
    nameLabel = nil,
    pictures = {}
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
    -- if self.mainPanel == nil then
    self.mainPanel = Panel:new()
    -- end

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

    for i = 1, 4 do
        local tPicture = Picture:new()
        tPicture = Picture:new()
        tPicture:init(host,"Assets/TB_GUI/faces/nothing.png",0,0,50,50,self.mainPanel.ptr)
        -- tPicture:setTexture("Assets/TB_GUI/faces/Reimu_face.png")
        local pos = ((i - 1) * 25) + 2.5
        tPicture:setSize(65,65)
        -- tPicture:setSizeStr("23%","23%")
        tPicture:setPosStr( tostring(pos) .. "%","50%")
        table.insert(self.pictures,tPicture)
    end

    for i = 1, #Lobby_Formation_Show[formationID].characters do
        local characterID = Lobby_Formation_Show[formationID].characters[i].id
        self.pictures[i]:setTexture(Shop_CharacterTable[characterID].portraitPath)
    end

    -- for i = 1, #Lobby_Formation_Show[formationID].characters do
    --     local characterID = Lobby_Formation_Show[formationID].characters[i].id
    --     self.pictures[i]:setTexture(Shop_CharacterTable[characterID].portraitPath)
    -- end
    -- self.nameLabel:setText(Lobby_Formation_Show[formationID].name)

end

function Formation_Panel:clear()

    for i = 1, #self.pictures do
        self.pictures[i]:remove()
    end

    if self.nameLabel ~= nil then
        self.nameLabel:remove()
    end
    if self.mainPanel ~= nil then
        self.mainPanel:remove()
    end

end