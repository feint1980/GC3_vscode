---- include Lua libraries

package.path = package.path .. ";../../Lua/include/?.lua"

local json = require ("dkjson")


--- Classes declare


PacketID = {
    ID_DISCONNECTION_NOTIFICATION = 21,
    ID_ALREADY_CONNECTED = 18,
    ID_INCOMPATIBLE_PROTOCOL_VERSION = 25,
    ID_REMOTE_DISCONNECTION_NOTIFICATION = 31,
    ID_REMOTE_CONNECTION_LOST = 32,
    ID_REMOTE_NEW_INCOMING_CONNECTION = 33,
    ID_CONNECTION_BANNED = 23,
    ID_CONNECTION_ATTEMPT_FAILED = 17,
    ID_NO_FREE_INCOMING_CONNECTIONS = 20,
    ID_CONNECTION_LOST = 22,
    ID_CONNECTION_REQUEST_ACCEPTED = 16,
    ID_UNCONNECTED_PING = 24,
    ID_UNCONNECTED_PONG = 28,
    ID_OTHER = 124
}

---MARK:Main Server
--- for CLient
PacketChannel ={
    AccountChannel = 1,
    UserChannel = 2,
    ShopChannel =3,
    TransactionChannel = 4,
    FormationChannel = 5,
    ArenaChannel = 6
}

AccountResponse = {
    Alogin = 1,
    Aregister = 2,
    ARequesKey = 3
}

UserResponse = {
    MainInfo = 1,  --- account info (mon,souls)
    CharacterInfo = 2,
    SkillInfo = 3,
    SkillInfo_Start = 4,
    SkillInfo_Data = 5,
    SkillInfo_End = 6,
    OwnedCharacter_Request = 7,
    OwnedCharacter_Start = 8,
    OwnedCharacter_Data = 9,
    OwnedCharacter_End = 10,

}

FormationResponse = {
    Formation_Request = 1, ---- use for notification
    Formation_Start = 2,
    Formation_Data = 3,
    Formation_SubData = 4,
    Formation_End = 5,
    Formation_Add = 6,
    Formation_Remove = 7,
    Formation_Rename = 8,
    Formation_Info_Update = 9,
}


ShopResponse = {
    ShopChracterInfo = 1,
    ShopItemInfo = 2,
    ShopCharacterInfo_Begin = 3,
    ShopCharacterInfo_Data = 4,
    ShopCharacterInfo_End = 5,
    ShopCharacter_Buy = 6
}

ArenaResponse = {
    Arena_Request_GetServerList = 1,
    Arena_RequestLobbyList = 2,
    Arena_RequestLobbyResponse = 3,
    Arena_RequestLobby_Create = 4,
    Arena_RequestLobbyListResponse = 5,
    Arena_RequestJoinLobby_WithBSGUID_LobbyID = 6,
    Arena_RequestJoinLobby_WithBSGUID_LobbyID_Response = 7,

    -- Arena_Connect_ConnectToServer = 2,
}

--- MARK: Battle Server

BattlePacketChannel = {
    InfoChannel = 1,
    Lobby = 2,
    Combat = 3
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
    -- Lobby_
}

BattleInfoResponse = {
    BattleInfo_AddCryptor_Request = 1,
    BattleInfo_AddCryptor_Response = 2,
}

CCombatResponse = {
    Combat_ReadyStatus = 1,
    Combat_IngameData = 2,
    Combat_TurnOrder =3,
}

CombatIngameData = 
{
    Sync = 1, 
    MatchStart = 2, 
    OnCharacterTurnStart = 3,
    Skill_Info_Sync = 4,
}

CombatTurnOrder = 
{
    Sync = 1,
    RollResult = 2,
    SpeedAffect = 3,
    UpdateOrder = 4,
    PlayerCharacterTurn = 5,
}


--- MARK: Functions
--- MARK:Main server

ClientMessageHandling = {

}


ClientBattleHandling = {

}


for k,v in pairs(PacketChannel) do
    -- print(k,v)
    ClientMessageHandling[v] = {}
