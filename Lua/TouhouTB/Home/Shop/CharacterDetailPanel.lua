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
    panelPath = 28
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
    physicDefVal = nil,
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

    --- string section
    strTxt = "",
    vitTxt = "",
    dexTxt = "",
    agiTxt = "",
    intTxt = "",
    wisTxt = "",
    hpTxt = "",


}
function CharacterDetailPanel:new()
    local o = {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function CharacterDetailPanel:init(GUI_host, parent)
    self.mainPanel = parent
    self.detailPanel = ScrollablePanel:new()
    self.detailPanel:init(GUI_host, 0, 0, 0, 0, self.mainPanel)
    self.detailPanel:setAligment(0.5, 0.5)
    self.detailPanel:setPosStr("50%", "50%")
    self.detailPanel:setSizeStr("98%", "98%")

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
    local strLabel = Label:new()
    strLabel:init(GUI_host, "STR", 0, 0, self.detailPanel.ptr)
    strLabel:setPosStr("18%", "2%")
    strLabel:setScale(0.8)
    self.strVal = RTLabel:new()
    self.strVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    self.strVal:setPosStr("24%", "2%")
    self.strVal:setScale(0.8)
    local vitLabel = Label:new()
    vitLabel:init(GUI_host, "VIT", 0, 0, self.detailPanel.ptr)
    vitLabel:setPosStr("28%", "2%")
    vitLabel:setScale(0.8)
    self.vitVal = RTLabel:new()
    self.vitVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    self.vitVal:setPosStr("34%", "2%")
    self.vitVal:setScale(0.8)
    local dexLabel = Label:new()
    dexLabel:init(GUI_host, "DEX", 0, 0, self.detailPanel.ptr)
    dexLabel:setPosStr("18%", "8%")
    dexLabel:setScale(0.8)
    self.dexVal = Label:new()
    self.dexVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    self.dexVal:setPosStr("24%", "8%")
    self.dexVal:setScale(0.8)
    local agiLabel = Label:new()
    agiLabel:init(GUI_host, "AGI", 0, 0, self.detailPanel.ptr)
    agiLabel:setPosStr("28%", "8%")
    agiLabel:setScale(0.8)
    self.agiVal = Label:new()
    self.agiVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    self.agiVal:setPosStr("34%", "8%")
    self.agiVal:setScale(0.8)
    local intLabel = Label:new()
    intLabel:init(GUI_host, "INT", 0, 0, self.detailPanel.ptr)
    intLabel:setPosStr("18%", "13%")
    intLabel:setScale(0.8)
    self.intVal = Label:new()
    self.intVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    self.intVal:setPosStr("24%", "13%")
    self.intVal:setScale(0.8)
    local wisLabel = Label:new()
    wisLabel:init(GUI_host, "WIS", 0, 0, self.detailPanel.ptr)
    wisLabel:setPosStr("28%", "13%")
    wisLabel:setScale(0.8)
    self.wisVal = Label:new()
    self.wisVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    self.wisVal:setPosStr("34%", "13%")
    self.wisVal:setScale(0.8)
    local hpLabel = RTLabel:new()
    hpLabel:init(GUI_host, "Hp/Mp", 0, 0, self.detailPanel.ptr)
    hpLabel:setPosStr("18%", "18%")
    hpLabel:setScale(0.8)
    self.hp_mpVal = RTLabel:new()
    self.hp_mpVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    self.hp_mpVal:setPosStr("34%", "18%")
    self.hp_mpVal:setScale(0.8)
    local attackLabel = Label:new()
    attackLabel:init(GUI_host, "ATT", 0, 0, self.detailPanel.ptr)
    attackLabel:setPosStr("18%", "23%")
    attackLabel:setScale(0.8)
    self.dmgVal = RTLabel:new()
    self.dmgVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    self.dmgVal:setPosStr("34%", "23%")
    self.dmgVal:setScale(0.8)
    local defLabel = Label:new()
    defLabel:init(GUI_host, "DEF", 0, 0, self.detailPanel.ptr)
    defLabel:setPosStr("18%", "28%")
    defLabel:setScale(0.8)
    self.physicDefVal = RTLabel:new()
    self.physicDefVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    self.physicDefVal:setPosStr("34%", "28%")
    self.physicDefVal:setScale(0.8)

    local acc_rvaLabel = RTLabel:new()
    acc_rvaLabel:init(GUI_host, "Acc/Eva/Crit", 0, 0, self.detailPanel.ptr)
    acc_rvaLabel:setPosStr("18%", "33%")
    acc_rvaLabel:setScale(0.7)
    self.acc_eva_criVal = RTLabel:new()
    self.acc_eva_criVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    self.acc_eva_criVal:setPosStr("34%", "33%")
    self.acc_eva_criVal:setScale(0.8)

    -- local hpScaleLabel = Label:new()
    -- hpScaleLabel:init(GUI_host, "HP scale", 0, 0, self.detailPanel.ptr)
    -- hpScaleLabel:setPosStr("28%", "18%")
    -- hpScaleLabel:setScale(0.8)
    -- self.hpScaleVal = Label:new()
    -- self.hpScaleVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    -- self.hpScaleVal:setPosStr("51%", "18%")
    -- self.hpScaleVal:setScale(0.8)
    -- local manaScaleLabel = Label:new()
    -- manaScaleLabel:init(GUI_host, "Mana scale", 0, 0, self.detailPanel.ptr)
    -- manaScaleLabel:setPosStr("35%", "23%")
    -- manaScaleLabel:setScale(0.8)
    -- self.manaScaleVal = Label:new()
    -- self.manaScaleVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    -- self.manaScaleVal:setPosStr("51%", "23%")
    -- self.manaScaleVal:setScale(0.8)

    -- local physicDmgScaleLabel = Label:new()
    -- physicDmgScaleLabel:init(GUI_host, "Physic DMG scale", 0, 0, self.detailPanel.ptr)
    -- physicDmgScaleLabel:setPosStr("35%", "28%")
    -- physicDmgScaleLabel:setScale(0.7)
    -- self.physicDmgScaleVal = Label:new()
    -- self.physicDmgScaleVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    -- self.physicDmgScaleVal:setPosStr("51%", "28%")
    -- self.physicDmgScaleVal:setScale(0.8)
    -- local magicDmgScaleLabel = Label:new()
    -- magicDmgScaleLabel:init(GUI_host, "Magic DMG scale", 0, 0, self.detailPanel.ptr)
    -- magicDmgScaleLabel:setPosStr("35%", "33%")
    -- magicDmgScaleLabel:setScale(0.7)
    -- self.magicDmgScaleVal = Label:new()
    -- self.magicDmgScaleVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    -- self.magicDmgScaleVal:setPosStr("51%", "33%")
    -- self.magicDmgScaleVal:setScale(0.8)

    -- local physicDefScaleLabel = Label:new()
    -- physicDefScaleLabel:init(GUI_host, "Physic def scale", 0, 0, self.detailPanel.ptr)
    -- physicDefScaleLabel:setPosStr("35%", "38%")
    -- physicDefScaleLabel:setScale(0.7)
    -- self.physicDefScaleVal = Label:new()
    -- self.physicDefScaleVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    -- self.physicDefScaleVal:setPosStr("51%", "38%")
    -- self.physicDefScaleVal:setScale(0.8)
    -- local magicDefScaleLabel = Label:new()
    -- magicDefScaleLabel:init(GUI_host, "Magic def scale", 0, 0, self.detailPanel.ptr)
    -- magicDefScaleLabel:setPosStr("35%", "43%")
    -- magicDefScaleLabel:setScale(0.8)
    -- self.magicDefScaleVal = Label:new()
    -- self.magicDefScaleVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    -- self.magicDefScaleVal:setPosStr("51%", "43%")
    -- self.magicDefScaleVal:setScale(0.8)
    -- local accurateScaleLabel = Label:new()
    -- accurateScaleLabel:init(GUI_host, "Accurate scale", 0, 0, self.detailPanel.ptr)
    -- accurateScaleLabel:setPosStr("35%", "48%")
    -- accurateScaleLabel:setScale(0.7)
    -- self.accurateScaleVal = Label:new()
    -- self.accurateScaleVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    -- self.accurateScaleVal:setPosStr("51%", "48%")
    -- self.accurateScaleVal:setScale(0.8)
    -- local evasivenessScaleLabel = Label:new()
    -- evasivenessScaleLabel:init(GUI_host, "Evade scale", 0, 0, self.detailPanel.ptr)
    -- evasivenessScaleLabel:setPosStr("35%", "53%")
    -- evasivenessScaleLabel:setScale(0.8)
    -- self.evadeChanceScaleVal = Label:new()
    -- self.evadeChanceScaleVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    -- self.evadeChanceScaleVal:setPosStr("51%", "53%")
    -- self.evadeChanceScaleVal:setScale(0.8)

    -- local deathDoorSurviveChanceLabel = Label:new()
    -- deathDoorSurviveChanceLabel:init(GUI_host, "Death door survive chance", 0, 0, self.detailPanel.ptr)
    -- deathDoorSurviveChanceLabel:setPosStr("35%", "58%")
    -- deathDoorSurviveChanceLabel:setScale(0.7)
    -- self.deathDoorSurviveChanceVal = Label:new()
    -- self.deathDoorSurviveChanceVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    -- self.deathDoorSurviveChanceVal:setPosStr("51%", "58%")
    -- self.deathDoorSurviveChanceVal:setScale(0.8)
    -- self.nameVal = RTLabel:new()
    -- self.nameVal:init(GUI_host, " ", 0, 0, self.detailPanel.ptr)
    -- -- self.nameVal:setAlignment(TextAlginment.Center)
    -- self.nameVal:setPosStr("0%", "60%")
    -- self.nameVal:setScale(1.1)

    -- self.titleVal = RTLabel:new()
    -- self.titleVal:init(GUI_host, " ", 0, 0, self.detailPanel.ptr)
    -- -- self.titleVal:setAlignment(TextAlginment.Center)
    -- self.titleVal:setPosStr("0%", "65%")
    -- self.titleVal:setScale(1.1)
    -- self.detailPanel:setVisible(false)

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
        self.hp_mpVal:setText(Tag.color_red .. self.hpTxt .. Tag.color_close  .. "/" .. Tag.color_blue .. self.manaTxt .. Tag.color_close)
    elseif index == CharacterDetailPanelVal.mana then
        self.manaTxt = val
        self.hp_mpVal:setText(Tag.color_red .. self.hpTxt .. Tag.color_close  .. "/" .. Tag.color_blue .. self.manaTxt .. Tag.color_close)
        -- return
    -- elseif index == CharacterDetailPanelVal.physicDmg then
    --     self.dmgVal:setText(val)
    -- elseif index == CharacterDetailPanelVal.physicDef then
    --     self.physicDefVal:setText(val)
    -- elseif index == CharacterDetailPanelVal.magicDmg then
    --     self.magicDmgVal:setText(val)
    -- elseif index == CharacterDetailPanelVal.magicDef then
    --     -- self.magicDefVal:setText(val)
    -- elseif index == CharacterDetailPanelVal.accurate then
    --     self.acc_eva_criVal:setText(val)
    -- elseif index == CharacterDetailPanelVal.evadeChance then
    --     self.evadeChanceVal:setText(val)
    -- elseif index == CharacterDetailPanelVal.critChance then
    --     self.critChanceVal:setText(val)
    -- elseif index == CharacterDetailPanelVal.hpScale then
    --     self.hpScaleVal:setText(val)
    -- elseif index == CharacterDetailPanelVal.manaScale then
    --     self.manaScaleVal:setText(val)
    -- elseif index == CharacterDetailPanelVal.physicDmgScale then
    --     self.physicDmgScaleVal:setText(val)
    -- elseif index == CharacterDetailPanelVal.physicDefScale then
    --     self.physicDefScaleVal:setText(val)
    -- elseif index == CharacterDetailPanelVal.magicDmgScale then
    --     self.magicDmgScaleVal:setText(val)
    -- elseif index == CharacterDetailPanelVal.magicDefScale then
    --     self.magicDefScaleVal:setText(val)
    -- elseif index == CharacterDetailPanelVal.accurateScale then
    --     self.accurateScaleVal:setText(val)
    -- elseif index == CharacterDetailPanelVal.evadeChanceScale then
    --     self.evadeChanceScaleVal:setText(val)
    -- elseif index == CharacterDetailPanelVal.deathDoorSurviveChance then
    --     self.deathDoorSurviveChanceVal:setText(val)
    elseif index == CharacterDetailPanelVal.name then
        self.nameVal:setText(val)
    elseif index == CharacterDetailPanelVal.lastName then
        self.lastNameVal:setText(val)
    elseif index == CharacterDetailPanelVal.title then
        self.titleVal:setText(val)
    elseif index == CharacterDetailPanelVal.panelPath then
        self.t_picture:setTexture(val)
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