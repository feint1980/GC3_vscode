--- Battle server, lobby section
package.path = package.path .. ";../luaFiles/?.lua" 


require "battleWrapper"
require "BS_global"

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

    BM_addToWhitelist(host,tTargetGUID) -- add the user to whitelist

    BM_sendWrapData(host, ip, guid, BattlePacketType.ID_TH_INTERNAL, MainServerChanel.Lobby, LobbyResponse.Lobby_Create_Response , {tTargetGUID,targetID,serverGUID,lobbyID,lobbyName,lobbyPassword}) -- Send to the client request the lobby 

    -- add lobby to list
    

end

--- MARK:Client 

ClientPacketHandling[ClientChannel.Lobby][CLobbyResponse.Lobby_Join_Request] = function(host, channel, request,data,ip, guid)

    print("join lobby detected from " .. guid)

    -- print("data " .. data)

    local clientGUID, clientID, lobbyID = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|$")

    print("clientGUID " .. clientGUID)
    print("clientID " .. clientID)
    print("lobbyID " .. lobbyID)

    local joinResult =  BM_JoinLobby(host,clientGUID,clientID,lobbyID,ip)

    BM_sendWrapData(host, ip, guid, BattlePacketType.ID_TH_TB_BATTLE, ClientChannel.Lobby, CLobbyResponse.Lobby_Join_Response , {clientGUID,clientID,lobbyID , tostring(joinResult) , "Unable to join lobby"})

end