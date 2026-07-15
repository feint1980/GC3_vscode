package.path = package.path .. ';../../Lua/system/objects/?.lua;' .. ';../../Lua/TouhouTB/Combat/UI/?.lua;'

require "compositeObject"

--[[
    Combat_dock_middle_panel
]]

Combat_dock_middle_panel = {
    renderContextHost = nil,
    windowWidth = 0,
    windowHeight = 0,

    -- group header texts
    basicSkillsHeader = nil,
    itemsHeader = nil,
    generalHeader = nil,

    -- button registries, keyed by slot name e.g. "1", "Q", "E"
    buttons = {},

    -- layout constants
    buttonWidth = 120,
    buttonHeight = 120,
    buttonGap = 10,
}

function Combat_dock_middle_panel:new()
    local o = {}
    setmetatable(o, self)
    -- setmetatable(o.buttons, self.buttons)
    self.__index = self
    o.buttons = {}
    return o
end

function Combat_dock_middle_panel:init(renderHost, tWindowWidth, tWindowHeight)
    self.renderContextHost = renderHost
    self.windowWidth = tWindowWidth
    self.windowHeight = tWindowHeight
    self.buttons = {}

    -- anchor the whole button grid to the bottom-center of the screen,
    -- leaving room on the left for the character info dock and on the
    -- right for the skill detail panel
    local groupY = -(self.windowHeight * 0.5 )  + (self.buttonHeight * 0.5) -- distance up from bottom edge, in our -pos coordinate space
    

    --======================================================
    -- group headers
    --======================================================
    -- local basicSkillsX = -(self.windowWidth * 0.5) + 150 + 430
    -- local itemsX       = -(self.windowWidth * 0.5) + 700
    -- local generalX     = -(self.windowWidth * 0.5) + 900

    local basicSkillsX = -(self.windowWidth * 0.5) + 360 + self.buttonWidth * 0.5 
    local itemsX       = -(self.windowWidth * 0.5) + 320 + (self.buttonWidth * 5 )  + (self.buttonGap * 2)
    local generalX     = itemsX 
    + (self.buttonWidth + self.buttonGap * 2)

    self.basicSkillsHeader = self:createHeader("Basic Skills", basicSkillsX + self.buttonWidth * 2, groupY + 210)
    self.itemsHeader       = self:createHeader("Items",  itemsX ,       groupY + 220)
    self.generalHeader     = self:createHeader("Generals",  
    generalX,    groupY + 220)

    --======================================================
    -- Basic Skills row: slots 1,2,3,4
    --======================================================
    local bw = self.buttonWidth
    local gap = self.buttonGap * 0.5

    self:addButton("Q", basicSkillsX,                     groupY + self.buttonHeight + self.buttonGap , "Yin-Yang Shot", "MP 20")
    self:addButton("W", basicSkillsX + (bw + gap),         groupY + self.buttonHeight + self.buttonGap, "Spirit Barrage", "Free")
    self:addButton("E", basicSkillsX + (bw + gap) * 2,     groupY + self.buttonHeight + self.buttonGap, "Ofuda Throw",    "MP 15")
    self:addButton("R", basicSkillsX + (bw + gap) * 3,     groupY + self.buttonHeight + self.buttonGap, "Focused Mind",   "SP 30")

    self:addButton("A", basicSkillsX,                     groupY , "Kick Back", "MP 20")
    self:addButton("S", basicSkillsX + (bw + gap),         groupY, "Brace", "Free")
    self:addButton("D", basicSkillsX + (bw + gap) * 2,     groupY, "Hakurei Bless",    "MP 15")
    self:addButton("F", basicSkillsX + (bw + gap) * 3,     groupY, "Meditation",   "")

    --======================================================
    -- Items row: 1,2
    --======================================================
    self:addButton("1", itemsX ,               groupY + self.buttonHeight + self.buttonGap , "Hakurei Charm", "x1")
    self:addButton("2", itemsX,   groupY  , "Heal Potion",   "x1")

    --======================================================
    -- General row: M, Space
    --======================================================
    self:addButton("M", generalX,             groupY + self.buttonHeight + self.buttonGap , "Move",     "AP 0.5")
    self:addButton("Space", generalX, groupY , "End Turn", "")
end

---@Description internal: create a header text object (not part of a button)
function Combat_dock_middle_panel:createHeader(label, posX, posY)
    local headerDock = L_compositeObject:new()
    -- zero-size composite purely to host a text object at this position
    headerDock:init(self.renderContextHost, posX, posY, 0,
    0, 0, 4)
    headerDock:addText(label, 0, 0, 3, .95, 220, 200, 160, 255, 0) -- center aligned, gold-ish
    return headerDock
end

---@Description add one action button (key + panel + name + info) and register it
---@param key string key label, e.g. "1", "Q", "E"
---@param posX number x position (in the same -pos coordinate space as the rest of the dock)
---@param posY number y position
---@param name string skill/item/action name
---@param info string small info line (cost, count, etc.) -- can be ""
function Combat_dock_middle_panel:addButton(key, posX, posY, name, info)
    local btn = L_compositeObject:new()
    btn:init(self.renderContextHost, posX, posY, self.buttonWidth, self.buttonHeight, 0, 4)
    btn:addPanel("Basic_border", 0.3)
    btn:showPanelBG(true)
    btn:setPanelBGColor(20, 20, 25, 220)
    btn:setPanelBGScale(0.95)

    -- key label, top-left corner of the button
    btn:addText(key,
        -(self.buttonWidth * 0.5) + 10, (self.buttonHeight * 0.5) - 14,
        1, 0.8,
        255, 255, 255, 255,
        0)

    -- name, center of the button (small, may wrap visually depending on your text renderer)
    btn:addText(name,
        0, 4,
        3, 0.55,
        230, 230, 230, 255,
        0)

    -- info line, bottom of the button
    if info ~= "" then
        btn:addText(info,
            0, -(self.buttonHeight * 0.5) + 14,
            3, 0.6,
            170, 200, 255, 255,
            0)
    end

    self.buttons[key] = btn
end

---@Description update a button's displayed name/info at runtime (e.g. skill swapped, item count changed)
function Combat_dock_middle_panel:updateButton(key, name, info)
    local btn = self.buttons[key]
    if btn == nil then
        print("Combat_dock_middle_panel: no button registered for key " .. tostring(key))
        return
    end
    -- NOTE: this assumes addText returns a pointer whose .text field
    -- is writable from Lua (same assumption used in combat_dock_my_character_info.lua).
    -- If that's not how your binding works, this needs to go through whatever
    -- setter you actually expose (e.g. cpp_TextObject_setText).
end

return Combat_dock_middle_panel