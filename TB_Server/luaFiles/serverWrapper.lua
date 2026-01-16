---- include Lua libraries

package.path = package.path .. ";../../Lua/include/?.lua"

local json = require ("dkjson")


------------------ Main info section

-- Replicate enum from C++

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
    Formation_Request = 1, 
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
}


------------------ Battle server section

BattleChanel = {
    PaperWork = 1,
    ClientRequest = 2,
    Combat = 3,
    Lobby = 4
}

PaperWorkRequest = {
    SelfRegister = 1,
    SelfRegisterAccepted = 2,
    LobbiesListUpdate = 3
}

LobbyResponse = {
    Lobby_Create_Request = 1,
    Lobby_Create_Response = 2
}


--- Classes declare
---@class pointer

--- function wrapper of cppDoQuery
---@Description: call a server to do a query
---@param host pointer instance of ServerScriptingManager
---@param query string the query command
function SV_DoQuery(host,query)
    cppDoQuery(host,query)
    SV_GetQueryResults(host)
end

--- function wrapper of cppDoQuerySTMT
---@Description: call a server to do a query
---@param host pointer instance of ServerScriptingManager
---@param stmt pointer instance of sqlite3_stmt
function SV_DoQuerySTMT(host,stmt)
    cppDoQuerySTMT(host,stmt)
    SV_GetQueryResults(host)
end

--- function wrapper of cppGetQueryResults
---@Description: get the result of a query
---@param host pointer instance of ServerScriptingManager
function SV_GetQueryResults(host)
    return cppGetQueryResults(host)
end

--- function wrapper of cppPacket_getData
---@Description: get the data of a packet 
---@param host pointer instance of ServerScriptingManager
---@param packet pointer instance of RakNet::Packet
---@return string data of the packet 
function SV_GetPacketData(host,packet)
    return cppPacket_getData(host,packet)
end

--- function wrapper of cppPacket_getGUID
---@Description: get the GUID of a packet 
---@param packet pointer instance of RakNet::Packet
---@return string GUID of the packet 
function SV_GetPacketGUID(packet)
    return cppPacket_getGUID(packet)
end

--- function wrapper of cppPacket_getIP
---@Description: get the IP of a packet 
---@param packet pointer instance of RakNet::Packet
---@return pointer instance of RakNet::SystemAddress
function SV_GetPacketIP(packet)
    return cppPacket_getIP(packet)
end

--- function wrapper of cppPacket_getIPAsString
--- @Description: get the IP (as string) from IP
--- @param ip pointer instance of RakNet::SystemAddress
--- @return string
function SV_GetIPString(ip)
    if ip == nil then 
        return "IP_nil"
    end 
    return cppPacket_getIPAsString(ip)
end

---function wrapper of cppGetSystemAddressPort
--- @Description: get the port from IP
--- @param ip pointer instance of RakNet::SystemAddress
--- @return number 
function SV_GetPortFromIP(ip)
    return cppGetSystemAddressPort(ip)
end

--- function wrapper of cppPacket_extract
---@Description: get the data of a packet 
---@param packet pointer instance of RakNet::Packet
---@return string data of the packet 
---@return pointer instance of RakNet::SystemAddress
function SV_ExtractPacket(packet)
    return cppPacket_extract(packet)
end

--- function wrapper of cppSendToClient
---@Description: send a packet to a client
---@param host pointer instance of ServerScriptingManager
---@param clientIP pointer instance of RakNet::SystemAddress
---@param message string message to send
---@param t_encrypt? boolean if need to t_encrypt (default true)
---@return number return value
function SV_SendMsg(host,clientIP,message,t_encrypt)
    t_encrypt = t_encrypt or true
    return cppSendToClient(host,clientIP,message,t_encrypt)
end

---@Description: wrap packet with headers [channel][request][data * n]
---@param channel number channel
---@param request number request
---@param list table data
---@return string
function WrapMsg(channel, request, list)
    -- print("WrapMsg called")
    local returnValue = ""
    returnValue = string.char(channel) .. string.char(request) .. "|"
    for i = 1, #list do
        returnValue = returnValue .. list[i] .. "|"
    end
    -- print("result check " .. returnValue)
    return returnValue
