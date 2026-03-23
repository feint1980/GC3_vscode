
require "combat_turndisplayer_wrapper"


---@class CombatTurnDisplayer
CombatTurnDisplayer = {
    host = nil
}

function CombatTurnDisplayer:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function CombatTurnDisplayer:init(host)
    self.host = host
end

function CombatTurnDisplayer:addPortrait(characterID,side)
    CTD_AddPortrait(self.host, characterID,side)
end









