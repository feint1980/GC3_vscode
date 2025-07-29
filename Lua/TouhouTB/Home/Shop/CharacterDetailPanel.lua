package.path = package.path .. ';../../Lua/system/GUI/?/?.lua;' .. ';../../Lua/system/GUI/widgets/?.lua;' .. ';../../Lua/TouhouTB/Home/?.lua;'

require "TGUI_Label"
require "TGUI_Panel"
require "TGUI_RTLabel" 
require "TGUI_Editbox"
require "TGUI_Picture"
require "TGUI_TabContainer"
require "TGUI_ScrollablePanel"
require "TGUI_Canvas"
require "homeGlobal"
require "CharacterPanel"


---@class (exact) CharacterDetailPanel
---@field str number
---@field vit number
---@field dex number
---@field agi number
---@field int number
---@field wis number
---@field hp number
---@field mana number
---@field physicDmg number
---@field physicDef number
---@field magicDmg number
---@field magicDef number
---@field accurate number
---@field evadeChance number
---@field critChance number
---@field hpScale number
---@field manaScale number
---@field physicDmgScale number
---@field physicDefScale number
---@field magicDmgScale number
---@field magicDefScale number
---@field accurateScale number
---@field evadeChanceScale number
---@field deathDoorSurviveChance number
---@field name number
---@field lastName number
---@field title number
---@field panelPath number
---@field speed number
---@field id number
---@field isOwn number
CharacterDetailPanelVal = {
    str = 1,
    vit = 2,
    dex = 3,
    agi = 4,
    int = 5,
    wis = 6,
    hp = 7,
    mana = 8,
    physicDmg = 9,
    physicDef = 10,
    magicDmg = 11,
    magicDef = 12,
    accurate = 13,
    evadeChance = 14,
    critChance = 15,
    hpScale = 16,
    manaScale = 17,
    physicDmgScale = 18,
    physicDefScale = 19,
    magicDmgScale = 20,
    magicDefScale = 21,
    accurateScale = 22,
    evadeChanceScale = 23,
    deathDoorSurviveChance = 24,
    name = 25,
    lastName = 26,
    title = 27,
    panelPath = 28,
    speed = 29,
    id = 30,
    isOwn = 31
}


CharacterDetailPanel = {
    ---@type pointer
    mainPanel = nil,
    ---@type ScrollablePanel
    detailPanel = nil,
    ---@type Label
    closeButton = nil,
    ---@type Picture
    t_picture = nil,
    ---@type Label
    strVal = nil,
    ---@type Label
    vitVal = nil,
    ---@type Label
    dexVal = nil,
    ---@type Label
    agiVal = nil,
    ---@type Label
    intVal = nil,
    ---@type Label
    wisVal = nil,
    ---@type Label
    hp_mpVal = nil,
    ---@type Label
    manaVal = nil,
    ---@type RTLabel
    dmgVal = nil,
    ---@type Label
    defVal = nil,
    ---@type Label
    magicDmgVal = nil,
    ---@type Label
    magicDefVal = nil,
    ---@type Label
    acc_eva_criVal = nil,
    ---@type Label
    evadeChanceVal = nil,
    ---@type Label
    critChanceVal = nil,
    ---@type Label
    hpScaleVal = nil,
    ---@type Label
    manaScaleVal = nil,
    ---@type Label
    physicDmgScaleVal = nil,
    ---@type Label
    physicDefScaleVal = nil,
    ---@type Label
    magicDmgScaleVal = nil,
    ---@type Label
    magicDefScaleVal = nil,
    ---@type Label
    accurateScaleVal = nil,
    ---@type Label
    evadeChanceScaleVal = nil,
    ---@type Label
    deathDoorSurviveChanceVal = nil,
    ---@type Label
    nameVal = nil,
    ---@type Label
    lastNameVal = nil,
    ---@type RTLabel
    titleVal = nil,

    ---@type RTLabel
    unlockButton = nil,


    ---@type Canvas
    demoCanvas = nil,

    --- string section
    strTxt = "",
    vitTxt = "",
    dexTxt = "",
    agiTxt = "",
    intTxt = "",
    wisTxt = "",
    hpTxt = "",
    manaTxt = "",
    phyAttTxt = "",
    magAttTxt = "",
    phyDefTxt = "",
    magDefTxt = "",
    accTxt = "",
    evaTxt = "",
    criTxt = "",
    spdTxt ="",
    deathDoorSurviveChanceTxt = "",
    ---@type ScrollablePanel 
    skillDescPanel = nil,
    ---@type RTLabel
    skillNameTxt = nil,
    ---@type RTLabel
    skillEffTxt = nil,
    ---@type RTLabel
    skillQuoteTxt = nil,

    skillDescTxt = nil,
    ---@type ScrollablePanel
    skillPanel = nil,
    characterID = "NONE",
    ---@type table
    skillIcons = {},

}
function CharacterDetailPanel:new()
    local o = {}
    setmetatable(o, self)
    self.__index = self
    return o
