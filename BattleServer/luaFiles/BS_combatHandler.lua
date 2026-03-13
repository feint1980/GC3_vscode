--- Battle server, lobby section
package.path = package.path .. ";../luaFiles/?.lua" 


require "battleWrapper"
require "BS_global"
require "BS_handle_clients"
require "BS_formation"


ClientPacketHandling[ClientChannel.Combat][CCombatResponse.Combat_ReadyStatus] = function(host, channel, request,data,ip, guid)
    print("Combat_ReadyStatus detected from " .. guid)
    print(data)

    -- local tGUID, tID, tLobbyID, tPlayerIndex , status = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|([^|]+)|([^|]+)|$")

    -- parse from this data : |869194754175014699|huyen13|8268922112124474966|2.0|Ready|

    -- local tGUID, tID, tLobbyID, tPlayerIndex , status = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|([^|]+)|([^|]+)|$")

    local tGUID, tID, tLobbyID, tPlayerIndex , status = string.match(data, "|([^|]+)|([^|]+)|([^|]+)|([^|]+)|([^|]+)|")

    print("tGUID " .. tGUID)
    print("tID " .. tID)
    print("tPlayerIndex " .. tPlayerIndex)
    print("tLobbyID " .. tLobbyID)
    print("status " .. status)

    if BattleLobby_List[tLobbyID] ~= nil then
        print("Lobby check out")
        BattleLobby_List[tLobbyID]:AppendReady(host,tID,tonumber(tPlayerIndex))
    end

end

