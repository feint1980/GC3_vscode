package.path = package.path .. ';../../Lua/system/objects/?.lua;' .. ';../../Lua/TouhouTB/Combat/UI/?.lua;'

require "compositeObject"

--[[
    Combat_dock_middle_panel
    Bottom button grid: "Basic Skills" / "Items" / "General" groups,
    each containing a row of key-bound action buttons (1,2,3,4 / Q,W / E,R)
    matching the layout in ref_2.png.

    Each button is its own L_compositeObject with:
      - a small bordered panel
      - a key label (top-left, e.g. "1", "Q", "E")
      - a name text (center, e.g. "Yin-Yang Shot")
      - an info text (bottom, e.g. "MP 20" / "Front 1")
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
    buttonWidth = 90,
    buttonHeight = 90,
    buttonGap = 10,
}

function Combat_dock_middle_panel:new()
    local o = {}
    setmetatable(o, self)
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
    local groupY = -(self.windowHeight * 0.5 - 60)  -- distance up from bottom edge, in our -pos coordinate space

    --======================================================
    -- group headers
    --======================================================
    local basicSkillsX = -(self.windowWidth * 0.5) + 430
    local itemsX       = -(self.windowWidth * 0.5) + 700
    local generalX     = -(self.windowWidth * 0.5) + 900

    self.basicSkillsHeader = self:createHeader("Basic Skills", basicSkillsX, groupY - 30)
    self.itemsHeader       = self:createHeader("Items (2/2)",  itemsX,       groupY - 30)
    self.generalHeader     = self:createHeader("General",      generalX,     groupY - 30)

    --======================================================
    -- Basic Skills row: slots 1,2,3,4
    --======================================================
    local bw = self.buttonWidth
    local gap = self.buttonGap

    self:addButton("1", basicSkillsX,                     groupY, "Yin-Yang Shot", "MP 20")
    self:addButton("2", basicSkillsX + (bw + gap),         groupY, "Spirit Barrage", "Free")
    self:addButton("3", basicSkillsX + (bw + gap) * 2,     groupY, "Ofuda Throw",    "MP 15")
    self:addButton("4", basicSkillsX + (bw + gap) * 3,     groupY, "Focused Mind",   "SP 30")

    --======================================================
    -- Items row: Q, W
    --======================================================
    self:addButton("Q", itemsX,               groupY, "Hakurei Charm", "x1")
    self:addButton("W", itemsX + (bw + gap),   groupY, "Heal Potion",   "x1")

    --======================================================
    -- General row: E, R
    --======================================================
    self:addButton("E", generalX,             groupY, "Move",     "")
    self:addButton("R", generalX + (bw + gap), groupY, "End Turn", "")
end

---@Description internal: create a header text object (not part of a button)
function Combat_dock_middle_panel:createHeader(label, posX, posY)
    local headerDock = L_compositeObject:new()
    -- zero-size composite purely to host a text object at this position
    headerDock:init(self.renderContextHost, posX, posY, 0, 0, 0, 4)
    headerDock:addText(label, 0, 0, 3, 0.4, 220, 200, 160, 255, 0) -- center aligned, gold-ish
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
        -(self.buttonWidth * 0.5) + 10, -(self.buttonHeight * 0.5) + 14,
        1, 0.3,
        255, 255, 255, 255,
        0)

    -- name, center of the button (small, may wrap visually depending on your text renderer)
    btn:addText(name,
        0, 4,
        3, 0.28,
        230, 230, 230, 255,
        0)

    -- info line, bottom of the button
    if info ~= "" then
        btn:addText(info,
            0, (self.buttonHeight * 0.5) - 14,
            3, 0.25,
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