end

local oldXSize = 0
local oldYSize = 0

function CharacterDetailPanel:init(GUI_host, parent, clientHost, ip)
    self.mainPanel = parent
    self.detailPanel = ScrollablePanel:new()
    self.detailPanel:init(GUI_host, 0, 0, 0, 0, self.mainPanel)
    self.detailPanel:setAlignment(0.5, 0.5)
    self.detailPanel:setPosStr("50%", "50%")
    self.detailPanel:setSizeStr("99%", "99%")

    self.t_picture = Picture:new()
    self.t_picture:init(GUI_host, "./Assets/TB_GUI/panels/missing.png", 0, 0, 164,343, self.detailPanel.ptr)
    self.t_picture:setPosStr("1%", "1%")
    -- self.t_picture:setSizeStr("30%", "30%")

    self.closeButton = Label:new()
    self.closeButton:init(GUI_host, "X", 0, 0, self.detailPanel.ptr)
    self.closeButton:setPosStr("99%", "1%")
    self.closeButton:setAlignment(TextAlginment.Center)
    self.closeButton:setHoverable(0, 255, 0, 255, 255, 255, 255, 255)
    self.closeButton:setOnClickCallback(function()
        self:setVisible(false)
    end)
    local strLabel = RTLabel:new()
    strLabel:init(GUI_host, Tag.color_TB_STR .. "STR" .. Tag.color_close, 0, 0, self.detailPanel.ptr)
    strLabel:setPosStr("18%", "15%")

    self.strVal = RTLabel:new()
    self.strVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    self.strVal:setPosStr("26%", "15%")
    local vitLabel = RTLabel:new()
    vitLabel:init(GUI_host, Tag.color_TB_VIT .. "VIT" .. Tag.color_close, 0, 0, self.detailPanel.ptr)
    vitLabel:setPosStr("32%", "15%")

    self.vitVal = RTLabel:new()
    self.vitVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    self.vitVal:setPosStr("38%", "15%")
    local dexLabel = RTLabel:new()
    dexLabel:init(GUI_host, Tag.color_TB_DEX .. "DEX" .. Tag.color_close, 0, 0, self.detailPanel.ptr)
    dexLabel:setPosStr("18%", "21%")
    self.dexVal = RTLabel:new()
    self.dexVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    self.dexVal:setPosStr("26%", "21%")

    local agiLabel = RTLabel:new()
    agiLabel:init(GUI_host, Tag.color_TB_AGI .. "AGI" .. Tag.color_close, 0, 0, self.detailPanel.ptr)
    agiLabel:setPosStr("32%", "21%")

    self.agiVal = RTLabel:new()
    self.agiVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    self.agiVal:setPosStr("38%", "21%")

    local intLabel = RTLabel:new()
    intLabel:init(GUI_host, Tag.color_TB_INT .. "INT" .. Tag.color_close, 0, 0, self.detailPanel.ptr)
    intLabel:setPosStr("18%", "26%")

    self.intVal = RTLabel:new()
    self.intVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    self.intVal:setPosStr("26%", "26%")

    local wisLabel = RTLabel:new()
    wisLabel:init(GUI_host, Tag.color_TB_WIS .. "WIS" .. Tag.color_close, 0, 0, self.detailPanel.ptr)
    wisLabel:setPosStr("32%", "26%")

    self.wisVal = RTLabel:new()
    self.wisVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    self.wisVal:setPosStr("38%", "26%")

    local hpMpLabel = RTLabel:new()
    hpMpLabel:init(GUI_host, "Hp/Mp", 0, 0, self.detailPanel.ptr)
    hpMpLabel:setPosStr("18%", "31%")

    self.hp_mpVal = RTLabel:new()
    self.hp_mpVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    -- self.hp_mpVal:setAlignment(TextAlginment.Center)
    self.hp_mpVal:setPosStr("30%", "31%")

    local attackLabel = Label:new()
    attackLabel:init(GUI_host, "ATK", 0, 0, self.detailPanel.ptr)
    attackLabel:setPosStr("18%", "36%")
    self.dmgVal = RTLabel:new()
    self.dmgVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    self.dmgVal:setPosStr("30%", "36%")
    local defLabel = Label:new()
    defLabel:init(GUI_host, "DEF", 0, 0, self.detailPanel.ptr)
    defLabel:setPosStr("18%", "41%")
    self.defVal = RTLabel:new()
    self.defVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    self.defVal:setPosStr("30%", "41%")

    local acc_rvaLabel = RTLabel:new()
    acc_rvaLabel:init(GUI_host, "Acc/Eva/Cri/Spd", 0, 0, self.detailPanel.ptr)
    acc_rvaLabel:setPosStr("18%", "46%")
    acc_rvaLabel:setScale(0.8)
    self.acc_eva_criVal = RTLabel:new()
    self.acc_eva_criVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    self.acc_eva_criVal:setPosStr("30%", "46%")
    self.acc_eva_criVal:setScale(0.8)

    local deathDoorSurviveChanceLabel = RTLabel:new()
    deathDoorSurviveChanceLabel:init(GUI_host,  "Last stand chance", 0, 0, self.detailPanel.ptr)
    deathDoorSurviveChanceLabel:setPosStr("18%", "51%")
    deathDoorSurviveChanceLabel:setScale(0.8)
    self.deathDoorSurviveChanceVal = RTLabel:new()
    self.deathDoorSurviveChanceVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    self.deathDoorSurviveChanceVal:setPosStr("35%", "51%")
    self.deathDoorSurviveChanceVal:setScale(0.9)
    self.nameVal = RTLabel:new()
    self.nameVal:init(GUI_host, " ", 0, 0, self.detailPanel.ptr)

    self.nameVal:setPosStr("18%", "1%")
    self.nameVal:setScale(1.15)

    self.titleVal = RTLabel:new()
    self.titleVal:init(GUI_host, " ", 0, 0, self.detailPanel.ptr)
    -- self.titleVal:setAlignment(TextAlginment.Center)
    self.titleVal:setPosStr("18%", "8%")
    self.titleVal:setScale(1.2)

    self.detailPanel:setVisible(false)

    self.skillDescPanel = ScrollablePanel:new()
    self.skillDescPanel:init(GUI_host, 0, 0, 0, 0, self.detailPanel.ptr)
    self.skillDescPanel:setAlignment(0.5, 0.5)
    self.skillDescPanel:setPosStr("25%", "80%")
    self.skillDescPanel:setSizeStr("48%", "40%")

    oldXSize, oldYSize = self.skillDescPanel:getSize()

    self.skillNameTxt = RTLabel:new()
    self.skillNameTxt:init(GUI_host, "Name", 0, 0, self.skillDescPanel.ptr)
    self.skillNameTxt:setScale(1.1)
    self.skillNameTxt:setPosStr("1%", "1%")

    self.skillDescTxt = RTLabel:new()
    self.skillDescTxt:init(GUI_host, "Description", 0, 0, self.skillDescPanel.ptr)
    self.skillDescTxt:setScale(0.72)
    self.skillDescTxt:setPosStr("1%", "13%")

    self.skillEffTxt = RTLabel:new()
    self.skillEffTxt:init(GUI_host, "Effect", 0, 0, self.skillDescPanel.ptr)
    self.skillEffTxt:setScale(0.77)
    self.skillEffTxt:setPosStr("1%", "44%")

    self.skillQuoteTxt = RTLabel:new()
    self.skillQuoteTxt:init(GUI_host, "Quote", 0, 0, self.skillDescPanel.ptr)
    self.skillQuoteTxt:setScale(0.7)
    self.skillQuoteTxt:setPosStr("1%", "88%")
    self.skillQuoteTxt:setColor(122,122,122,255)

    self.skillPanel = ScrollablePanel:new()
    self.skillPanel:init(GUI_host, 0, 0, 0, 0, self.detailPanel.ptr)
    self.skillPanel:setAlignment(0.5, 0.5)
    self.skillPanel:setPosStr("75%", "77%")
    self.skillPanel:setSizeStr("48%", "34%")

    self.unlockButton = RTLabel:new()
    self.unlockButton:init(GUI_host, "Unlock for " .. Tag.color_TB_title .. "" , 0, 0, self.detailPanel.ptr)
    self.unlockButton:setPosStr("75%", "94%")
    self.unlockButton:setAlignment(TextAlginment.Center)

    self.demoCanvas =   Canvas:new()
    self.demoCanvas:init(GUI_host,"characterDetail", 500, 100, 400, 400, self.detailPanel.ptr)

