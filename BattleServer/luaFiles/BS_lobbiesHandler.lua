--- Battle server, lobby section
package.path = package.path .. ";../luaFiles/?.lua" 


require "battleWrapper"
require "BS_global"
require "BS_handle_clients"
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
    BattleLobby_List[lobbyID]:init(lobbyID,lobbyName,lobbyPassword)

    -- BM_removeFromWhitelist_ByGUID(tTargetGUID) --- 
    BM_addToWhitelist(tTargetGUID,targetID) -- add the user to whitelist

    BM_sendWrapData(host, ip, guid, BattlePacketType.ID_TH_INTERNAL, MainServerChanel.Lobby, LobbyResponse.Lobby_Create_Response , {tTargetGUID,targetID,serverGUID,lobbyID,combineData}) -- Send to the client request the lobby 
    BattleLobby_Notify_LobbiesStates(host)
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
        BM_sendWrapData(host,BattleLobby_List[lobbyID].battleClientEP_List[i]:getIP(),BattleLobby_List[lobbyID].battleClientEP_List[i].guid,BattlePacketType.ID_TH_TB_BATTLE,ClientChannel.Lobby,CLobbyResponse.Lobby_SyncStatusResponse,{BattleLobby_List[lobbyID].battleClientEP_List[i].guid,BattleLobby_List[lobbyID].battleClientEP_List[i].id,JSON_Encode(playerList)})
    end
end

ClientPacketHandling[ClientChannel.Lobby][CLobbyResponse.Lobby_SyncStatus] = function(host, channel, request,data,ip, guid)
    -- print("sync status detected from " .. guid)

    local clientGUID, clientID, lobbyID, readyState = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|([^|]+)|$")

    print("clientGUID " .. clientGUID)
    print("clientID " .. clientID)
    print("lobbyID " .. lobbyID)
    print("readyState " .. readyState)
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
                end
            end

            -- local playerList = {}
            BS_Lobbies_Notify_ClientChanges(host,lobbyID)
            -- for i = 1, #BattleLobby_List[lobbyID].battleClientEP_List do
            --     print("client #" .. i)
            --     print("\tclientID " .. BattleLobby_List[lobbyID].battleClientEP_List[i].id)
            --     print("\tclientGUID " .. BattleLobby_List[lobbyID].battleClientEP_List[i].guid)
            --     local clientData = {}
            --     clientData.id = BattleLobby_List[lobbyID].battleClientEP_List[i].id
            --     clientData.guid = BattleLobby_List[lobbyID].battleClientEP_List[i].guid
            --     clientData.index = i
            --     playerList[clientData.guid] = clientData
            --     -- table.insert(lobbyList,clientData)
            -- end
            -- for i = 1, #BattleLobby_List[lobbyID].battleClientEP_List do
            --     BS_Lobbies_Notify_ClientChanges(host,lobbyID,playerList)
            --     -- BM_sendWrapData(host,BattleLobby_List[lobbyID].battleClientEP_List[i]:getIP(),BattleLobby_List[lobbyID].battleClientEP_List[i].guid,BattlePacketType.ID_TH_TB_BATTLE,ClientChannel.Lobby,CLobbyResponse.Lobby_SyncStatusResponse,{BattleLobby_List[lobbyID].battleClientEP_List[i].guid,BattleLobby_List[lobbyID].battleClientEP_List[i].id,JSON_Encode(playerList)})
            -- end
        end
    else
        print("client not found")
    end

end