end

for k,v in pairs(BattlePacketChannel) do

    print("init function for channel (BattlePacketChannel) " .. v)
    ClientBattleHandling[v] = {}
end


---- MARK:Battle server

---@Description combines packet
---@param type string type of packet to wrap
---@param list table data to wrap
---@return string
function CombinePackage(type,list)
    ----
    local returnValue = "|"
    returnValue = returnValue .. type .. "_REQUEST|" 
    for i = 1, #list do
        returnValue = returnValue .. list[i] .. "|"
    end
    returnValue = returnValue .. type .. "_END_REQUEST|"
    return returnValue
end

---@Description wraps packet
---@param channel number channel 
---@param request number type of packet to wrap
---@param list table data to wrap
---@return string
function WrapRequest(channel, request, list)

    local returnValue = ""
    returnValue = string.char(channel) .. string.char(request) .. "|"
    for i = 1, #list do
        returnValue = returnValue .. tostring(list[i]) .. "|"
    end
    -- returnValue = returnValue .. "|"
    return returnValue
end

--- split data into multiple part with special character and no of split
---@return table table of string data split
function SplitMessgae(message, character, no_of_split)
    local tTable;
    tTable = {};
    for str in string.gmatch(message, "([^" .. character .. "]+)") do
        table.insert(tTable, str);
    end
    return tTable
end

--- return client guid
--- @return string
function ClientGetGUID(host)
    return cppGetClientGUID(host)
end

---@Description: wrapper of cppGetPingFromServer
---@param host pointer instance of ClientScriptingManager
---@param ip? ipaddres
--- return client ping
--- @return numer
function ClientGetPing(host, ip)
    return cppGetPingFromServer(host)
end

---@Description: wrapper of cppPing_server
---@param host pointer instance of ClientScriptingManager
---@param ipString string ip address
---@param port number port
function ClientPingToServer(host, ipString, port)
    return cppPing_server(host, ipString, port)
end

---@Description wrapper of cppConnectToBattleServer
---@param host pointer instance of ClientScriptingManager
---@param guid
function ClientConnectToBattleServer(host, guid)
    print("ClientConnectToBattleServer called guid " .. guid)
    return cppConnectToBattleServer(host, guid)
end

function ClientConnect2SV(host,ip,port)
    return cpp_connect2SV(host,ip,port)
end

function ClientDisconnectFromCurrentBattleServer(host)
    cpp_disconnectFromCurrentBS(host)
end


--- deep copy table
function Table_DeepCopy(orig, copies)
    copies = copies or {} -- to handle cycles
    if type(orig) ~= "table" then
        return orig
    elseif copies[orig] then
        return copies[orig]
    end
    
    local copy = {}
    copies[orig] = copy
    for k, v in pairs(orig) do
        copy[Table_DeepCopy(k, copies)] = Table_DeepCopy(v, copies)
    end
    return setmetatable(copy, getmetatable(orig))
end

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

---@Description: wrapper of cpp_client_Packet_getIP
---@param packet pointer instance of RakNetPacket
---@return string (IP with port )
function Client_GetIP_FromPacket(packet)
    return cpp_Packet_getIP(packet)
end

---@Description: wrapper of cpp_client_Packet_getGUID
---@param packet pointer instance of RakNetPacket
---@return string (GUID)
function Client_GetGUID_FromPacket(packet)
    print("Client_GetGUID_FromPacket called")
    return cpp_Packet_getGUID(packet)
end

function Client_GetPort_FromPacket(packet)
    return cpp_Packet_getPort(packet)
end

---@Description: wrapper of cpp_addCryptor
---@param host pointer instance of ClientScriptingManager
---@param key string 
function Client_AddCryptor(host, key)
    return cpp_addCryptor(host, key)
end

---@Description: wrapper of cpp_removeCryptor
---@param host pointer instance of ClientScriptingManager
---@param key string 
function Client_RemoveCryptor(host, key)
    return cpp_removeCryptor(host, key)
end
