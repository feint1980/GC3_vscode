--- Battle server, lobby section
package.path = package.path .. ";../luaFiles/?.lua" ..  ";../luaFiles/Characters/?.lua" 


require "battleWrapper"
require "BS_global"
require "BS_handle_clients"
require "BS_formation"
require "BS_Character"
--- MARK:Main server

InternalPacketHandling[MainServerChanel.Lobby][LobbyResponse.Lobby_Create_Request] = function(host, channel, request,data,ip, guid)

    print("create lobby detected")

    -- print(data)
    local tTargetGUID, targetID, serverGUID , combineData = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|([^|]+)|$")

    local lobbyName, lobbyPassword = string.match(combineData, "^{(.-)%$(.-)}$")

    print("tTargetGUID " .. tTargetGUID)
    print("targetID " .. targetID)
    print("serverGUID " .. serverGUID)

    print("lobby name " .. lobbyName)
    print("lobby password " .. lobbyPassword)
    local lobbyID =  BM_CreateLobby(host,lobbyName,lobbyPassword)

    BattleLobby_List[lobbyID] = BattleLobby:new()
    BattleLobby_List[lobbyID]:init(host,lobbyID,lobbyName,lobbyPassword)

    -- BM_removeFromWhitelist_ByGUID(tTargetGUID) --- 
    BM_addToWhitelist(tTargetGUID,targetID) -- add the user to whitelist

    BM_sendWrapData(host, ip, guid, BattlePacketType.ID_TH_INTERNAL, MainServerChanel.Lobby, LobbyResponse.Lobby_Create_Response , {tTargetGUID,targetID,serverGUID,lobbyID,combineData}) -- Send to the client request the lobby 
    BattleLobby_Notify_LobbiesStates(host)
    BS_Lobbies_Notify_ClientChanges(host,lobbyID)

    Request_ClientOwnedCharacters_From_MainServer(host, lobbyID,tTargetGUID, targetID)

    -- Request_Formation_From_MainServer(host, tTargetGUID, targetID)
    -- add lobby to list
end

InternalPacketHandling[MainServerChanel.Lobby][LobbyResponse.Lobby_Join_Request_WL] = function(host, channel, request,data,ip, guid)
    print("Add client to whitelist")

    local tTargetGUID, targetID = string.match(data, "^|([^|]+)|([^|]+)|$")

    BM_removeFromWhitelist_ByID(targetID)
    -- BM_removeFromWhitelist_ByGUID(tTargetGUID)

    BM_addToWhitelist(tTargetGUID,targetID)

    
end

--- MARK:Client 

ClientPacketHandling[ClientChannel.Lobby][CLobbyResponse.Lobby_Join_Request] = function(host, channel, request,data,ip, guid)

    print("join lobby detected from " .. guid)

    local clientGUID, clientID, lobbyID = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|$")

    print("clientGUID " .. clientGUID)
    print("clientID " .. clientID)
    print("lobbyID " .. lobbyID)

    local joinResult =  BM_JoinLobby(host,clientGUID,clientID,lobbyID,ip)

    if BattleClientEP_List[clientGUID] == nil then 
        print("fresh player, adding to list")
        BattleClientEP_List[clientGUID] = BattleClientEP:new()
        BattleClientEP_List[clientGUID]:init(clientID,clientGUID,ip)
    end

    if  BattleClientEP_List[clientGUID] ~= nil then
        if joinResult == true then
            BattleLobby_List[lobbyID]:addPlayer(clientID, clientGUID, BattleClientEP_List[clientGUID]:getIP())
            BattleClientEP_List[clientGUID]:joinLobby(lobbyID)
        end
    end

    BM_sendWrapData(host, ip, guid, BattlePacketType.ID_TH_TB_BATTLE, ClientChannel.Lobby, CLobbyResponse.Lobby_Join_Response , {clientGUID,clientID,lobbyID , tostring(joinResult) , "Unable to join lobby"})

    -- for k,v in pairs(BattleLobby_List) do
    --     print("lobbyID " .. k)
    --     print("lobbyName " .. v.name)
    -- end

    BattleLobby_Notify_LobbiesStates(host)

    Request_ClientOwnedCharacters_From_MainServer(host, lobbyID,clientGUID, clientID)

    -- Request_Formation_From_MainServer(host, clientGUID, clientID)

