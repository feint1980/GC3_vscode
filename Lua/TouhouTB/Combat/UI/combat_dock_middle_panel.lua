package.path = package.path .. ';../../Lua/system/objects/?.lua;' .. ';../../Lua/TouhouTB/Combat/UI/?.lua;'

require "compositeObject"
require "dock_button"
require "dock_global"
--[[
    Combat_dock_middle_panel
    
]]
---@class Combat_dock_middle_panel
Combat_dock_middle_panel = {}
Combat_dock_middle_panel.__index = Combat_dock_middle_panel
function Combat_dock_middle_panel:new()

    local o = setmetatable({}, self)

    o.renderContextHost = nil
    o.windowWidth = 0
    o.windowHeight = 0
    o.posX = 0
    o.posY = 0

    o.mainPanel = nil

    -- group header texts
    o.basicSkillsHeader = nil
    o.itemsHeader = nil
    o.generalHeader = nil

    -- layout constants
    o.buttonWidth = 120
    o.buttonHeight = 120
    o.buttonGap = 10
    -- button registries , keyed group and slot name e.g. "1", "Q", "E"
    o.buttons = {}

    -- setmetatable(o.buttons, self.buttons)
    self.__index = self

    return o
end

function Combat_dock_middle_panel:init(renderHost, tPosX,tPosY,tWindowWidth, tWindowHeight)

    self.renderContextHost = renderHost
    self.windowWidth = tWindowWidth
    self.windowHeight = tWindowHeight
    self.posX = tPosX
    self.posY = tPosY

    self.buttons = {}

    -- anchor the whole button grid to the bottom-center of the screen,
    -- leaving room on the left for the character info dock and on the
    -- right for the skill detail panel
    local groupY = -(self.windowHeight * 0.5 )  + (self.buttonHeight * 0.5) + 5 -- distance up from bottom edge, in our -pos coordinate space

    --======================================================
    -- group headers
    --======================================================
    -- local basicSkillsX = -(self.windowWidth * 0.5) + 150 + 430
    -- local itemsX       = -(self.windowWidth * 0.5) + 700
    -- local generalX     = -(self.windowWidth * 0.5) + 900

    -- old 360, 320, 
    local basicSkillsX = -(self.windowWidth * 0.5) + 360 + self.buttonWidth * 0.5
    local itemsX       = -(self.windowWidth * 0.5) + 320 + (self.buttonWidth * 5 )  + (self.buttonGap * 2)
    local generalX     = itemsX
    + (self.buttonWidth + self.buttonGap * 2)

    self.basicSkillsHeader = self:createHeader("Basic Skills", basicSkillsX + self.buttonWidth * 2, groupY + 215)
    self.itemsHeader       = self:createHeader("Items",  itemsX ,       groupY + 215)
    self.generalHeader     = self:createHeader("Generals",  
    generalX,    groupY + 215)

    local panelWidth = ( 6 * (self.buttonWidth + self.buttonGap ) ) + 10

    self.mainPanel = L_compositeObject:new()
    self.mainPanel:init(self.renderContextHost,
    (self.posX - self.windowWidth * 0.5 ) - 50, self.posY - (self.buttonHeight) + 70, panelWidth,
    self.windowHeight * 0.34,0,5)

    self.mainPanel:addPanel("Simple_border", 0.25)

    self.mainPanel:addEmblem(0,"emblem_pack.xml/corner_b_14b.png", 1,0, 0,
        4, 0.85)

    self.mainPanel:addEmblem(1,"emblem_pack.xml/corner_a_05.png", 3,3, 18,
        -18, 0.45)

    self.mainPanel:showPanelBG(true)

    --======================================================
    -- Basic Skills row: slots 1,2,3,4
    --======================================================
    local bw = self.buttonWidth
    local gap = self.buttonGap * 0.5

    self:addButton("skill","Q", basicSkillsX,                     groupY + self.buttonHeight + self.buttonGap , "Yin-Yang Shot", "<color=#38B6FF>20</color>", "Ying Yang is a thing, davai test\n <color=#38B6FF>text</color> bro, LAsweww")
    self:addButton("skill","W", basicSkillsX + (bw + gap),         groupY + self.buttonHeight + self.buttonGap, "Spirit Barrage", " ", "spirit_barrage")
    self:addButton("skill","E", basicSkillsX + (bw + gap) * 2,     groupY + self.buttonHeight + self.buttonGap, "Ofuda Throw",    "<color=#38B6FF>15</color>", "ofuda_throw")
    self:addButton("skill","R", basicSkillsX + (bw + gap) * 3,     groupY + self.buttonHeight + self.buttonGap, "Focused Mind",   "SP 30", "focused_mind")

    self:addButton("skill","A", basicSkillsX,                     groupY , "Kick Back", "<color=#38B6FF>20</color>", "kick_back")
    self:addButton("skill","S", basicSkillsX + (bw + gap),         groupY, "Brace", "Free", "brace")
    self:addButton("skill","D", basicSkillsX + (bw + gap) * 2,     groupY, "Hakurei Bless",    "<color=#38B6FF>15</color>", "hakurei_bless")
    self:addButton("skill","F", basicSkillsX + (bw + gap) * 3,     groupY, "Meditation",   " ", "meditation")

    --======================================================
    -- Items row: 1,2
    --======================================================
    self:addButton("item","1", itemsX ,               groupY + self.buttonHeight + self.buttonGap , "Hakurei Charm", "x1", "hakurei_charm")
    self:addButton("item","2", itemsX,   groupY  , "Heal Potion",   "x1", "heal_potion")

    --======================================================
    -- General row: M, Space
    --======================================================
    self:addButton("general","M", generalX,             groupY + self.buttonHeight + self.buttonGap , "Move",     "AP 0.5", "move")
    self:addButton("general","Space", generalX, groupY , "End Turn", "", "end_turn")

    self:setAllButtonsVisible("skill",false)

