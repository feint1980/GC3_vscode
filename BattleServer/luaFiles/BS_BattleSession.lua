package.path = package.path .. ";../../luaFiles/Characters/?.lua"
require "BS_BattleEvent"
require "BS_Char_Reimu"
require "BS_Char_Yukari"
require "BS_Char_Patchouli"
require "BS_Char_Meiling"
require "BS_Char_Remilia"

--[[
================================================================================
  BS_BattleSession.lua
  Battle Session — lives on BattleLobby as self.session
  Created inside BattleLobby:AppendReady when both players are ready

  Owns:
    - both player endpoints (for broadcast)
    - both formations (BS_Char_* instances)
    - round / turn state
    - the broadcast method (replaces the stub in BS_BattleEvent)

  Usage in BattleLobby:AppendReady:
    self.session = BattleSession:new()
    self.session:init(host, lobbyId, p1EP, p2EP, leftFormation, rightFormation)
    self.session:start()
================================================================================
]]--

-- maps character_id string → child class
-- add new characters here as they are implemented


BattlePhase = {
    READY        = 0,
    ROUND_START  = 1,
    ACTION_PHASE = 2,
    ROUND_END    = 3,
    BATTLE_END   = 4
}


local CHARACTER_CLASS_MAP = {
    S_Reimu     = BS_Char_Reimu,
    S_Yukari    = BS_Char_Yukari,
    S_Patchouli = BS_Char_Patchouli,
    S_Meiling   = BS_Char_Meiling,
    --    = BS_Char_Remilia,
}

---@class BattleSession
---@field lobbyId string
---@field host? pointer of ServerScriptingManager
---@field p1Id string
---@field p2Id string
---@field p1EP? BattleClientEP
---@field p2EP? BattleClientEP
---@field p1Formation table
---@field p2Formation table
---@field currentRound number
---@field turnQueue table
---@field currentChar? BS_Char_*
---@field phase number
BattleSession = {
    lobbyId      = "",
    host         = nil,     -- ServerScriptingManager pointer
    p1Id         = "",      -- playerID string
    p2Id         = "",      -- playerID string
    p1EP         = nil,     -- BattleClientEP
    p2EP         = nil,     -- BattleClientEP
    p1Formation  = {},      -- list of BS_Char_* instances
    p2Formation  = {},      -- list of BS_Char_* instances
    currentRound = 0,
    turnQueue    = {},
    currentChar  = nil,     -- BS_Char_* currently acting
    phase        = -1,     -- BattlePhase enum (defined in BS_global)
    playerSideMap = {},
    playerIDMap = {},
}

--------------------------------------------------------------------------------
--  LIFECYCLE
--------------------------------------------------------------------------------

function BattleSession:new(o)
    o = o or {}
    o.p1Formation = {}
    o.p2Formation = {}
    o.turnQueue   = {}
    setmetatable(o, self)
    self.__index = self
    return o
end

---@param host pointer of ServerScriptingManager
---@param lobbyId string
---@param p1EP BattleClientEP
---@param p2EP BattleClientEP
---@param leftFormation table  raw formation data from lobby { {characterId, cellPosition, stats}, ... }
---@param rightFormation table
function BattleSession:init(host, lobbyId, p1EP, p2EP, leftFormation, rightFormation)
    self.host    = host
    self.lobbyId = lobbyId
    self.p1EP    = p1EP
    self.p2EP    = p2EP
    self.p1Id    = p1EP.id
    self.p2Id    = p2EP.id
    self.phase   = BattlePhase.READY

    self.playerSideMap[self.p1Id] = 1
    self.playerSideMap[self.p2Id] = 2

    self.playerIDMap[1] = self.p1Id
    self.playerIDMap[2] = self.p2Id

    print("[BattleSession] init | lobby:" .. lobbyId
        .. " p1:" .. self.p1Id .. " p2:" .. self.p2Id)

    -- build BS_Char_* instances from raw formation data
    self.p1Formation = self:buildFormation(self.p1Id, leftFormation,1)
    self.p2Formation = self:buildFormation(self.p2Id, rightFormation,2)

    -- local tData = JSON_Encode (self:serializeFormation(self.p1Formation),true)
    -- print(tData)

    self:start()
end

--- Called after init — sends BATTLE_START to both clients then kicks off round 1
function BattleSession:start()
    self.phase = BattlePhase.ROUND_START

    -- share both formations with both players 
    -- Sync the battle field 
    self:broadcast(ClientChannel.Combat, CCombatResponse.Combat_IngameData, CombatIngameData.Sync , { self.lobbyId,
        self.p1Id,
        self.p2Id,
        self:getFormationJSON(self.p1Formation),
        self:getFormationJSON(self.p2Formation),
    })

    print("[BattleSession] battle started — beginning round 1")
    
    BS_BattleEvent.onRoundStart(self)

    -- TM_addTask(function()
    --     BS_BattleEvent.onTurnStartSpeedRoll(self)
    -- end,50)


