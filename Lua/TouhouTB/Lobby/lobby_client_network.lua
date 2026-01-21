package.path = package.path .. ';../../Lua/system/GUI/?/?.lua;' .. ';../../Lua/system/GUI/widgets/?.lua;' .. ';../../Lua/system/Networking/?.lua;'


-- Lobby_HandleNetwork[PacketID.ID_CONNECTION_REQUEST_ACCEPTED] = function(host,packet,RakNetPacket)

--     local tGuid = Client_GetGUID_FromPacket(RakNetPacket)
--     print("accepted from server " .. tGuid)

--     -- cpp_lobby_changeScene(SceneIndex.Home)

-- end

--- Disconnect
Lobby_HandleNetwork[PacketID.ID_DISCONNECTION_NOTIFICATION] = function(host,packet,RakNetPacket)

    print("disconnected from server")

    Prompt_UI_Table["Back_to_Home_Noti"]:showMsg("Disconnected from lobby !")
    -- cpp_lobby_changeScene(SceneIndex.Home)

end


--- Send Sync request
function Client_Lobby_SendSyncRequest()


    cppSelecBattleServer(host,tGuid)
    print("Client_Lobby_SendSyncRequest")
    -- Send Sync Request
    SendBattleRequest(BattlePacketChannel.Lobby,CLobbyResponse.Lobby_SyncStatus, {MainInfo.guid, MainInfo.id ,Target_Lobby_ID },5,0.1,0.15)

end
