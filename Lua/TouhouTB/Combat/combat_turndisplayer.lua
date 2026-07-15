package.path = package.path .. ';../../Lua/system/event/?.lua;'

require "TaskManager"
require "EventPipeline"

require "combat_turndisplayer_wrapper"

---@class CombatTurnDisplayer
CombatTurnDisplayer = {}
CombatTurnDisplayer.__index = CombatTurnDisplayer

function CombatTurnDisplayer:new()
    local o = setmetatable({}, self)
    o.host = nil

    self.__index = self
    return o
end

function CombatTurnDisplayer:init(host)
    self.host = host
end

function CombatTurnDisplayer:addIcon(characterID,side,order)
    CTD_AddIcon(self.host, characterID,side,order)
end

function CombatTurnDisplayer:updateOrder()
    CTD_UpdateOrder(self.host)
end

function CombatTurnDisplayer:getCharacterIcon(characterID,side)
    return CTD_GetCharacterIcon(self.host,characterID,side)
end

function CombatTurnDisplayer:setUpdateSpeedChange(value)
    CTD_SetUpdateSpeedChange(self.host,value)
end

function CombatTurnDisplayer:setSelected(character,side)
    print("CombatTurnDisplayer:setSelected " .. character .. " " .. side)
    CTD_SetSelected(self.host,character,side)
end

------ Event pipeline

EventPipeline.on("TURNDISPLAYER_SpeedChange", {
    {
        type = "instant",
        fn   = function(data)
            print("testttt TURNDISPLAYER_SpeedChange called ")
        end,
    }
}
)

EventPipeline.on("TURNDISPLAYER_SetSelection", {
    {
        type = "instant",
        fn   = function(data)
            print("testttt TURNDISPLAYER_SetSelection called ")
        end,
    },
    {
        type = "poll",
        condition = function()
            return EP_PollSignals["TurnDisplayerIsReady"] == true
            end,
        fn        = function(data)
            print("[poll] RollUpdate done")

            TM_addTask(function()
                TurnDisplayer_instance:setSelected(data.characterID,data.side)
            end
            ,30)
            EP_ClearPollSignal("TurnDisplayerIsReady")
        end,
    }
})
