print("Battle side script started ...")

package.path = package.path .. ";../luaFiles/?.lua" 

require "battleWrapper"
require "BS_global"

BS_Host = nil
function BattleSide_Init(host)
    print("BattleSide_Init lua init")
    BS_Host = host
end

ID_DISCONNECTION_NOTIFICATION = 21
ID_NEW_INCOMING_CONNECTION  = 19
ID_INCOMPATIBLE_PROTOCOL_VERSION = 25
ID_CONNECTED_PING = 0
ID_UNCONNECTED_PING = 1
ID_CONNECTION_LOST = 22
ID_CONNECTION_REQUEST_ACCEPTED = 16
ID_CONNECTION_ATTEMPT_FAILED = 17

CommonPacketHandling = {}

function BattleMain_HandleCommon(host, packet, packetID)

    if CommonPacketHandling[packetID] ~= nil then
        CommonPacketHandling[packetID](host,packet)
    end
end

CommonPacketHandling[ID_CONNECTION_REQUEST_ACCEPTED] = function(host,packet)
    print("connected to main server")
end

CommonPacketHandling[ID_CONNECTION_ATTEMPT_FAILED] = function(host,packet)
    print("failed to connect to main server")
end

CommonPacketHandling[ID_CONNECTION_LOST] = function(host,packet)
    print("main server lost")
end

