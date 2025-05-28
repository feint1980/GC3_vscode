package.path = package.path .. ';../../Lua/TouhouTB/system/?.lua;'

-- require "Character"

---@class Status
---@field description string
---@field target Character
Status =
{
    ---@type string
    description = "",
    ---@type Character
    target = nil
}

function Status:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end
function Status:init(tDescription, tTarget)
    self.description = tDescription
    self.target = tTarget
end
function Status:getDescription()
    return self.description
end

function Status:setDescription(tDescription)
    self.description = tDescription
end
function Status:startTurnEffect()
    --- to be overriden
end
function Status:endTurnEffect()
    --- to be overriden
end