end

---@Description: send a wrapped packet to a client
---@param host pointer instance of ServerScriptingManager
---@param clientIP pointer instance of RakNet::SystemAddress
---@param channel number channel
---@param request number request
---@param list table data
---@return number return value
function SV_SendWrapMsg(host, clientIP, guid, channel, request, list)
    -- print("SV_SendWrapMsg called")
    return cppSendWrapMsgToClient(host, clientIP,guid, WrapMsg(channel, request, list))
end

---@Description: send a wrapped packet to a battle server
---@param host pointer instance of ServerScriptingManager
---@param clientIP pointer instance of RakNet::SystemAddress
---@param channel number channel
---@param request number request
---@param list table data
---@return number return value
function SV_SendWrapMsg2BattleServer(host, clientIP, guid, channel, request, list)
    -- print("SV_SendWrapMsg called")
    return cppSendWrapMsgToBattleServer(host, clientIP,guid, WrapMsg(channel, request, list))
end

---@Description force to send until it send OK
---@param host pointer instance of ServerScriptingManager
---@param ip pointer client ip
---@param guid string 
---@param channel number channel
---@param request number request
---@param tList table data
function SendReliable(host,ip, guid,channel,request,tList)

    local t_response = 0
    t_response = SV_SendWrapMsg(host,ip, guid,channel,request,tList)
    while t_response == 0 do
        t_response = SV_SendWrapMsg(host,ip, guid,channel,request,tList)
    end
end

---@Description force to send until it send OK
---@param host pointer instance of ServerScriptingManager
---@param ip pointer client ip
---@param guid string 
---@param channel number channel
---@param request number request
---@param tList table data
function SendReliable2BattleServer(host,ip, guid,channel,request,tList)

    local t_response = 0
    t_response = SV_SendWrapMsg2BattleServer(host,ip, guid,channel,request,tList)
    while t_response == 0 do
        t_response = SV_SendWrapMsg(host,ip, guid,channel,request,tList)
    end
end

function SV_SendMsgNonEncrypt(host,clientIP,message,t_encrypt)
    cppSendToClient(host,clientIP,message,false)
end

--- function wrapper of cppSqlite_CreateStatement
---@Desciption: create a sqlite3_stmt 
---@param host pointer instace of ServerScriptingManager
---@param baseQuery string base query 
function SV_CreateSQLSTMT(host,baseQuery)
    return cppSqlite_CreateStatement(host,baseQuery)
end

--- function wrapper of cppSqlite_BindStatement
---@Desciption: create a sqlite3_stmt 
---@param stmt pointer stm need to be bound 
---@param index number indext need to bound
---@param stringVal string 
function SV_BindSQLSTMT(stmt,index, stringVal)
    cppSqlite_BindStatement(stmt,index, stringVal)
end

--- function wrapper of cppSqlite_StepStatement
---@Desciption: create a step a sqlite3_stmt 
---@param host pointer instace of ServerScriptingManager
---@param stmt pointer stm need to be step
---@return number return value of the step
function SV_StepSQLSTMT(host,stmt)
    return cppSqlite_StepStatement(host,stmt)
end

--- function wrapper of cppSqlite_GetResultColumnCount
--- @Desciption: get the column count of a sqlite3_stmt after step
--- @param stmt pointer stm just run 
--- @return number number of column in the result
function SV_SQLGetResultColumnCount(stmt)
    return cppSqlite_GetResultColumnCount(stmt)
end

--- function wrapper of cppSqlite_gettResultInt
--- @Desciption: get the result as int value
--- @param stmt pointer stm just run
--- @param index number index of the column
--- @return number number of column in the result
function SV_SQLGetResultInt(stmt,index)
    return cppSqlite_gettResultInt(stmt,index)
end

