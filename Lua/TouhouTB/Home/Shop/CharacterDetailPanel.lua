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
    hpVal = nil,
    ---@type Label
    manaVal = nil,
    ---@type Label
    physicDmgVal = nil,
    ---@type Label
    physicDefVal = nil,
    ---@type Label
    magicDmgVal = nil,
    ---@type Label
    magicDefVal = nil,
    ---@type Label
    accurateVal = nil,
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
    ---@type Label
    titleVal = nil
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
    self.detailPanel:setSizeStr("95%", "90%")

    self.t_picture = Picture:new()
    self.t_picture:init(GUI_host, "./Assets/TB_GUI/panels/missing.png", 0, 0, 250,490, self.detailPanel.ptr)
    self.t_picture:setPosStr("1%", "1%")
    -- self.t_picture:setSizeStr("30%", "30%")

    self.closeButton = Label:new()
    self.closeButton:init(GUI_host, "X", 0, 0, self.detailPanel.ptr)
    self.closeButton:setPosStr("95%", "5%")
    self.closeButton:setAlignment(TextAlginment.Center)
    self.closeButton:setHoverable(0, 255, 0, 255, 255, 255, 255, 255)
    self.closeButton:setOnClickCallback(function()
        self:setVisible(false)
    end)
    local strLabel = Label:new()
    strLabel:init(GUI_host, "STR", 0, 0, self.detailPanel.ptr)
    strLabel:setPosStr("54%", "5%")
    self.strVal = Label:new()
    self.strVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    self.strVal:setPosStr("84%", "5%")
    local vitLabel = Label:new()
    vitLabel:init(GUI_host, "VIT", 0, 0, self.detailPanel.ptr)
    vitLabel:setPosStr("54%", "10%")
    self.vitVal = Label:new()
    self.vitVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    self.vitVal:setPosStr("84%", "10%")
    local dexLabel = Label:new()    
    dexLabel:init(GUI_host, "DEX", 0, 0, self.detailPanel.ptr)
    dexLabel:setPosStr("54%", "15%")
    self.dexVal = Label:new()
    self.dexVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    self.dexVal:setPosStr("84%", "15%")
    local agiLabel = Label:new()
    agiLabel:init(GUI_host, "AGI", 0, 0, self.detailPanel.ptr)
    agiLabel:setPosStr("54%", "20%")
    self.agiVal = Label:new()
    self.agiVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    self.agiVal:setPosStr("84%", "20%")
    local intLabel = Label:new()
    intLabel:init(GUI_host, "INT", 0, 0, self.detailPanel.ptr)
    intLabel:setPosStr("54%", "25%")
    self.intVal = Label:new()
    self.intVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    self.intVal:setPosStr("84%", "25%")
    local wisLabel = Label:new()
    wisLabel:init(GUI_host, "WIS", 0, 0, self.detailPanel.ptr)
    wisLabel:setPosStr("54%", "30%")
    self.wisVal = Label:new()
    self.wisVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    self.wisVal:setPosStr("84%", "30%")
    local hpLabel = Label:new()
    hpLabel:init(GUI_host, "HP", 0, 0, self.detailPanel.ptr)
    hpLabel:setPosStr("54%", "35%")
    self.hpVal = Label:new()
    self.hpVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    self.hpVal:setPosStr("84%", "35%")
    local manaLabel = Label:new()
    manaLabel:init(GUI_host, "MANA", 0, 0, self.detailPanel.ptr)
    manaLabel:setPosStr("54%", "40%")
    self.manaVal = Label:new()
    self.manaVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    self.manaVal:setPosStr("84%", "40%")
    local physicDmgLabel = Label:new()
    physicDmgLabel:init(GUI_host, "PHYSIC DMG", 0, 0, self.detailPanel.ptr)
    physicDmgLabel:setPosStr("54%", "45%")
    self.physicDmgVal = Label:new()
    self.physicDmgVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    self.physicDmgVal:setPosStr("84%", "45%")
    local physicDefLabel = Label:new()
    physicDefLabel:init(GUI_host, "PHYSIC DEF", 0, 0, self.detailPanel.ptr)
    physicDefLabel:setPosStr("54%", "50%")
    self.physicDefVal = Label:new()
    self.physicDefVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    self.physicDefVal:setPosStr("84%", "50%")
    local magicDmgLabel = Label:new()
    magicDmgLabel:init(GUI_host, "MAGIC DMG", 0, 0, self.detailPanel.ptr)
    magicDmgLabel:setPosStr("54%", "55%")
    self.magicDmgVal = Label:new()
    self.magicDmgVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    self.magicDmgVal:setPosStr("84%", "55%")
    local magicDefLabel = Label:new()
    magicDefLabel:init(GUI_host, "MAGIC DEF", 0, 0, self.detailPanel.ptr)
    magicDefLabel:setPosStr("54%", "60%")
    self.magicDefVal = Label:new()
    self.magicDefVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    self.magicDefVal:setPosStr("84%", "60%")

    local accurateLabel = Label:new()
    accurateLabel:init(GUI_host, "ACCURACY", 0, 0, self.detailPanel.ptr)
    accurateLabel:setPosStr("54%", "65%")
    self.accurateVal = Label:new()
    self.accurateVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    self.accurateVal:setPosStr("84%", "65%")
    local evasivenessLabel = Label:new()
    evasivenessLabel:init(GUI_host, "EVASIVENESS", 0, 0, self.detailPanel.ptr)
    evasivenessLabel:setPosStr("54%", "70%")
    self.evadeChanceVal = Label:new()
    self.evadeChanceVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    self.evadeChanceVal:setPosStr("84%", "70%")

    local critChanceLabel = Label:new()
    critChanceLabel:init(GUI_host, "CRIT CHANCE", 0, 0, self.detailPanel.ptr)
    critChanceLabel:setPosStr("54%", "75%")
    self.critChanceVal = Label:new()
    self.critChanceVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    self.critChanceVal:setPosStr("84%", "75%")
    local hpScaleLabel = Label:new()
    hpScaleLabel:init(GUI_host, "HP SCALE", 0, 0, self.detailPanel.ptr)
    hpScaleLabel:setPosStr("54%", "80%")
    self.hpScaleVal = Label:new()
    self.hpScaleVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    self.hpScaleVal:setPosStr("84%", "80%")
    local manaScaleLabel = Label:new()
    manaScaleLabel:init(GUI_host, "MANA SCALE", 0, 0, self.detailPanel.ptr)
    manaScaleLabel:setPosStr("54%", "85%")
    self.manaScaleVal = Label:new()
    self.manaScaleVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    self.manaScaleVal:setPosStr("84%", "85%")

    local physicDmgScaleLabel = Label:new()
    physicDmgScaleLabel:init(GUI_host, "PHYSIC DMG SCALE", 0, 0, self.detailPanel.ptr)
    physicDmgScaleLabel:setPosStr("54%", "90%")
    self.physicDmgScaleVal = Label:new()
    self.physicDmgScaleVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    self.physicDmgScaleVal:setPosStr("84%", "90%")
    local magicDmgScaleLabel = Label:new()
    magicDmgScaleLabel:init(GUI_host, "MAGIC DMG SCALE", 0, 0, self.detailPanel.ptr)
    magicDmgScaleLabel:setPosStr("54%", "95%")
    self.magicDmgScaleVal = Label:new()
    self.magicDmgScaleVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    self.magicDmgScaleVal:setPosStr("84%", "95%")

    local physicDefScaleLabel = Label:new()
    physicDefScaleLabel:init(GUI_host, "PHYSIC DEF SCALE", 0, 0, self.detailPanel.ptr)
    physicDefScaleLabel:setPosStr("54%", "100%")
    self.physicDefScaleVal = Label:new()
    self.physicDefScaleVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    self.physicDefScaleVal:setPosStr("84%", "100%")
    local magicDefScaleLabel = Label:new()
    magicDefScaleLabel:init(GUI_host, "MAGIC DEF SCALE", 0, 0, self.detailPanel.ptr)
    magicDefScaleLabel:setPosStr("54%", "105%")
    self.magicDefScaleVal = Label:new()
    self.magicDefScaleVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    self.magicDefScaleVal:setPosStr("84%", "105%")
    local accurateScaleLabel = Label:new()
    accurateScaleLabel:init(GUI_host, "ACCURACY SCALE", 0, 0, self.detailPanel.ptr)
    accurateScaleLabel:setPosStr("54%", "110%")
    self.accurateScaleVal = Label:new()
    self.accurateScaleVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    self.accurateScaleVal:setPosStr("84%", "110%")
    local evasivenessScaleLabel = Label:new()
    evasivenessScaleLabel:init(GUI_host, "EVASIVENESS SCALE", 0, 0, self.detailPanel.ptr)
    evasivenessScaleLabel:setPosStr("54%", "115%")
    self.evadeChanceScaleVal = Label:new()
    self.evadeChanceScaleVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    self.evadeChanceScaleVal:setPosStr("84%", "115%")

    local deathDoorSurviveChanceLabel = Label:new()
    deathDoorSurviveChanceLabel:init(GUI_host, "DEATH DOOR SURVIVE CHANCE", 0, 0, self.detailPanel.ptr)
    deathDoorSurviveChanceLabel:setPosStr("54%", "120%")
    self.deathDoorSurviveChanceVal = Label:new()
    self.deathDoorSurviveChanceVal:init(GUI_host, "0", 0, 0, self.detailPanel.ptr)
    self.deathDoorSurviveChanceVal:setPosStr("84%", "120%")

    self.nameVal = Label:new()
    self.nameVal:init(GUI_host, " ", 0, 0, self.detailPanel.ptr)
    self.nameVal:setPosStr("2%", "85%")
    -- self.lastNameVal = Label:new()
    -- self.lastNameVal:init(GUI_host, " ", 0, 0, self.detailPanel.ptr)
    -- self.lastNameVal:setPosStr("2%", "85%")

    self.titleVal = Label:new()
    self.titleVal:init(GUI_host, " ", 0, 0, self.detailPanel.ptr)
    -- self.titleVal:setAlignment(TextAlginment.Center)
    self.titleVal:setPosStr("2%", "90%")

    self.detailPanel:setVisible(false)

