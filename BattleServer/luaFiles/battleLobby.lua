
package.path = package.path .. ";../luaFiles/?.lua" 


require "battleWrapper"
require "BS_global"

InternalPacketHandling[MainServerChanel.Lobby][LobbyResponse.Lobby_Create_Request] = function(host, channel, request,data,ip, guid)

    print("create lobby detected")

    print(data)
    -- local targetGUID, targetID, serverGUID, lobbyName, lobbyPassword = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|([^|]+)|([^|]+)|$")

    -- print("targetGUID " .. targetGUID)
    -- print("targetID " .. targetID)
    -- print("serverGUID " .. serverGUID)
    -- print("lobbyName " .. lobbyName)
    -- print("lobbyPassword " .. lobbyPassword)

end