--- function wrapper of cppSqlite_gettResultString
--- @Desciption: get the result as string value
--- @param stmt pointer stm just run
--- @param index number index of the column
--- @return string value of column in the result
function SV_SQLGetResultString(stmt,index)
    return cppSqlite_gettResultString(stmt,index)
end

--- function wrapper of cppSqlite_finalizeStmt
--- @Desciption: get the result as string value
--- @param stmt pointer stm just run
function SV_SQLFinalizeStmt(stmt)
    cppSqlite_finalizeStmt(stmt)
end
--- function wrapper of cppSqlite_exec
---@Description: execute a sql command
---@param host pointer instance of ServerScriptingManager
---@param cmd string sql command
function SV_SQLExec(host, cmd)
    cppSqlite_exec(host,cmd)
end

--- function wrapper of cppGenKey
--- @Desciption: get the generated key 
--- @param no number of key generated
--- @return string generated key
function SV_GenKey(no)
    return cppGenKey(no)
end

--- function wrapper of cpp_getEncrypedPW
--- @Desciption: get the encrypted pw
--- @param host pointer instance of ServerScriptingManager
--- @param pw string account pw
--- @return string encrypted pw
function SV_getEncryptPW(host, pw)
    return cpp_getEncrypedPW(host, pw)
end

--- function wrapper of cpp_updateCharacter
--- @Desciption: update character data
--- @param host pointer instance of ServerScriptingManager
--- @param character_stats table of character data
function SV_UpdateCharacter(host, character_stats)
    return cpp_updateCharacter(host, character_stats)
end

--- function wrapper of cpp_updateSkill
--- @Desciption: update skill data
--- @param host pointer instance of ServerScriptingManager
--- @param skill_stats table of skill data
--- @param name string
function SV_UpdateSkill(host, skill_stats, name)
    return cpp_updateSkill(host, skill_stats,name)
end

--- function wrapper of cpp_addCryptor
--- @Desciption: add cryptor data
--- @param host pointer instance of ServerScriptingManager
--- @param key string 
function SV_AddCryptor(host, key)
    return cpp_addCryptor(host, key)
end

--- function wrapper of cpp_removeCryptor
--- @Desciption: remove cryptor data
--- @param host pointer instance of ServerScriptingManager
--- @param key string 
function SV_RemoveCryptor(host, key)
    return cpp_removeCryptor(host, key)
end

---@Description: check if data 
---@param data table of data
function SVI_checkData(data)
    for i = 1, #data do
        if data[i] == nil then
            print("data " .. i .. " is nil")
            return false
        end
    end
    return true
end

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
    
    local tbl, pos, err = json.decode(data,1,nil)
    return tbl, pos, err
end

function SV_GetTargetPing(target)
    return cppGetTargetPing(T_Host,target)
end

---@Description: Wrapper of cpp_addClientOnlineSession | save the online session of client
---@param guid string
---@param id string (account id) 
---@param ip pointer instance of systemAddress
function SV_addClientOnlineSession_CPP(guid, id, ip)
    return cpp_addClientOnlineSession(guid, id, ip)
end


---@Description: Wrapper of cpp_removeClientOnlineSession | remove the online session of client by guid
---@param guid string
---@return boolean
function SV_removeClientOnlineSessionByGUID_CPP(guid)
    return cpp_removeClientOnlineSessionByGUID(guid)
end


---@Description: Wrapper of cpp_removeClientOnlineSession | remove the online session of client by id
---@param id pointer
---@return boolean
function SV_removeClientOnlineSessionByID_CPP(id)
    return cpp_removeClientOnlineSessionByID(id)
end

---@Description: Wrapper of cpp_getClientOnlineSessionByGUID | get the online session of client by guid
---@param guid string
---@return pointer instance of RakNet::SystemAddress
function SV_getClientIPByGUID_CPP(guid)
    return cpp_getClientOnlineSessionByGUID(guid)
end


---@Description: Wrapper of cpp_getClientOnlineSessionByID | get the online session of client by id
---@param id string
---@return RakNet_SystemAddress
function SV_getClientIPByID_CPP(id)
    return cpp_getClientOnlineSessionByID(id)
end

