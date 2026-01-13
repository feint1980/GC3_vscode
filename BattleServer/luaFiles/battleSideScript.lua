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

    local tPort = BS_Packet_getPort(packet)
    if tPort == 1123 then
        print("disconnected from main server") 
        -- TODO consider make a reconnect attempts
    else
        local tGUID = BS_Packet_getGUID(packet)
        print("lost connection to " .. tGUID)
        BM_removeCryptor(host,tGUID)
        if BattleClientEP_List[tGUID] ~= nil then
            print("remove the client " .. tGUID .. " from list ")
            print("check for lobby ID " .. BattleClientEP_List[tGUID].lobbyID)
            if BattleClientEP_List[tGUID].lobbyID ~= "" then
                local tLobbyID = BattleClientEP_List[tGUID].lobbyID
                if BattleLobby_List[tLobbyID] ~= nil then
                    BattleLobby_List[tLobbyID]:removePlayer(tGUID)
                end
            end
            BattleClientEP_List[tGUID] = nil
        end
        BattleLobby_UpdateLobbiesStatus() --- update status
        BattleLobby_Notify_LobbiesStates(host)
    end

end

CommonPacketHandling[ID_UNCONNECTED_PING] = function(host,packet)
    print("ID_UNCONNECTED_PING get")
    cpp_sendBackPong(host,packet)
end

CommonPacketHandling[ID_NEW_INCOMING_CONNECTION] = function(host,packet)
    print("ID_NEW_INCOMING_CONNECTION get")
    BM_handleIncomingConnection(host,packet)
end


---- Internal 

for k,v in pairs(MainServerChanel) do
    InternalPacketHandling[v] = {}
end

for k , v in pairs(ClientChannel) do
    ClientPacketHandling[v] = {}
end


-- InternalPacketHandling[MainServerChanel.PaperWork] = {}

require "battlePaperWork"
require "BS_lobbiesHandler"
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

function BattleMain_HandleClient(host, channel, request,data,ip, guid)

    print("BattleMain_HandleInternal called")
    if ClientPacketHandling[channel] == nil then
        print("channel not found " .. channel)
        return
    end
    if ClientPacketHandling[channel][request] ~= nil then
        ClientPacketHandling[channel][request](host, channel, request,data,ip, guid)
    else
        print("request not found channel " .. channel .. " request " .. request)
    end
end

function Battlemain_GetInfo()
    return cpp_BM_GetInfo(BS_Host)
end

--- MARK:Client handle
require "BS_handle_clients"
require "BS_lobby"

