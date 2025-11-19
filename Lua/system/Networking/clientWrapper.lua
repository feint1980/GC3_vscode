---- include Lua libraries

package.path = package.path .. ";../../Lua/include/?.lua"

local json = require ("dkjson")


--- Classes declare

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
    Arena_CreateLobby_Request = 4
    -- Arena_Connect_ConnectToServer = 2,
}

--- MARK: Battle Server

BattlePacketChannel = {
    InfoChannel = 1,
}

BattleInfoResponse = {
    BattleInfo_AddCryptor_Request = 1,
    BattleInfo_AddCryptor_Response = 2,
    
}


--- MARK: Functions

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
