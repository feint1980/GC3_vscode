require "battle_handle_clients"

BattleLobby = {
    id = "",
    name  = "",
    battleClientEP_List = {},
    lobbyState =  BattleLobbyState.CLOSED
}

function BattleLobby:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function BattleLobby:init(id,name)
    self.id = id
    self.name = name
    self.Battle_LobbyState = BattleLobbyState.OPEN
end

function BattleLobby:addPlayer(playerID, playerGUID, playerIP)
    local clientEP = BattleClientEP:new()
    clientEP:init(playerID, playerGUID, playerIP)
    if #self.battleClientEP_List < 2 then 
        print("player " .. playerID .. "(" .. playerGUID ..  ") added to lobby " .. self.id)
        table.insert(self.battleClientEP_List, clientEP)
    else
        print("lobby " .. self.id .. " is full")
    end
end