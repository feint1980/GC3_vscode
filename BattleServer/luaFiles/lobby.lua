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
    -- print("removing player " .. playerGUID .. " from lobby " .. self.id .. "(" .. self.name .. ")")
    for i = 1, #self.battleClientEP_List do
        -- print("comparing " .. self.battleClientEP_List[i].guid .. " with " .. playerGUID)
        if self.battleClientEP_List[i].guid == playerGUID then
            print("player " .. playerGUID .. " removed from lobby " .. self.id .. "(" .. self.name .. ")")
            table.remove(self.battleClientEP_List, i)
            break
        end
    end

    -- self check 
    if #self.battleClientEP_List == 0 then
        print("lobby " .. self.id .. " is empty")
        self.lobbyState = BattleLobbyState.EXPIRED
    end
    -- BattleLobby_UpdateLobbiesStatus()

end

BattleLobby_List = {}

function BattleLobby_ResetList()
    BattleLobby_List = {}
end


function BattleLobby_UpdateLobbiesStatus()
    for k,v in pairs(BattleLobby_List) do
        if v.lobbyState == BattleLobbyState.EXPIRED then
            print("removing expired lobby " .. v.id)
            BattleLobby_List[k] = nil
        end
    end
end

---@Description send update of lobbies to main server
---@host pointer instance of ServerScriptingManager
function BattleLobby_Notify_LobbiesStates(host)
    BM_sendWrapData(host,BM_getMainServerIP(host),BM_getMainServerGUID(host), BattlePacketType.ID_TH_INTERNAL, MainServerChanel.Lobby, PaperWorkRequest.LobbiesListUpdate , {JSON_Encode(BattleLobby_List)})
end

-- function BattleLobby_FinalizeLobbies
