Lobby_HandleNetwork[PacketID.ID_DISCONNECTION_NOTIFICATION] = function(host,packet,RakNetPacket)

    print("disconnected from server")

    cpp_changeScene(SceneIndex.Home)

end