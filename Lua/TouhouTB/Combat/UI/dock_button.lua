package.path = package.path .. ';../../Lua/system/objects/?.lua;' .. ';../../Lua/TouhouTB/Combat/UI/?.lua;'

require "compositeObject"

Dock_button = {}
Dock_button.__index = Dock_button
function Dock_button:new()
    local o = setmetatable({}, self)
    o.name = "Button Name"
    o.description = "Button Description"
    o.cost = "Cost (MP,AP,etc)" -- there are rules for this
    o.key = "Unassigned key"
    o.keyInstance = nil  --- tTextObject 
    o.nameInstance = nil
    o.costInstance = nil
    o.clickable = true
    -- o.
    ---@type L_compositeObject
    o.panel = nil -- compositeObject

    return o

end

---@param renderContextHost pointer instance of RenderContext
---@param key string key label, e.g. "1", "Q", "E"
---@param name string skill/item/action name
---@param posX number x position (in the same -pos coordinate space as the rest of the dock)
---@param posY number y position
---@param width number width
---@param height number height
---@param description string small info line (cost, count, etc.) -- can be ""
---@param cost string small info line (cost, count, etc.) -- can be ""
function Dock_button:init(renderContextHost,key, name,posX, posY, width, height, description, cost)
    self.key = key
    self.name = name
    self.description = description
    self.cost = cost

    self.panel = L_compositeObject:new()
    self.panel:init(renderContextHost, posX, posY, width, height, 0, 4)
    self.panel:addPanel("Basic_border", 0.3)
    self.panel:showPanelBG(true)
    self.panel:setPanelBGColor(20, 20, 25, 220)
    self.panel:setPanelBGScale(0.95)

    -- key label, top-left corner of the button
    self.keyInstance = self.panel:addText(key,
        -(width * 0.5) + 10, (height * 0.5) - 14,
        1, 0.8,
        210, 210, 150, 255,
        0)

    -- name, center of the button (small, may wrap visually depending on your text renderer)
    self.nameInstance =  self.panel:addText(name,
        0, 4,
        3, 0.55,
        230, 230, 230, 255,
        0)

    -- info line, bottom of the button
    -- if self.cost ~= "" then
    self.costInstance = self.panel:addText(self.cost,
            0, -(height * 0.5) + 14,
            3, 0.6,
            170, 200, 255, 255,
            0)
    -- end

end

function Dock_button:updateButtonInfo(name, description, cost , clickable)
    if clickable == false then
        CompositeObjectText_setText(self.keyInstance, " ")
    else
        CompositeObjectText_setText(self.keyInstance, self.key)
    end

    self.name = name
    CompositeObjectText_setText(self.nameInstance, self.name)


    self.description = description
    self.cost = cost
    CompositeObjectText_setText(self.costInstance, self.cost)

end

function Dock_button:getPanel()
    return self.panel
end

function Dock_button:setVisible(visible)
    self.panel:setVisible(visible)
end

function Dock_button:registerCallback(event, callback)
    self.panel:registerCallback(event, callback)
end

function Dock_button:getValue(name)
    return self[name]
end


return Dock_button