end


function BS_Lobbies_Notify_ClientChanges(host,lobbyID)

    local playerList = {}
    for i = 1, #BattleLobby_List[lobbyID].battleClientEP_List do
        print("client #" .. i)
        print("\tclientID " .. BattleLobby_List[lobbyID].battleClientEP_List[i].id)
        print("\tclientGUID " .. BattleLobby_List[lobbyID].battleClientEP_List[i].guid)
        local clientData = {}
        clientData.id = BattleLobby_List[lobbyID].battleClientEP_List[i].id
        clientData.guid = BattleLobby_List[lobbyID].battleClientEP_List[i].guid
        clientData.index = BattleLobby_List[lobbyID].battleClientEP_List[i].index
        clientData.readyState = BattleLobby_List[lobbyID].battleClientEP_List[i].readyState
        playerList[clientData.guid] = clientData
        -- table.insert(lobbyList,clientData)
    end

    for i = 1, #BattleLobby_List[lobbyID].battleClientEP_List do
        BM_sendWrapData(host,BattleLobby_List[lobbyID].battleClientEP_List[i]:getIP(),BattleLobby_List[lobbyID].battleClientEP_List[i].guid,BattlePacketType.ID_TH_TB_BATTLE,ClientChannel.Lobby,CLobbyResponse.Lobby_SyncStatusResponse,{lobbyID,BattleLobby_List[lobbyID].name,BattleLobby_List[lobbyID].battleClientEP_List[i].guid,BattleLobby_List[lobbyID].battleClientEP_List[i].id,JSON_Encode(playerList)})
    end
end

ClientPacketHandling[ClientChannel.Lobby][CLobbyResponse.Lobby_SyncStatus] = function(host, channel, request,data,ip, guid)
    -- print("sync status detected from " .. guid)

    local clientGUID, clientID, lobbyID, readyState,selectedFormation = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|([^|]+)|([^|]+)|$")

    print("clientGUID " .. clientGUID)
    print("clientID " .. clientID)
    print("lobbyID " .. lobbyID)
    print("readyState " .. readyState)
    print("selectedFormation " .. selectedFormation)
    local tReadyState = false
    if readyState == "true" then
        tReadyState = true
    end
    -- toboolean
    if BattleClientEP_List[clientGUID] ~= nil then
        -- print("found")
        local tID = BattleClientEP_List[clientGUID].id
        print("check client ID " .. tID .. "/" .. clientID )
        if tID == clientID then
            print("matched !!!")
            -- BattleClientEP_List[clientGUID].readyState = tReadyState
            if BattleLobby_List[lobbyID] == nil then
                print("lobby not found")
                return
            end
            for i = 1, #BattleLobby_List[lobbyID].battleClientEP_List do
                if BattleLobby_List[lobbyID].battleClientEP_List[i].guid == clientGUID then
                    BattleLobby_List[lobbyID].battleClientEP_List[i].readyState = tReadyState

                    BattleLobby_List[lobbyID].battleClientEP_List[i]. selected_formation_index = selectedFormation

                end
            end

            -- local playerList = {}
            BS_Lobbies_Notify_ClientChanges(host,lobbyID)

        end

        local readyCount = 0
        if BattleLobby_List[lobbyID].lobbyState == BattleLobbyState.OPEN or BattleLobby_List[lobbyID].lobbyState == BattleLobbyState.FULL then 
            for i = 1, #BattleLobby_List[lobbyID].battleClientEP_List do
                if BattleLobby_List[lobbyID].battleClientEP_List[i].readyState == true then
                    readyCount = readyCount + 1
                end
            end
            if readyCount >= 2 then
                print("Lobby " .. lobbyID .. " is ready")
                print("Startinng the game ")
                for i = 1, #BattleLobby_List[lobbyID].battleClientEP_List do
                    print("player " .. i .. " guid " .. BattleLobby_List[lobbyID].battleClientEP_List[i].guid .. " selected formation " .. BattleLobby_List[lobbyID].battleClientEP_List[i].selected_formation_index)
                    -- BM_sendWrapData()
                    BM_sendWrapData(host,BattleLobby_List[lobbyID].battleClientEP_List[i]:getIP(),BattleLobby_List[lobbyID].battleClientEP_List[i].guid,BattlePacketType.ID_TH_TB_BATTLE,ClientChannel.Lobby,CLobbyResponse.Lobby_Response_MatchStart,{lobbyID,BattleLobby_List[lobbyID].name,BattleLobby_List[lobbyID].battleClientEP_List[i].guid,BattleLobby_List[lobbyID].battleClientEP_List[i].id, "MatchStart"})
                end
                BattleLobby_List[lobbyID].lobbyState = BattleLobbyState.LOCK_IN
            end
        elseif BattleLobby_List[lobbyID].lobbyState == BattleLobbyState.LOCK_IN then
            if tReadyState == false then
                print("Lobby " .. lobbyID .. " is not ready, canceling the match")

                for i = 1, #BattleLobby_List[lobbyID].battleClientEP_List do
                    print("player " .. i .. " guid " .. BattleLobby_List[lobbyID].battleClientEP_List[i].guid .. " selected formation " .. BattleLobby_List[lobbyID].battleClientEP_List[i].selected_formation_index)
                    -- BM_sendWrapData()
                    BM_sendWrapData(host,BattleLobby_List[lobbyID].battleClientEP_List[i]:getIP(),BattleLobby_List[lobbyID].battleClientEP_List[i].guid,BattlePacketType.ID_TH_TB_BATTLE,ClientChannel.Lobby,CLobbyResponse.Lobby_Response_MatchStart,{lobbyID,BattleLobby_List[lobbyID].name,BattleLobby_List[lobbyID].battleClientEP_List[i].guid,BattleLobby_List[lobbyID].battleClientEP_List[i].id, "MatchCancel"})
                end
                BattleLobby_List[lobbyID].lobbyState = BattleLobbyState.FULL
            end
        else

            print("Problem caused in Lobby " .. lobbyID )
        end

    else
        print("client not found")
    end