end

---@Description internal: create a header text object (not part of a button)
function Combat_dock_middle_panel:createHeader(label, posX, posY)
    local headerDock = L_compositeObject:new()
    -- zero-size composite purely to host a text object at this position
    headerDock:init(self.renderContextHost, posX, posY, 0,
    0, 0, 4)
    headerDock:addText(label, 0, 0, 3, .75, 220, 200, 160, 255, 0) -- center aligned, gold-ish
    return headerDock
end

---@Description add one action button (key + panel + name + info) and register it
---@param key string key label, e.g. "1", "Q", "E"
---@param posX number x position (in the same -pos coordinate space as the rest of the dock)
---@param posY number y position
---@param name string skill/item/action name
---@param info string small info line (cost, count, etc.) -- can be ""
function Combat_dock_middle_panel:addButton(group,key, posX, posY, name, info , description)
    -- local btn = L_compositeObject:new()

    if self.buttons[group] == nil then
        self.buttons[group] = {}
    end

    local btn = Dock_button:new()

    btn:init(self.renderContextHost, key, name, posX, posY, self.buttonWidth,
    self.buttonHeight, description, info)

    btn:getPanel():setRegisterFlag(1)
    btn:registerCallback("onHoverEnter", function()
        -- print("hover enter " .. name)
        btn:getPanel():setFrameColor(100, 255,100, 255)


        -- text set
        Combat_Dock_Right_Instance:getSide("skill_des"):setText("skill_name",btn.name)
        Combat_Dock_Right_Instance:getSide("skill_des"):setText("skill_description",btn.description)
        Combat_Dock_Right_Instance:getSide("skill_des"):setText("skill_cost", btn.cost)

    end)

    btn:registerCallback("onHoverLeave", function()
        -- print("hover leave " .. name)
        btn:getPanel():setFrameColor(255, 255, 255, 255)
    end)

    btn:registerCallback("onClick", function()
        print("clicked " .. btn.name)
    end)

    self.buttons[group][key] = btn

end

---@Description update a button's displayed name/info at runtime (e.g. skill swapped, item count changed)
function Combat_dock_middle_panel:updateButton(group,key, name, description, cost, clickable)
    local btn = self.buttons[group][key]
    if btn == nil then
        print("Combat_dock_middle_panel: no button registered for key " .. tostring(key))
        return
    end
    btn:updateButtonInfo(name, description, cost, clickable)
    btn:setVisible(true)
    -- NOTE: this assumes addText returns a pointer whose .text field
    -- is writable from Lua (same assumption used in combat_dock_my_character_info.lua).
    -- If that's not how your binding works, this needs to go through whatever
    -- setter you actually expose (e.g. cpp_TextObject_setText).
end

function Combat_dock_middle_panel:setAllButtonsVisible(targetGroup,value)

    targetGroup = targetGroup or ""

    if targetGroup ~= "" then
        for key, btn in pairs(self.buttons[targetGroup]) do
            btn:setVisible(value)
        end
        return
    end
    for group in pairs(self.buttons) do
        for key, btn in pairs(self.buttons[group]) do
            btn:setVisible(value)
        end
    -- for key, btn in pairs(self.buttons) do
        -- btn:setVisible(false)
    end
end

---@Description 
function Combat_dock_middle_panel:getHoveredButton()

    for group in pairs(self.buttons) do
        for key, btn in pairs(self.buttons[group]) do
            if btn:getPanel():isHovered() then
                return btn:getPanel()
            end
        end
    end
    -- for key, btn in pairs(self.buttons) do
    --     if btn:getPanel():isHovered() then
    --         return btn:getPanel()
    --     end
    -- end
    return nil
end

function Combat_dock_middle_panel:handleInput(key)
    if (key & Signal.mouseLeft) ~= 0 then
        if( key & Signal.isAlted) ~= 0 then
            print("alt + left click")
        elseif (key & Signal.isShifted) ~= 0 then
            print("shift + left click")
        elseif (key & Signal.isCntrled) ~= 0 then
            print("ctrl + left click")
        else
            -- print("just left click")
            if(self:getHoveredButton() ~= nil) then
                self:getHoveredButton():fireCallback("onClick")
            end
        end
    end
end

function Combat_dock_middle_panel:setCurrentCharacter(character)
    -- print("set character " .. character.stats.name)
    print("dump here ")
    
    self:setAllButtonsVisible("skill",false)
    
    for k, v in pairs(character) do 
        for k2 ,v2 in pairs(character.skills) do
            -- self.buttons[k2]:update
            self:updateButton("skill", k2, v2.name,v2.description, v2.costText, (not v2.isPassive))
        end
    end

end


return Combat_dock_middle_panel