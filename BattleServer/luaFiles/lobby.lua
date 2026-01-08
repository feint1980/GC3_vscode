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

function BattleLobby:removePlayer(playerGUID)
    for i = 1, #self.battleClientEP_List do
        if self.battleClientEP_List[i].GUID == playerGUID then
            print("player " .. playerGUID .. " removed from lobby " .. self.id .. "(" .. self.name .. ")")
            table.remove(self.battleClientEP_List, i)
            break
        end
    end
end

BattleLobby_List = {}

function BattleLobby_ResetList()
    BattleLobby_List = {}
end


-- function BattleLobby_AddLobby(id,name , hostID, hostGUID, hostIP)
--     local lobby = BattleLobby:new()
--     lobby:init(id,name)
--     lobby:addPlayer(hostID, hostGUID, hostIP)
--     table.insert(BattleLobby_List,lobby)
-- end


-- function BattleLobby_FinalizeLobbies