end

ClientPacketHandling[ClientChannel.Lobby][CLobbyResponse.Lobby_Request_Formations] = function(host, channel, request,data,ip, guid)

    local tGUID, tID = string.match(data, "^|([^|]+)|([^|]+)|$")
    print("request formations detected from " .. tGUID .. " " .. tID)

    if BattleClientEP_List[tGUID] == nil then 
        print("client not registered yet")
        return 
    end
    if BattleClientEP_List[tGUID].id == tID then 
        print("client matched")
        if ClientFormations[tID] == nil then
            print("This client has no formations yet")
            -- todo send the signal that show on client UI
        end
        print("data check")
        for k,v in pairs(ClientFormations[tID]) do
            -- print("k " .. k)
            -- print("formation name " .. v.name)
            -- print("index " .. v.index)
            for i = 1, #v.characters do
                -- print("character " .. i)
                -- print("character id " .. v.characters[i].id)
                -- print("character slot index " .. v.characters[i].slotIndex)
                -- print("character row pos " .. v.characters[i].rowPos)
                -- print("character col pos " .. v.characters[i].colPos)
            end
        end
    end

    local tData = JSON_Encode(ClientFormations[tID],false)

    -- print("data check " .. tData)

    BM_sendWrapData(host, ip, guid,BattlePacketType.ID_TH_TB_BATTLE, ClientChannel.Lobby, CLobbyResponse.Lobby_Response_Formations,{tGUID,tID,tData} )
end


ClientPacketHandling[ClientChannel.Lobby][CLobbyResponse.Lobby_Request_OwnedCharacters] = function(host, channel, request,data,ip, guid)

    local tGUID, tID = string.match(data, "^|([^|]+)|([^|]+)|$")
    print("request formations detected from " .. tGUID .. " " .. tID)
    if BattleClientEP_List[tGUID] == nil then 
        print("client not registered yet")
        return 
    end
    if BattleClientEP_List[tGUID].id == tID then 
        print("client matched")
        if ClientOwnedCharacters[tGUID] == nil then
            print("This client has no owned characters yet")
            -- todo send the signal that show on client UI
        end

    end

    local tData = JSON_Encode(ClientOwnedCharacters[tID])

    -- print("tData check " .. tData)
    BM_sendWrapData(host, ip, guid,BattlePacketType.ID_TH_TB_BATTLE, ClientChannel.Lobby, CLobbyResponse.Lobby_Response_OwnedCharacters,{tGUID,tID,tData} )