end

---@Description set the value of a label
---@param index number (CharacterDetailPanelVal)
---@param val string
function CharacterDetailPanel:setVal(index, val)
    if index == CharacterDetailPanelVal.str then
        self.strVal:setText(Tag.color_TB_STR .. val .. Tag.color_close)
    elseif index == CharacterDetailPanelVal.vit then
        self.vitVal:setText(Tag.color_TB_VIT .. val .. Tag.color_close)
    elseif index == CharacterDetailPanelVal.dex then
        self.dexVal:setText(Tag.color_TB_DEX .. val .. Tag.color_close)
    elseif index == CharacterDetailPanelVal.agi then
        self.agiVal:setText(Tag.color_TB_AGI .. val .. Tag.color_close)
    elseif index == CharacterDetailPanelVal.int then
        self.intVal:setText(Tag.color_TB_INT .. val .. Tag.color_close)
    elseif index == CharacterDetailPanelVal.wis then
        self.wisVal:setText(Tag.color_TB_WIS .. val .. Tag.color_close)
    elseif index == CharacterDetailPanelVal.hp then
        self.hpTxt = val
        self.hp_mpVal:setText(Tag.color_TB_VIT .. self.hpTxt .. Tag.color_close  .. "/" .. Tag.color_TB_WIS .. self.manaTxt .. Tag.color_close)
    elseif index == CharacterDetailPanelVal.mana then
        self.manaTxt = val
        self.hp_mpVal:setText(Tag.italic_open .. Tag.color_TB_VIT .. self.hpTxt .. Tag.color_close   .. " / " .. Tag.color_TB_WIS .. self.manaTxt .. Tag.color_close ..Tag.italic_close)
    elseif index == CharacterDetailPanelVal.physicDmg then
        self.phyAttTxt = val
        self.dmgVal:setText(Tag.italic_open .. Tag.color_TB_STR .. self.phyAttTxt .. Tag.color_close .. " / " .. Tag.color_TB_INT .. self.magAttTxt .. Tag.color_close .. Tag.italic_close)
    elseif index == CharacterDetailPanelVal.magicDmg then
        self.magAttTxt = val
        self.dmgVal:setText(Tag.italic_open .. Tag.color_TB_STR .. self.phyAttTxt .. Tag.color_close .. " / " .. Tag.color_TB_INT .. self.magAttTxt .. Tag.color_close .. Tag.italic_close)
    elseif index == CharacterDetailPanelVal.physicDef then
        self.phyDefTxt = val
        self.defVal:setText(Tag.color_TB_AGI .. self.phyDefTxt .. Tag.color_close .. " / " .. Tag.color_TB_INT .. self.magDefTxt .. Tag.color_close)
    elseif index == CharacterDetailPanelVal.magicDef then
        self.magDefTxt = val
        self.defVal:setText(Tag.color_TB_AGI .. self.phyDefTxt .. Tag.color_close .. " / " .. Tag.color_TB_WIS .. self.magDefTxt .. Tag.color_close)
    elseif index == CharacterDetailPanelVal.accurate then
        local txt = ""
        self.accTxt =  Tag.color_TB_DEX .. val .. Tag.color_close

        txt = self.accTxt .. " / " .. self.evaTxt .. " / " .. self.criTxt .. " / " .. self.spdTxt
        self.acc_eva_criVal:setText(txt)

    elseif index == CharacterDetailPanelVal.evadeChance then
        local txt = ""

        self.evaTxt = Tag.color_TB_AGI .. val .. Tag.color_close

        txt = self.accTxt .. " / " .. self.evaTxt .. " / " .. self.criTxt .. " / " .. self.spdTxt
        self.acc_eva_criVal:setText(txt)
    elseif index == CharacterDetailPanelVal.critChance then
        local txt = ""

        self.criTxt = Tag.color_TB_DEX .. val .. Tag.color_close

        txt = self.accTxt .. " / " .. self.evaTxt .. " / " .. self.criTxt .. " / " .. self.spdTxt
        self.acc_eva_criVal:setText(txt)
    elseif index == CharacterDetailPanelVal.speed then
        local txt = ""
        self.spdTxt = Tag.color_TB_AGI .. val .. Tag.color_close
        txt = self.accTxt .. " / " .. self.evaTxt .. " / " .. self.criTxt .. " / " .. self.spdTxt
        self.acc_eva_criVal:setText(txt)
    elseif index == CharacterDetailPanelVal.id then
        self.characterID = val

        self.skillDescPanel:setSize(0,0)
        self.skillDescPanel:setSizeStr("48%", "40%")
        self.skillNameTxt:setText("Name")
        self.skillDescTxt:setText("Description")
        self.skillEffTxt:setText("Effect")
        self.skillQuoteTxt:setText("Quote")

        self.skillNameTxt:setPosStr("1%", "1%")
        self.skillDescTxt:setPosStr("1%", "13%")
        self.skillEffTxt:setPosStr("1%", "44%")
        self.skillQuoteTxt:setPosStr("1%", "88%")
        
        --process if user owned the character
        self.unlockButton:setColor(255, 255, 255, 255)
        self.unlockButton:setHoverable(0, 255, 0, 255, 255, 255, 255, 255)
        self.unlockButton:setText("Unlock for " .. Tag.color_TB_title ..  Shop_CharacterTable[self.characterID].price .. " " ..Tag.icon_soul .. Tag.color_close )
        self.unlockButton:setOnClickCallback(function()
            print("unlock " ..  Shop_CharacterTable[self.characterID].ID)
        
            local id, pw= Home_GetInfo(2)

            SendRequest(PacketChannel.TransactionChannel,ShopResponse.ShopCharacter_Buy,{id,pw, Shop_CharacterTable[self.characterID].ID},5,0.25)
            -- SendReliable(host,ip,PacketChannel.TransactionChannel,ShopResponse.ShopCharacter_Buy,{"davai", Shop_CharacterTable[self.characterID].ID}) client host needed
        end)

        Skill_Table = _G.Skill_Table
        --- display innate skill 
        
        if Skill_Serialized_Table[self.characterID] ~= nil then
            for k,v in pairs(Skill_Serialized_Table[self.characterID]) do
                if Skill_Table[self.characterID][k] ~= nil then
                    self.skillNameTxt:setText(Skill_Table[self.characterID][k].name)
                    self.skillDescTxt:setText(Skill_Table[self.characterID][k].description)

                    local nX, nY = self.skillDescTxt:getSize()
                    local tOldXPos, tOldYPos = self.skillEffTxt:getPos()

                    self.skillEffTxt:setPos(5, nY + 25)
                    self.skillEffTxt:setText(Skill_Table[self.characterID][k].effect)
                    local nX2, nY2 = self.skillEffTxt:getSize()

                    self.skillQuoteTxt:setPos(5, nY + nY2 + 10)
                    self.skillQuoteTxt:setText(Skill_Table[self.characterID][k].quote)
                    return
                end
            end
        else
            print("no innate skill detacted")
        end
    elseif index == CharacterDetailPanelVal.deathDoorSurviveChance then
        self.deathDoorSurviveChanceVal:setText( Tag.color_TB_VIT .. val .. Tag.color_close)
    elseif index == CharacterDetailPanelVal.name then
        self.nameVal:setText(val)
    elseif index == CharacterDetailPanelVal.lastName then
        self.lastNameVal:setText(val)
    elseif index == CharacterDetailPanelVal.title then
        self.titleVal:setText(val)
    elseif index == CharacterDetailPanelVal.panelPath then
        self.t_picture:setTexture(val)
    elseif index == CharacterDetailPanelVal.isOwn then
        if val == true then
            self.unlockButton:setText("Unlocked")
            self.unlockButton:setColor(122,122,122 ,  255)
        end
    end
end

---@Description show or hide the panel
---@param visible boolean
function CharacterDetailPanel:setVisible(visible)
    if visible == true then
        self.detailPanel:showWithEffect(PanelShowType.Fade,250)
    else
        self.detailPanel:hideWithEffect(PanelShowType.Fade,250)
    end
end

