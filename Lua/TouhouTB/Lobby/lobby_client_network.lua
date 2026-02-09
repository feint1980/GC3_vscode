package.path = package.path .. ';../../Lua/system/GUI/?/?.lua;' .. ';../../Lua/system/GUI/widgets/?.lua;' .. ';../../Lua/system/Networking/?.lua;'

-- Lobby_HandleNetwork[PacketID.ID_CONNECTION_REQUEST_ACCEPTED] = function(host,packet,RakNetPacket)

--     local tGuid = Client_GetGUID_FromPacket(RakNetPacket)
--     print("accepted from server " .. tGuid)

--     -- cpp_lobby_changeScene(SceneIndex.Home)

-- end

--- Disconnect
Lobby_HandleNetwork[PacketID.ID_DISCONNECTION_NOTIFICATION] = function(host,packet,RakNetPacket)

    print("disconnected from server")
    if Lobby_Leave_Decision == false then
        Prompt_UI_Table["Back_to_Home_Noti"]:showMsg("Disconnected from lobby !")
    end

end

--- Send Sync request
function Client_Lobby_SendSyncRequest()

    print("Client_Lobby_SendSyncRequest")

    local tGUID = InfoHolder_getStrVal("MainInfo.guid")
    local tID = InfoHolder_getStrVal("MainInfo.id")
    local targetLobbyID = InfoHolder_getStrVal("Target_Lobby_ID")
    local  readyState = tostring(LobbyScene_isReady)
    -- Send Sync Request
    SendBattleRequest(BattlePacketChannel.Lobby,CLobbyResponse.Lobby_SyncStatus, {tGUID, tID ,targetLobbyID,readyState },5,0.1,0.15)
end

function Client_Lobby_Request_Formations()
    local tGUID = InfoHolder_getStrVal("MainInfo.guid")
    local tID = InfoHolder_getStrVal("MainInfo.id")

    SendBattleRequest(BattlePacketChannel.Lobby,CLobbyResponse.Lobby_Request_Formations, {tGUID, tID },5,0.1,0.15)

end


LobbyBattleHandling[BattlePacketChannel.Lobby][CLobbyResponse.Lobby_SyncStatusResponse] = function(host,data,guid)
    print("Lobby_SyncStatusResponse called " .. guid)

    local lobbyID, lobbyName, tGUID, id, tData = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|([^|]+)|([^|]+)|$")

    cppSelecBattleServer(host,guid)
    print("lobbyID " .. lobbyID)
    print("tGUID " .. tGUID)
    print("id " .. id)
    -- print("tData " .. tData)

    local clientList, pos, err = JSON_Decode(tData)
    if clientList == nil then
        print("Ke3 F3i117 exception (PacketChannel.Lobby][LobbyResponse.Lobby_SyncStatusResponse) JSON decode error:", err)
        return
    end
    for k,v in pairs(clientList) do
        print("k " .. k)
        -- print("guid " .. v.guid)
    end

    local myGUID = InfoHolder_getStrVal("MainInfo.guid")
    local myID = InfoHolder_getStrVal("MainInfo.id")
    LobbyIDLabel:setText("ID : " .. lobbyID)
    LobbyTitleLabel:setText(lobbyName)
    print("comparing ..." )
    print(myGUID .. "/" .. tGUID)
    print(myID .. "/" .. id)

    if clientList[myGUID] == nil then
        print("client in response not found")
        return
    end

    local index = clientList[myGUID].index
    print("index " .. index)

    LobbyScene_ChangeHandleSync(clientList)
    if Formation_Selector ~= nil then
        Formation_Selector:setIndex(tonumber(index))
        Formation_Selector:setVisible(true)
    end

end

LobbyBattleHandling[BattlePacketChannel.Lobby][CLobbyResponse.Lobby_Response_Formations] = function(host,data,guid)

    print("Formation response")

    local tGUID, tID, tData = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|$")

    -- let just skip guid check 

    local formations, pos, err = JSON_Decode(tData)
    if formations == nil then
        print("Ke3 F3i117 exception (PacketChannel.Lobby][LobbyResponse.Lobby_Response_Formations) JSON decode error:", err)
        return
    end

    -- re write formation 
    Lobby_Formations_Info = {}
    Lobby_Formations_Info = Table_DeepCopy(formations)

    table.sort(Lobby_Formations_Info)

    --- Reset the formation UI
    for k, v in pairs(Lobby_Formations_Info) do 
        print("k " .. k )
        print("formation name " .. v.name)
        print("index " .. v.index)
        for i = 1, #v.characters do
            print("character " .. i)
            print("character id " .. v.characters[i].id)
            print("character slot index " .. v.characters[i].slotIndex)
            print("character row pos " .. v.characters[i].rowPos)
            print("character col pos " .. v.characters[i].colPos)
        end
    end

end