end

---@Description set the value of a label
---@param index number (CharacterDetailPanelVal)
---@param val string
function CharacterDetailPanel:setVal(index, val)
    if index == CharacterDetailPanelVal.str then 
        self.strVal:setText(val)
    elseif index == CharacterDetailPanelVal.vit then
        self.vitVal:setText(val)
    elseif index == CharacterDetailPanelVal.dex then
        self.dexVal:setText(val)
    elseif index == CharacterDetailPanelVal.agi then
        self.agiVal:setText(val)
    elseif index == CharacterDetailPanelVal.int then
        self.intVal:setText(val)
    elseif index == CharacterDetailPanelVal.wis then
        self.wisVal:setText(val)
    elseif index == CharacterDetailPanelVal.hp then
        self.hpVal:setText(val)
    elseif index == CharacterDetailPanelVal.mana then
        self.manaVal:setText(val)
    elseif index == CharacterDetailPanelVal.physicDmg then
        self.physicDmgVal:setText(val)
    elseif index == CharacterDetailPanelVal.physicDef then
        self.physicDefVal:setText(val)
    elseif index == CharacterDetailPanelVal.magicDmg then
        self.magicDmgVal:setText(val)
    elseif index == CharacterDetailPanelVal.magicDef then
        self.magicDefVal:setText(val)
    elseif index == CharacterDetailPanelVal.accurate then
        self.accurateVal:setText(val)
    elseif index == CharacterDetailPanelVal.evadeChance then
        self.evadeChanceVal:setText(val)
    elseif index == CharacterDetailPanelVal.critChance then
        self.critChanceVal:setText(val)
    elseif index == CharacterDetailPanelVal.hpScale then
        self.hpScaleVal:setText(val)
    elseif index == CharacterDetailPanelVal.manaScale then
        self.manaScaleVal:setText(val)
    elseif index == CharacterDetailPanelVal.physicDmgScale then
        self.physicDmgScaleVal:setText(val)
    elseif index == CharacterDetailPanelVal.physicDefScale then
        self.physicDefScaleVal:setText(val)
    elseif index == CharacterDetailPanelVal.magicDmgScale then
        self.magicDmgScaleVal:setText(val)
    elseif index == CharacterDetailPanelVal.magicDefScale then
        self.magicDefScaleVal:setText(val)
    elseif index == CharacterDetailPanelVal.accurateScale then
        self.accurateScaleVal:setText(val)
    elseif index == CharacterDetailPanelVal.evadeChanceScale then
        self.evadeChanceScaleVal:setText(val)
    elseif index == CharacterDetailPanelVal.deathDoorSurviveChance then
        self.deathDoorSurviveChanceVal:setText(val)
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