print("Battle side script started ...")

package.path = package.path .. ";../luaFiles/?.lua" 

require "battleWrapper"
require "BS_global"

BS_Host = nil
function BattleSide_Init(host)
    print("BattleSide_Init lua init")
    BS_Host = host

    MainInfo.guid = cpp_BM_GetInfo(host)
end


---- Handle Common

function BattleMain_HandleCommon(host, packet, packetID)

    if CommonPacketHandling[packetID] ~= nil then
        CommonPacketHandling[packetID](host,packet)
    end
end

CommonPacketHandling[ID_CONNECTION_REQUEST_ACCEPTED] = function(host,packet)
    BM_handleIncomingConnection(host,packet)
end

CommonPacketHandling[ID_CONNECTION_ATTEMPT_FAILED] = function(host,packet)
    print("failed to connect to main server")
end

CommonPacketHandling[ID_CONNECTION_LOST] = function(host,packet)
    print("main server lost")
end

---- Internal 

-- for i = 1, #BattleChanel do
--     InternalPacketHandling[i] = {}
-- end

InternalPacketHandling[BattleChanel.PaperWork] = {}

require "battlePaperWork"

function BattleMain_HandleInternal(host, channel, request,data,ip, guid)

    print("BattleMain_HandleInternal called")
    if InternalPacketHandling[channel] == nil then
        print("channel not found " .. channel)
        return
    end
    if InternalPacketHandling[channel][request] ~= nil then
        InternalPacketHandling[channel][request](host, channel, request,data,ip, guid)
    else
        print("request not found channel " .. channel .. " request " .. request)
    end
end


function Battlemain_GetInfo()
    return cpp_BM_GetInfo(BS_Host)
end

