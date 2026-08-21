package.path = package.path .. ';../../Lua/TouhouTB/Combat/?.lua;'

require "CC_Event"

CombatCharacter = {}
CombatCharacter.__index = CombatCharacter

---@param host pointer cpp CombatCharacter instance
---@param characterID string
---@param side number
---@param fieldHost pointer cpp CombatField instance (needed to route calls through CombatField bindings)
function CombatCharacter:new(host, characterID, side, fieldHost)
    local o = setmetatable({}, self)
    o.host = host
    o.characterID = characterID
    o.side = side
    o.fieldHost = fieldHost
    o.key = characterID .. "_" .. tostring(side)
    return o
end

---@Description Start a lerped move toward the given cell. Fires "<key>_moveComplete" when done.
---Routed through CombatField - CombatField resolves the target slot internally.
---@param col number
---@param row number
---@param duration number seconds
function CombatCharacter:moveToCell(col, row, duration)
    CF_CharacterMoveToCell(self.fieldHost, self.characterID, self.side, col, row, duration)
end

---@Description Play an animation. loop=false fires "<key>_animComplete" when it finishes.
---@param animName string
---@param loop boolean
function CombatCharacter:playAnimation(animName, loop)
    if loop == nil then loop = false end
    CF_CharacterPlayAnimation(self.fieldHost, self.characterID, self.side, animName, loop)
end

---@Description Yield until the current move finishes. Call from inside a coroutine.
function CombatCharacter:waitMoveComplete()
    CC_Event.wait(self.key .. "_moveComplete")
end

---@Description Yield until the current one-shot animation finishes. Call from inside a coroutine.
function CombatCharacter:waitAnimComplete()
    CC_Event.wait(self.key .. "_animComplete")
end

---@Description Get the value of a stat.
---@param statName string
function CombatCharacter:getStat(statName)
    
end

function CombatCharacter:getStatStr(statName)

end