end

--------------------------------------------------------------------------------
--  FORMATION BUILDER
--------------------------------------------------------------------------------

--- Instantiates BS_Char_* objects from raw formation data sent by client
---@param playerID string
---@param rawFormation table  { { characterId, cellPosition, stats }, ... }
---@param side number (1 is left formation, 2 is right formation)
---@return table  list of BS_Char_* instances
function BattleSession:buildFormation(playerID, rawFormation, side)
    local formation = {}

    print("buildFormation called")
    print("raw formation check ")
    print(rawFormation.name)
    print(rawFormation.index)
    formation.name = rawFormation.name
    formation.owner = playerID
    print(#rawFormation.characters)
    for i = 1, #rawFormation.characters do
        print(rawFormation.characters[i].id)
        -- for k,v in pairs(rawFormation.characters[i].stats) do
            -- print(k .. " " .. v)
        -- end
        local charID = rawFormation.characters[i].stats.ID
        print("charID " .. charID)

        local class = CHARACTER_CLASS_MAP[charID] or BS_Character
        local tChar = class:new(rawFormation.characters[i])

        -- local char = tChar
        if tChar ~= nil then
            -- tChar.side = side
            tChar:setSide(side)
            -- tChar:setOwner(playerID)
            -- print(tChar:getMaxHP())
            table.insert(formation, tChar)
        else
            print("tChar is nil")
        end
    end

    return formation
end

--- Serialize formation for network transmission
---@param formation table
---@return table
function BattleSession:serializeFormation(formation)
    local data = {}
    for _, char in ipairs(formation) do
        table.insert(data, {
            ownerId      = char.userID,
            characterId  = char.id,
            rowPos       = char.rowPos,
            colPos       = char.colPos,
            strength     = char:getStrength(),
            vitality     = char:getVitality(),
            dexterity    = char:getDexterity(),
            agility      = char:getAgility(),
            intelligence = char:getIntelligence(),
            wisdom = char:getWisdom(),
            physicDmg    = char:getPhysicDmg(),
            magicDmg     = char:getMagicDmg(),
            physicDef    = char:getPhysicDef(),
            magicDef     = char:getMagicDef(),
            physicalAccuracy = char:getPhysicalAccuracy(),
            magicalAccuracy  = char:getMagicalAccuracy(),
            evasion      = char:getEvasion(),
            critChance   = char:getCritChance(),
            speed        = char:getSpeed(0),
            deathDoorSurvival = char:getDeathDoorSurvival(),
            maxHp        = char:getMaxHP(),
            maxMana      = char:getMaxMana(),
            maxAP        = char:getMaxAP(),
            maxSP        = char:getMaxSP(),
            currentHP    = char:getCurrentHP(),
            currentMana  = char:getCurrentMana(),
            currentAP    = char:getCurrentAP(),
            currentSP    = char:getCurrentSP(),
        })
    end
    return data
end

function BattleSession:getFormationJSON(formation,indent)
    indent = indent or false
    return JSON_Encode (self:serializeFormation(formation),indent)
end

--------------------------------------------------------------------------------
--  BROADCAST
--  Replaces the stub in BS_BattleEvent — sends to both players via RakNet
--------------------------------------------------------------------------------

---@param channel number   ClientChannel enum
---@param request number   CCombatResponse enum
---@param data table
function BattleSession:broadcast(channel, request,type, data)

    local p1Data = {self.p1EP.guid, self.p1EP.id , type, JSON_Encode(data)}
    local p2Data = {self.p2EP.guid, self.p2EP.id , type, JSON_Encode(data)}

    -- local test = {self.p1EP.guid, self.p1EP.id}

    -- print("p1Data check")
    -- for k,v in pairs(p1Data) do
    --     print(k .. " " ..  v)
    -- end

    BM_sendWrapData(self.host,
        self.p1EP:getIP(), self.p1EP.guid,
        BattlePacketType.ID_TH_TB_BATTLE, channel, request, p1Data)

    BM_sendWrapData(self.host,
        self.p2EP:getIP(), self.p2EP.guid,
        BattlePacketType.ID_TH_TB_BATTLE, channel, request, p2Data)
end

--- Send to one specific player only
---@param playerID string
---@param channel number
---@param request number
---@param data table
function BattleSession:sendToPlayer(playerID, channel, request, data)
    local ep = (playerID == self.p1Id) and self.p1EP or self.p2EP
    if ep == nil then
        print("[BattleSession:sendToPlayer] ERROR: no EP for " .. playerID)
        return
    end
    BM_sendWrapData(self.host,
        ep:getIP(), ep.guid,
        BattlePacketType.ID_TH_TB_BATTLE, channel, request, data)
end

--------------------------------------------------------------------------------
--  TURN QUEUE RECALC
--  Called when a speed-affecting buff/debuff is applied mid-round
--  Re-sorts remaining queue using cached speed rolls — no new dice
--------------------------------------------------------------------------------

function BattleSession:recalcTurnQueue()
    -- exclude currently acting character — they are already mid-turn
    local remaining = {}
    for _, char in ipairs(self.turnQueue) do
        if char ~= self.currentChar then
            table.insert(remaining, char)
        end
    end

    -- re-sort by cached speed (lastSpeedRoll set during onRoundStart)
    table.sort(remaining, function(a, b)
        return a:getSpeed(a.lastSpeedRoll or 0) > b:getSpeed(b.lastSpeedRoll or 0)
    end)

    self.turnQueue = remaining

    -- announce updated order to both clients
    local queueInfo = {}
    for idx, char in ipairs(self.turnQueue) do
        table.insert(queueInfo, {
            order       = idx,
            characterId = char.id,
            ownerId     = char.userID,
        })
    end

    print("[BattleSession] turn queue recalculated")

    -- self:broadcast(ClientChannel.Combat, CCombatResponse.Combat_TurnQueue_Update, {
    --     turnQueue = queueInfo,
    -- })
end

--------------------------------------------------------------------------------
--  ACTION HANDLER
--  Entry point for incoming player actions — called from network handler
--------------------------------------------------------------------------------

--[[
  actionData structure (sent by client):
  {
      type        = "ATTACK" | "MOVE" | "STANCE" | "CONCEDE",
      actorId     = string,     -- characterId of acting character
      targetCell  = number,     -- 1~9 grid cell (ATTACK / MOVE)
      skillId     = string,     -- skill used (ATTACK)
  }
]]--

---@param playerID string   who sent this action
---@param actionData table
function BattleSession:onPlayerAction(playerID, actionData)

    -- validate: is it actually this player's turn?
    if self.currentChar == nil then
        print("[BattleSession:onPlayerAction] ERROR: no current character")
        self:sendToPlayer(playerID, ClientChannel.Combat,
            CCombatResponse.Combat_Invalid_Action, { reason = "no_active_turn" })
        return
    end

    if self.currentChar.userID ~= playerID then
        print("[BattleSession:onPlayerAction] ERROR: not " .. playerID .. "'s turn")
        self:sendToPlayer(playerID, ClientChannel.Combat,
            CCombatResponse.Combat_Invalid_Action, { reason = "not_your_turn" })
        return
    end

    local actionType = actionData.type

    if actionType == "CONCEDE" then
        local winnerId = (playerID == self.p1Id) and self.p2Id or self.p1Id
        BS_BattleEvent.onBattleEnd(self, winnerId)
        return
    end

    if actionType == "STANCE" then
        -- free action — no AP cost, no turn consumed
        if self.currentChar.switchStance == nil then
            self:sendToPlayer(playerID, ClientChannel.Combat,
                CCombatResponse.Combat_Invalid_Action, { reason = "no_stance" })
            return
        end
        self.currentChar:switchStance(self)
        -- do NOT advance turn — player still acts
        return
    end

    if actionType == "MOVE" then
        self:handleMove(actionData)
        return
    end

    if actionType == "ATTACK" then
        self:handleAttack(actionData)
        return
    end

    print("[BattleSession:onPlayerAction] unknown action type: " .. tostring(actionType))
end

--------------------------------------------------------------------------------
--  MOVE HANDLER
--------------------------------------------------------------------------------

---@param actionData table { actorId, targetCell }
function BattleSession:handleMove(actionData)
    local actor      = self:findCharById(self.currentChar.userID, actionData.actorId)
    local targetCell = actionData.targetCell

    if actor == nil then
        print("[BattleSession:handleMove] actor not found")
        return
    end

    -- validate target cell is empty in own formation
    local formation = (actor.userID == self.p1Id) and self.p1Formation or self.p2Formation
    for _, char in ipairs(formation) do
        if char ~= actor and char.cHp > 0 then
            local charCell = (char.rowPos - 1) * 3 + char.colPos
            if charCell == targetCell then
                self:sendToPlayer(actor.userID, ClientChannel.Combat,
                    CCombatResponse.Combat_Invalid_Action, { reason = "cell_occupied" })
                return
            end
        end
    end

    -- apply move
    local newRow = math.ceil(targetCell / 3)
    local newCol = ((targetCell - 1) % 3) + 1
    actor.rowPos = newRow
    actor.colPos = newCol

    print(string.format("[BattleSession:handleMove] %s moved to cell %d (row%d col%d)",
        actor.stats.name, targetCell, newRow, newCol))

    -- self:broadcast(ClientChannel.Combat, CCombatResponse.Combat_Move_Result, {
    --     characterId = actor.id,
    --     ownerId     = actor.userID,
    --     targetCell  = targetCell,
    -- })

    self:advanceTurn()
end

--------------------------------------------------------------------------------
--  ATTACK HANDLER
--------------------------------------------------------------------------------

---@param actionData table { actorId, targetCell, skillId }
function BattleSession:handleAttack(actionData)
    local actor      = self.currentChar
    local targetCell = actionData.targetCell

    -- find defender at target cell in opponent formation
    local opponentFormation = (actor.userID == self.p1Id)
        and self.p2Formation or self.p1Formation

    local defender = nil
    for _, char in ipairs(opponentFormation) do
        if char.cHp > 0 then
            local charCell = (char.rowPos - 1) * 3 + char.colPos
            if charCell == targetCell then
                defender = char
                break
            end
        end
    end

    if defender == nil then
        print("[BattleSession:handleAttack] no target at cell " .. tostring(targetCell))
        self:sendToPlayer(actor.userID, ClientChannel.Combat,
            CCombatResponse.Combat_Invalid_Action, { reason = "invalid_target" })
        return
    end

    -- TODO: look up skillId to determine rawDmg, isMagic, isAOE, AP cost
    -- for now using base physical attack as placeholder
    local rawDmg = actor:getPhysicDmg()
    local isMagic = false
    local isAOE   = false
    local apCost  = 1.0

    if not actor:canAfford(apCost) then
        self:sendToPlayer(actor.userID, ClientChannel.Combat,
            CCombatResponse.Combat_Invalid_Action, { reason = "not_enough_ap" })
        return
    end

    actor:spendAP(apCost)

    -- resolve attack through full pipeline
    local dmgInfo = BS_BattleEvent.resolveAttack(actor, defender, rawDmg, isMagic, isAOE, self)

    -- broadcast result
    if dmgInfo ~= nil then
        -- self:broadcast(ClientChannel.Combat, CCombatResponse.Combat_Attack_Result, {
        --     attackerId  = actor.id,
        --     defenderId  = dmgInfo.defender.id,
        --     finalDmg    = dmgInfo.finalDmg,
        --     isCrit      = dmgInfo.isCrit,
        --     absorbed    = dmgInfo.absorbed,
        --     defenderHp  = dmgInfo.defender.cHp,
        -- })
    end

    self:advanceTurn()
end

--------------------------------------------------------------------------------
--  TURN ADVANCEMENT
--------------------------------------------------------------------------------

function BattleSession:advanceTurn()
    local result = BS_BattleEvent.onTurnEnd(self.currentChar, self)
    self.currentChar = nil

    if result == "BATTLE_END" then
        return
    end

    if result == "ROUND_END" then
        BS_BattleEvent.onRoundEnd(self)
        BS_BattleEvent.onRoundStart(self)
    end

    -- pop next from queue
    local nextChar = table.remove(self.turnQueue, 1)
    self.currentChar = nextChar
    self.phase = BattlePhase.ACTION_PHASE

    BS_BattleEvent.onTurnStart(nextChar, self)
end

--------------------------------------------------------------------------------
--  HELPERS
--------------------------------------------------------------------------------

--- Find a character by id within a player's formation
---@param playerID string
---@param charId string
---@return BS_Character|nil
function BattleSession:findCharById(playerID, charId)
    local formation = (playerID == self.p1Id) and self.p1Formation or self.p2Formation
    for _, char in ipairs(formation) do
        if char.id == charId then return char end
    end
    return nil
end

--- Called by network handler on disconnect
---@param playerID string
function BattleSession:onPlayerDisconnect(playerID)
    print("[BattleSession] player disconnected: " .. playerID)
    local winnerId = (playerID == self.p1Id) and self.p2Id or self.p1Id

    -- self:broadcast(ClientChannel.Combat, CCombatResponse.Combat_Opponent_Disconnect, {
    --     disconnectedId = playerID,
    -- })

    BS_BattleEvent.onBattleEnd(self, winnerId)
end
