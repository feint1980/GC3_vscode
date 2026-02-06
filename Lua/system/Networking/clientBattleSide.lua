
require "clientWrapper"


--- It should be here ( handle from home scene )
ClientBattleHandling[BattlePacketChannel.Lobby][CLobbyResponse.Lobby_Join_Response] = function(host,data,guid)
    
    print("join response detected")
    print("from server GUID:" .. guid)
    -- print("Data:" .. data)
    local clientGUID, clientID, lobbyID , joinResult , errorMessage = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|([^|]+)|([^|]+)|$")

    print("clientGUID " .. clientGUID)
    print("clientID " .. clientID)
    print("lobbyID " .. lobbyID)
    print("joinResult " .. joinResult)
    print("errorMessage " .. errorMessage)

    _G.LobbyState = 0
    Prompt_UI_Table["CreateLobby_Status"]:show(false)
    local msg = errorMessage
    if joinResult == "true" then
        -- _G.LobbyState = 0
        -- msg = "Joined lobby " .. lobbyID
        -- Prompt_UI_Table["CreateLobby_Noti"]:showMsg(msg)
        Prompt_UI_Table["CreateLobby_Status"]:show(false)
        
            -- Prompt_UI_Table["CreateLobby_Noti"]:showMsg("Request timeout !")
        Create_Lobby_State = 0
        CreateLobbyPanel:setVisible(false)
        cpp_changeScene(SceneIndex.Lobby)

        -- todo : join lobby
    else
        -- _G.LobbyState = 1
        Prompt_UI_Table["CreateLobby_Noti"]:showMsg(msg)
    end

end