end


ClientPacketHandling[ClientChannel.Lobby][CLobbyResponse.Lobby_Response_MatchStart_Confirm] = function(host, channel, request,data,ip, guid)
    print("match start confirm detected from " .. guid)

    local tGUID, tID, lobbyID, selectedFormationIndex = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|([^|]+)|$")
    print("tGUID " .. tGUID)
    print("tID " .. tID)
    print("lobbyID " .. lobbyID)
    print("selectedFormationIndex " .. selectedFormationIndex)

    print("data check start ===================")

    ClientFormations = _G.ClientFormations


    if ClientFormations[tID][selectedFormationIndex] == nil then
        print("wrong Info (Lobby_Response_MatchStart_Confirm) ")
        return
    end

    -- for k,v in pairs(ClientFormations[tID][selectedFormationIndex].characters) do
    --     print("character " .. k)
    --     print("character id " .. v.id)
    --     print("character slot index " .. v.slotIndex)
    --     print("character row pos " .. v.rowPos)
    --     print("character col pos " .. v.colPos)
    --     -- print("character name " .. v.stats.name)
    --     -- for j, u in pairs(v.stats) do
    --     --     print("stat " .. j .. " value " .. u)
    --     -- end
    -- end

    for i = 1, #ClientFormations[tID][selectedFormationIndex].characters do
        local tCharacterID = ClientFormations[tID][selectedFormationIndex].characters[i].id
        local tSlotIndex = ClientFormations[tID][selectedFormationIndex].characters[i].slotIndex
        local tRowPos = ClientFormations[tID][selectedFormationIndex].characters[i].rowPos
        local tColPos = ClientFormations[tID][selectedFormationIndex].characters[i].colPos
        print("character id " .. tCharacterID)
        print("character slot index " .. tSlotIndex)
        print("character row pos " .. tRowPos)
        print("character col pos " .. tColPos)

    end
    

    -- todo send the signal that show on client UI

    -- for k,v in ClientFormations[tID] do
    --     print("formation " .. k .. " has " .. #v.characters .. " characters")
    -- end

    print("data check end ===================")
    print("locked formation index " .. selectedFormationIndex)
    BattleLobby_List[lobbyID]:addFormation(tID,ClientFormations[tID][selectedFormationIndex])

    print("Lobby " .. BattleLobby_List[lobbyID].name .. " has user " .. tID .. " locked formation " .. BattleLobby_List[lobbyID].formation_Map[tID].name)

end


-- function Request


--MARK: Client Data
-- This is to main server

--- Send request for formations based on user GUID and ID
function Request_Formation_From_MainServer(host, userGUID,userID)

    BM_sendWrapData(host, BM_getMainServerIP(host), BM_getMainServerGUID(host), BattlePacketType.ID_TH_INTERNAL,MainServerChanel.ClientData , ClientDataResponse.ClientData_Request_Formation, {userGUID,userID})

end

InternalPacketHandling[MainServerChanel.ClientData][ClientDataResponse.ClientData_Response_Formation] = function(host, channel, request,data,ip, guid)

    -- print(" response formations detected")
    local tGUID, tID, tFormation = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|$")

    -- print ("tGUID " .. tGUID)
    -- print("tID " .. tID)
    -- print("tFormation " .. tFormation)

    local tFormationList, pos , err = JSON_Decode(tFormation)
    if err then
        print("Ke3 F3i117 exception (MainServerChanel.ClientData][ClientDataResponse.ClientData_Response_Formation)  JSON decode error:", err)
    end
    if tFormationList == nil then
        print("user " .. tGUID .. " id " .. tID .. " has no formations")
        -- todo send the client a message that the user has no formations
    end

    -- ClientFormations[tID] = {}--- restart list
    if ClientFormations[tID] ~= nil then
        for k,v in pairs(ClientFormations[tID]) do
            ClientFormations[tID][k] = nil
        end
    end
    ClientFormations[tID] = {}

    ---@diagnostic disable-next-line: param-type-mismatch
    for k,v in pairs(tFormationList) do
        ClientFormations[tID][k] = BattleFormation:new()  
        ClientFormations[tID][k]:init(tonumber(k), v.name)
        local count = #v.formationData
        -- print("formation data ")
        for i = 1, count do
            -- print("data " .. i )
            local tSlotIndex = v.formationData[i].slot_index
            local tCharacterID = v.formationData[i].character_id
            local tRowPos = v.formationData[i].row_pos
            local tColPos = v.formationData[i].col_pos
            -- print("slot_index " .. v.formationData[i].slot_index)
            -- print("character_id " .. v.formationData[i].character_id)
            -- print("col_pos " .. v.formationData[i].col_pos)
            -- print("row_pos " .. v.formationData[i].row_pos)

            local tCharacter = BS_Character:new()
            tCharacter:init(tID,tCharacterID, tSlotIndex, tRowPos, tColPos)
            ClientFormations[tID][k]:addCharacter(tCharacter)

        end
        -- print("formation " .. k .. " has " .. #ClientFormations[tID][k].characters .. " characters")
    end

end

function Request_ClientOwnedCharacters_From_MainServer(host, lobbyID,  userGUID,userID)

    BM_sendWrapData(host, BM_getMainServerIP(host), BM_getMainServerGUID(host), BattlePacketType.ID_TH_INTERNAL,MainServerChanel.ClientData , ClientDataResponse.ClientData_Request_OwnedCharacters, {lobbyID,userGUID,userID})
end


InternalPacketHandling[MainServerChanel.ClientData][ClientDataResponse.ClientData_Response_OwnedCharacters] = function(host, channel, request,data,ip, guid)

    local  lobbyID, tGUID, tID, tOwnedCharacters = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|([^|]+)|$")

    -- print ("tGUID " .. tGUID)
    -- print("tID " .. tID)
    -- print(type(tOwnedCharacters))
    -- print("tOwnedCharacters |" .. tOwnedCharacters .. "|")

    local tOwnedCharactersList, pos , err = JSON_Decode(tOwnedCharacters)
    if err then
        print("Ke3 F3i117 exception (MainServerChanel.ClientData][ClientDataResponse.ClientData_Response_OwnedCharacters)  JSON decode error:", err)
    end
    if tOwnedCharactersList == nil then
        print("user " .. tGUID .. " id " .. tID .. " has no owned characters")
        -- todo send the client a message that the user has no owned characters
        return
    end


    -- for k,v in pairs(tOwnedCharactersList) do
    --     print("character " .. k)
    --     print("character id " .. v.ID)
    --     for t,u in pairs(v.stats) do
    --         print("stat " .. t .. " value " .. u)
    --     end

    --     -- print("character name " .. v.stats.name)
    --     -- for j, u in pairs(v.stats) do
    --     --     print("stat " .. j .. " value " .. u)
    --     -- end
    -- end


    ClientOwnedCharacters[tID] = {}

    for k,v in pairs(tOwnedCharactersList) do
        -- print("k " .. k)
        ClientOwnedCharacters[tID][k] = {}
        ClientOwnedCharacters[tID][k].ID = v.ID
        local stats = v.stats
        if stats == nil then
            print("Ke3 F3i117 exception (MainServerChanel.ClientData][ClientDataResponse.ClientData_Response_OwnedCharacters)  JSON decode error:")
            return
        end

        -- print("k2,v2 patch ===================================")
        for k2,v2 in pairs(stats) do
            -- print(k2 .. " " .. v2)
            ClientOwnedCharacters[tID][k][k2] = v2
        end
        --- overwrite level and xp | value from query higher priority
        ClientOwnedCharacters[tID][k].level = v.level
        ClientOwnedCharacters[tID][k].exp = v.exp
    end

    -- Update stat for lobbies
    if BattleLobby_List[lobbyID] == nil then
        LOG_COOKED("K286","BattleLobbiesHandler:Request_ClientOwnedCharacters_From_MainServer lobby " .. lobbyID .. " does not exist")
        return
    end
    -- if BattleLobby_List[lobbyID].formation_Map[tID] == nil then 
    --     LOG_COOKED("K287","BattleLobbiesHandler:Request_ClientOwnedCharacters_From_MainServer player " .. tID .. " does not exist in lobby " .. lobbyID)
    -- end
    
    --- request the formation from main server only when owned character get
    Request_Formation_From_MainServer(host, tGUID, tID)
    -- BattleLobby_List[lobbyID]:updateFormation(tID)
end

