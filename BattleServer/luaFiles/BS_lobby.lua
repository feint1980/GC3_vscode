require "BS_handle_clients"
require "BS_BattleSession"

---@class BattleLobby
---@field id string
---@field name string
---@field password string
---@field battleClientEP_List table of BattleClientEP (vector)
---@field battleClientEP_Map table of BattleClientEP (map)
---@field lobbyState number (BattleLobbyState)
---@field formation_Map table of Formation (map)
---@field playerIndexMap table of number (map)
---@field leftFormation? BattleFormation
---@field rightFormation? BattleFormation
---@field readyCount number
---@field networkHost? pointer of BattleMain(C++)
---@field battleSession? BattleSession
BattleLobby = {
    id = "",
    name  = "",
    password = "",
    battleClientEP_List = {},
    battleClientEP_Map = {},
    lobbyState =  BattleLobbyState.CLOSED,
    formation_Map = {},
    playerIndexMap = {},
    leftFormation = nil,
    rightFormation = nil,
    readyCount = 0,
    networkHost = nil,
    battleSession = nil
}

function BattleLobby:new(o)
    o = o or {
        -- battleClientEP_List = {}
    }
    setmetatable(o, self)
    o.battleClientEP_List = {}
    o.battleClientEP_Map = {}
    o.formation_Map = {}
    o.playerIndexMap = {}
    self.__index = self
    return o
end

function BattleLobby:init( networkHost,t_id,t_name,t_password)
    self.id = t_id
    self.name = t_name
    self.password = t_password
    self.lobbyState = BattleLobbyState.OPEN
    self.networkHost = networkHost
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

function MergeTable(t1, t2)
    if t1 == nil then return t2 end
    if t2 == nil then return t1 end
    
    local result = {}
    for k, v in pairs(t1) do result[k] = v end
    for k, v in pairs(t2) do result[k] = v end
    return result
end

function BattleLobby:broadCastToClient(channel,request, data, attachVerifiable)
    attachVerifiable = attachVerifiable or false

    local verifiableData = {}
    if attachVerifiable then
        verifiableData = self:getVerifiableData(1)
        data = MergeTable(data, verifiableData)
    end

    for i = 1, #BattleLobby_List[self.id].battleClientEP_List do
        BM_sendWrapData(self.networkHost,BattleLobby_List[self.id].battleClientEP_List[i]:getIP(),BattleLobby_List[self.id].battleClientEP_List[i].guid,BattlePacketType.ID_TH_TB_BATTLE,channel,request,data)
    end

end

function BattleLobby:getVerifiableData(index)
    local data = {}
    if BattleLobby_List[self.id].battleClientEP_List[index] ~= nil then
        data = {BattleLobby_List[self.id].battleClientEP_List[index].guid,
    BattleLobby_List[self.id].battleClientEP_List[index].id}
    end
    return data
end


function BattleLobby:updateFormation(playerID)
    -- print("formation " .. self.formation_Map[playerID].id .. " updating")
    -- self.formation_Map[playerID]:initStat()
    -- print("formation " .. self.formation_Map[playerID].id .. " updated")
    -- print("data check")
    -- for k,v in pairs(self.formation_Map[playerID]) do
        -- print("k " .. k)
    -- end


    
end

function BattleLobby:AppendReady(playerID, index)
    
    if self.formation_Map[playerID] == nil then 
        LOG_COOKED("K282","BattleLobby:AppendReady player " .. playerID .. " has no formation")
        return
    end
    self.readyCount = self.readyCount + 1
    self.playerIndexMap[playerID] = index

    if self.playerIndexMap[playerID] == 1 then
        self.leftFormation = self.formation_Map[playerID]
    elseif self.playerIndexMap[playerID] == 2 then
        self.rightFormation = self.formation_Map[playerID]
    else 
        LOG_COOKED("K283","BattleLobby:AppendReady player " .. playerID .. " has no index or wrong index " .. self.playerIndexMap[playerID])
        return
    end

    if self.readyCount >= 2 then
        print("ready player check")
        if self.leftFormation == nil then
            LOG_COOKED("K284","BattleLobby:AppendReady lobby " .. self.id .. " has no left formation")
            return
        end
        if self.rightFormation == nil then
            LOG_COOKED("K285","BattleLobby:AppendReady lobby " .. self.id .. " has no right formation")
            return
        end
        self.lobbyState = BattleLobbyState.INGAME

        print("precheck")


        if self.battleSession == nil then
            self.battleSession = BattleSession:new()
        end
        self.battleSession:init(self.networkHost, self.id,self.battleClientEP_List[1], self.battleClientEP_List[2], self.leftFormation, self.rightFormation)


        -- self.battleSession:start()
        -- self.battleSession:broadcast(ClientChannel.Combat,CCombatResponse.Combat_Match_Start, {"Match Start", self.battleSession:get})
        -- self:broadCastToClient(ClientChannel.Combat,CCombatResponse.Combat_Match_Start,{"Match Start"},true )

    end
end

function BattleLobby:getFieldJSON()
    local data = {}

end


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
