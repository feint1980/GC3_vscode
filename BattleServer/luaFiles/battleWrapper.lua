package.path = package.path .. ";../../Lua/include/?.lua"
local json = require ("dkjson")
BattlePacketType = {

    ID_TH_TB = 135, -- info from client to main server
	ID_TH_TB_BATTLE = 136, -- info from client to battle server
	ID_TH_INTERNAL = 137, -- main server to battle server
}

MainServerChanel = {
    PaperWork = 1,
    ClientRequest = 2,
    Combat = 3,
    Lobby = 4,
    ClientData = 5,
}

PaperWorkRequest = {
    SelfRegister = 1,
    SelfRegisterAccepted = 2,
    LobbiesListUpdate = 3,
    SelfRegisterAsk = 4,
}

ClientChannel = {
    InfoChannel = 1,
    Lobby = 2,
    Combat = 3
}

BattleInfoResponse = {
    BattleInfo_AddCryptor_Request = 1
}

LobbyResponse = {
    Lobby_Create_Request = 1,
    Lobby_Create_Response = 2,
    Lobby_Join_Request_WL = 3, --- add whitelist

}

ClientDataResponse = {
    ClientData_Request_Fomration = 1,
    ClientData_Response_Fomration = 2,
    ClientData_Request_OwnedCharacters = 3,
    ClientData_Response_OwnedCharacters = 4,
}

CLobbyResponse = {
    Lobby_Join_Request = 1,
    Lobby_Join_Response = 2,
    Lobby_SyncStatus = 3,
    Lobby_SyncStatusResponse = 4,
    Lobby_Request_Formations = 5,
    Lobby_Response_Formations = 6,
    Lobby_Request_OwnedCharacters = 7,
    Lobby_Response_OwnedCharacters = 8,
    Lobby_Response_MatchStart = 9,
    Lobby_Response_MatchStart_Confirm = 10,
}

CCombatResponse = {
    Combat_ReadyStatus = 1,
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

---@Description: wrapper of cpp_addToWhitelist
---@param guid string
---@param id string
function BM_addToWhitelist(guid,id)
    return cpp_addToWhitelist(guid,id)
end

---@Description: wrapper of cpp_removeFromWhitelist_ByGUID
---@param guid string
function BM_removeFromWhitelist_ByGUID(guid)
    print("remove white list for " .. guid)
    return cpp_removeFromWhitelist_ByGUID(guid)
end

function BM_removeFromWhitelist_ByID(id)
    return cpp_removeFromWhitelist_ByID(id)
end


function BM_addClientOnlineSession(guid,id,ip)
    return cpp_registerOnlineSession(guid,id,ip)
end

function BM_getClientOnlineSessionByGUID(guid)
    return cpp_getOnlineSessionByGUID(guid)
end

---@ Description: encode table to json
---@param t table table to encode
---@param isIndent boolean indent or not
function JSON_Encode(t,isIndent)
    isIndent = isIndent or false
    return json.encode(t, { indent = isIndent })
end

---@Description: decode json to table
---@param data string 
---@return table decoded Lua table
---@return number position in the string after parsing finished
---@return number error if decode failed (nil if OK)
function JSON_Decode(data)
    
    local tbl, pos, err = json.decode(data)
    return tbl, pos, err
end

function BM_getMainServerIP(host)
    return cpp_BM_GetMainServerIP(host)
end


function BM_getMainServerGUID(host)
    return cpp_BM_GetMainServerGUID(host)
end

function BM_connectToMainServer(host)
    cpp_BM_ConnectToMainServer(host)
end

function BM_handleDisconnectFromMainServer(host)
    cpp_BM_HandleDisconnectFromMainServer(host)
end



function LOG_INFO(msg)  print("[INFO] " .. msg) end
function LOG_WARN(msg)  print("[WARN] " .. msg) end
function LOG_COOKED(code, msg) print("[COOKED][" .. code .. "] " .. msg) end