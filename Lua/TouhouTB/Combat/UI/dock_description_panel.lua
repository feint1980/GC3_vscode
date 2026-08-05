package.path = package.path .. ';../../Lua/system/objects/?.lua;' .. ';../../Lua/TouhouTB/Combat/UI/?.lua;'

require "compositeObject"

Dock_description_panel = {}
Dock_description_panel.__index = Dock_description_panel


function Dock_description_panel:new()
    local o = setmetatable({}, self)
    -- o.sideName = ""
    o.textObjs = {}
    o.lineObjs = {}
    o.panel = nil
    return o
end

function Dock_description_panel:init(renderContextHost, posX, posY, width, height, angle, depth)
    self.panel = L_compositeObject:new()
    self.panel:init(renderContextHost, posX, posY, width, height, angle, depth)
    self.panel:addPanel("Basic_border", 0.25)
    self.panel:showPanelBG(true)
    self.panel:addEmblem(1,"emblem_pack.xml/corner_b_05.png", 15,15, 0,
        10, 0.0)

end

function Dock_description_panel:getPanel()
    return self.panel
end

function Dock_description_panel:addTextInstance(name, value, offsetPosX, offsetPosY, alignment, scale, colorR, colorG, colorB, colorA)
    local textObj = self.panel:addText(value, offsetPosX, offsetPosY, 3,
    0.85, 255, 255, 255, 255, 0)
    self.textObjs[name] = textObj

end

function Dock_description_panel:getTextInstance(name)
    return self.textObjs[name]
end

function Dock_description_panel:setText(textInstanceName, value)
    if self.textObjs[textInstanceName] == nil then
        return
    end

    CompositeObjectText_setText(self.textObjs[textInstanceName], value)
end

function Dock_description_panel:setTextColor(textInstanceName, colorR, colorG, colorB, colorA)
    if self.textObjs[textInstanceName] == nil then
        return
    end

    CompositeObjectText_setTextColor(self.textObjs[textInstanceName], colorR, colorG, colorB, colorA)
end

function Dock_description_panel:setTextScale(textInstanceName, scale)
    if self.textObjs[textInstanceName] == nil then
        return
    end

    CompositeObjectText_setScale(self.textObjs[textInstanceName], scale)
end

function Dock_description_panel:setTextAlignment(textInstanceName, alignment)
    if self.textObjs[textInstanceName] == nil then
        return
    end

    CompositeObjectText_setAligment(self.textObjs[textInstanceName], alignment)
end

function Dock_description_panel:setTextOffset(textInstanceName, offsetPosX, offsetPosY)
    if self.textObjs[textInstanceName] == nil then
        return
    end

    CompositeObjectText_setPositionOffset(self.textObjs[textInstanceName], offsetPosX, offsetPosY)

end

function Dock_description_panel:setTextWithOpt(textInstanceName, opts)
    if self.textObjs[textInstanceName] == nil then
        return
    end
    opts = opts or {}
    if opts.text ~= nil then 
        CompositeObjectText_setText(self.textObjs[textInstanceName], opts.text)
    end
    if opts.posX ~= nil or opts.posY ~= nil then
        CompositeObjectText_setPositionOffset(self.textObjs[textInstanceName], opts.posX or 0, opts.posY or 0)
    end
    if opts.alignment ~= nil then
        CompositeObjectText_setAligment(self.textObjs[textInstanceName], opts.alignment)
    end
    if opts.scale ~= nil then
        CompositeObjectText_setScale(self.textObjs[textInstanceName], opts.scale)
    end
    if opts.colorR ~= nil or opts.colorG ~= nil or opts.colorB ~= nil or opts.colorA ~= nil then
        CompositeObjectText_setTextColor(self.textObjs[textInstanceName], opts.colorR or 1, opts.colorG or 1, opts.colorB or 1, opts.colorA or 1)
    end

end