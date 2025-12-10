
-- require "clientSide"


ClientBattleHandling[BattlePacketChannel.InfoChannel][CLobbyResponse.Lobby_Join_Response] = function(host,data,guid)
    

    print("join response detected")
    print("from server GUID:" .. guid)
    -- print("Data:" .. data)
    local clientGUID, clientID, lobbyID , joinResult , errorMessage = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|([^|]+)|([^|]+)|$")

    print("clientGUID " .. clientGUID)
    print("clientID " .. clientID)
    print("lobbyID " .. lobbyID)
    print("joinResult " .. joinResult)
    print("errorMessage " .. errorMessage)
    
end
