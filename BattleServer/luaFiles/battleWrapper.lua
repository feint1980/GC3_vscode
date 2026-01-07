BattlePacketType = {

    ID_TH_TB = 135, -- info from client to main server
	ID_TH_TB_BATTLE = 136, -- info from client to battle server
	ID_TH_INTERNAL = 137, -- main server to battle server
}

MainServerChanel = {
    PaperWork = 1,
    ClientRequest = 2,
    Combat = 3,
    Lobby = 4
}

PaperWorkRequest = {
    SelfRegister = 1,
    SelfRegisterAccepted = 2,
    Lobbies_Change = 3
}

ClientChannel = {
    InfoChannel = 1,
    Lobby = 2
}

BattleInfoResponse = {
    BattleInfo_AddCryptor_Request = 1
}

LobbyResponse = {
    Lobby_Create_Request = 1,
    Lobby_Create_Response = 2
}

CLobbyResponse = {
    Lobby_Join_Request = 1,
    Lobby_Join_Response = 2
}

---@description handle incoming connection
---@param host pointer instance of BattleMain
---@param packet pointer instance of RakNet::Packet
function BM_handleIncomingConnection(host, packet)
    cpp_handleIncomingConnection(host,packet)
end


---@Description: wrap packet with headers [channel][request][data * n]
---@param id number RakNet PacketID
---@param channel number channel
---@param request number request
---@param list table data
---@return string
function BM_WrapMsg(id,channel, request, list)
    -- print("WrapMsg called")
    local returnValue = ""
    returnValue = string.char(id) .. string.char(channel) .. string.char(request) .. "|"
    for i = 1, #list do
        returnValue = returnValue .. list[i] .. "|"
    end
    -- print("result check " .. returnValue)
    return returnValue
end

function BM_sendWrapData(host,targetIP, guid, id,channel, request, list)
    return cpp_BM_SendWrapData(host,targetIP,guid, BM_WrapMsg(id,channel, request, list))
end

---@Description: wrapper of cpp_getPacketIP 
---@param packet pointer instance of RakNet::Packet
---@return pointer instance of RakNet::Address System
function BS_Packet_getIP(packet)
    return cpp_getPacketIP(packet)
end

---@Description: wrapper of cpp_getPacketIPAsString
---@param packet pointer instance of RakNet::Packet
---@return string IP (no port)
function BS_Packet_getIPAsString(packet)
    return cpp_getPacketIPAsString(packet)
end

---@Description: wrapper of cpp_getPacketGUID
---@param packet pointer instance of RakNet::Packet
---@return string GUID
function BS_Packet_getGUID(packet)
    return cpp_getPacketGUID(packet)
end

---@Description: wrapper of cpp_getPacketPort
---@param packet pointer instance of RakNet::Packet
---@return number port
function BS_Packet_getPort(packet)
    return cpp_getPacketPort(packet)
end

---@Description: wrapper of cpp_removeCryptor
---@param host pointer instance of BattleMain
---@param key string 
function BM_removeCryptor(host,key)
    cpp_removeCryptor(host,key)
end

---@Description: wrapper of cpp_BM_CreateLobby
---@param host pointer instance of BattleMain
---@param lobbyName string
---@param lobbyPassword string
---@return string 
function BM_CreateLobby(host, lobbyName, lobbyPassword)
    return cpp_BM_CreateLobby(host,lobbyName,lobbyPassword)
end


---@Description: wrapper of cpp_BM_JoinLobby
---@param host pointer instance of BattleMain
---@param clientGUID string
---@param clientID string
---@param lobbyID string
---@param ip pointer instance of RakNet::SystemAddress
---@return boolean
function BM_JoinLobby(host,clientGUID,clientID,lobbyID,ip)
    return cpp_BM_JoinLobby(host,clientGUID,clientID,lobbyID,ip)
end


function BM_addToWhitelist(guid,id)
    return cpp_addToWhitelist(guid,id)
end

function BM_removeFromWhitelist(guid)
    return cpp_removeFromWhitelist(guid)
end

function BM_addClientOnlineSession(guid,id,ip)
    return cpp_registerOnlineSession(guid,id,ip)
end

function BM_getClientOnlineSessionByGUID(guid)
    return cpp_getOnlineSessionByGUID(guid)
end