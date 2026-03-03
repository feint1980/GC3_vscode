require "BS_handle_clients"

BattleLobby = {
    id = "",
    name  = "",
    password = "",
    battleClientEP_List = {},
    battleClientEP_Map = {},
    lobbyState =  BattleLobbyState.CLOSED,
    formation_Map = {}
}

function BattleLobby:new(o)
    o = o or {
        battleClientEP_List = {}
    }
    setmetatable(o, self)
    self.__index = self
    return o
end

function BattleLobby:init(t_id,t_name,t_password)
    self.id = t_id
    self.name = t_name
    self.password = t_password
    self.lobbyState = BattleLobbyState.OPEN
end

function BattleLobby:addPlayer(playerID, playerGUID, playerIP)
    local clientEP = BattleClientEP:new()
    local indexSlot = #self.battleClientEP_List + 1
    if #self.battleClientEP_List > 0 then
        if self.battleClientEP_List[1] ~= nil then
            if self.battleClientEP_List[1].index == 2 then
                indexSlot = 1
            else
                indexSlot = 2
            end
        end
    end
    clientEP:init(playerID, playerGUID, playerIP, indexSlot)
    if #self.battleClientEP_List < 2 then 
        print(" BattleLobby:addPlayer")
        print("player " .. playerID .. "(" .. playerGUID ..  ") added to lobby " .. self.id)

        table.insert(self.battleClientEP_List, clientEP)
    end
    self.battleClientEP_Map[playerID] = clientEP
    if #self.battleClientEP_List >= 2 then 
        print("lobby " .. self.id .. " is full")
        self.lobbyState = BattleLobbyState.FULL
    end

    print("list of players")
    for i = 1, #self.battleClientEP_List do
        print(self.battleClientEP_List[i].id .. "(" .. self.battleClientEP_List[i].guid .. ")")
    end
    -- append to map list

end

function BattleLobby:removePlayer(playerGUID)
    -- print("removing player " .. playerGUID .. " from lobby " .. self.id .. "(" .. self.name .. ")")
    for i = 1, #self.battleClientEP_List do
        -- print("comparing " .. self.battleClientEP_List[i].guid .. " with " .. playerGUID)
        if self.battleClientEP_List[i].guid == playerGUID then
            print("player " .. playerGUID .. " removed from lobby " .. self.id .. "(" .. self.name .. ")")
            self.battleClientEP_Map[self.battleClientEP_List[i].id] = nil
            table.remove(self.battleClientEP_List, i)
            break
        end
    end

    -- self check 
    if #self.battleClientEP_List == 0 then
        print("lobby " .. self.id .. " is empty")
        self.lobbyState = BattleLobbyState.EXPIRED
    elseif #self.battleClientEP_List == 2 then
        print("lobby " .. self.id .. " is full")
        self.lobbyState = BattleLobbyState.FULL
    elseif #self.battleClientEP_List == 1 then
        print("lobby " .. self.id .. " is waiting")
        self.lobbyState = BattleLobbyState.OPEN
    end

end

function BattleLobby:addFormation(playerID, formation)
    self.formation_Map[playerID] = formation
end

function BattleLobby:getSize()
    return #self.battleClientEP_List
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

    local lobbyList = {}
    
    for k,v in pairs(BattleLobby_List) do
        print("replicated table check ")
        lobbyList[k] = {}
        lobbyList[k].id = v.id
        lobbyList[k].name = v.name
        lobbyList[k].password = v.password
        lobbyList[k].lobbyState = v.lobbyState
        lobbyList[k].battleClientEP_List = {}
        setmetatable(lobbyList[k].battleClientEP_List, {__mode = "kv"})
        
        -- print("k " .. k)
        print("id" .. v.id)
        print("name" .. v.name)
        print("password" .. v.password)
        print("lobbyState" .. v.lobbyState)
        print(#BattleLobby_List[k].battleClientEP_List .. " players")
        for i = 1, #v.battleClientEP_List do
            print(v.battleClientEP_List[i].id .. "(" .. v.battleClientEP_List[i].guid .. ")")
            lobbyList[k].battleClientEP_List[i] = {}
            lobbyList[k].battleClientEP_List[i].id = v.battleClientEP_List[i].id
            lobbyList[k].battleClientEP_List[i].guid = v.battleClientEP_List[i].guid
        end
    end

    local tData = JSON_Encode(lobbyList)
    -- print("json check " .. JSON_Encode(lobbyList,true))

    BM_sendWrapData(host,BM_getMainServerIP(host),BM_getMainServerGUID(host), BattlePacketType.ID_TH_INTERNAL, MainServerChanel.Lobby, PaperWorkRequest.LobbiesListUpdate , {tData})
end
-- 
