
package.path = package.path .. ";../luaFiles/?.lua" 


require "battleWrapper"
require "BS_global"

InternalPacketHandling[MainServerChanel.Lobby][LobbyResponse.Lobby_Create_Request] = function(host, channel, request,data,ip, guid)

    print("create lobby detected")

    -- print(data)
    local tTargetGUID, targetID, serverGUID , combineData = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|([^|]+)|$")

    
    local lobbyName, lobbyPassword = string.match(combineData, "^{(.-)%$(.-)}$")

    print("lobby name " .. lobbyName)
    print("lobby password " .. lobbyPassword)
    cpp_BM_CreateLobby(host,lobbyName,lobbyPassword)
end