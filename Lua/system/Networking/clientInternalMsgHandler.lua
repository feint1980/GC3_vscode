
require "clientSide"

Client_InternalMsgHandling = {}


function InteralMsgHandler(host, packetID,guid,data)

    for packetID in pairs(PacketID) do
        if Client_InternalMsgHandling[packetID] == nil then
            print("packetID " .. packetID .. " not handled")
        else
            Client_InternalMsgHandling[packetID](host,packetID,guid,data)
        end
    end
end

Client_InternalMsgHandling[PacketID.ID_DISCONNECTION_NOTIFICATION] = function(host,packetID,guid,data)
    print("ID_DISCONNECTION_NOTIFICATION from " .. guid)
end

Client_InternalMsgHandling[PacketID.ID_ALREADY_CONNECTED] = function(host,packetID,guid,data)
    print("ID_ALREADY_CONNECTED from " .. guid)
end

Client_InternalMsgHandling[PacketID.ID_INCOMPATIBLE_PROTOCOL_VERSION] = function(host,packetID,guid,data)
    print("ID_INCOMPATIBLE_PROTOCOL_VERSION from " .. guid)
end

Client_InternalMsgHandling[PacketID.ID_REMOTE_DISCONNECTION_NOTIFICATION] = function(host,packetID,guid,data)
    print("ID_REMOTE_DISCONNECTION_NOTIFICATION from " .. guid)
end

Client_InternalMsgHandling[PacketID.ID_REMOTE_CONNECTION_LOST] = function(host,packetID,guid,data)
    print("ID_REMOTE_CONNECTION_LOST from " .. guid)
end

Client_InternalMsgHandling[PacketID.ID_REMOTE_NEW_INCOMING_CONNECTION] = function(host,packetID,guid,data)
    print("ID_REMOTE_NEW_INCOMING_CONNECTION from " .. guid)
end

Client_InternalMsgHandling[PacketID.ID_CONNECTION_BANNED] = function(host,packetID,guid,data)
    print("ID_CONNECTION_BANNED from " .. guid)
end

Client_InternalMsgHandling[PacketID.ID_CONNECTION_ATTEMPT_FAILED] = function(host,packetID,guid,data)
    print("ID_CONNECTION_ATTEMPT_FAILED from " .. guid)
end

Client_InternalMsgHandling[PacketID.ID_NO_FREE_INCOMING_CONNECTIONS] = function(host,packetID,guid,data)
    print("ID_NO_FREE_INCOMING_CONNECTIONS from " .. guid)

end

Client_InternalMsgHandling[PacketID.ID_CONNECTION_LOST] = function(host,packetID,guid,data)
    print("ID_CONNECTION_LOST from " .. guid)
end


Client_InternalMsgHandling[PacketID.ID_CONNECTION_REQUEST_ACCEPTED] = function(host,packetID,guid,data)
    print("ID_CONNECTION_REQUEST_ACCEPTED from " .. guid)
end


Client_InternalMsgHandling[PacketID.ID_UNCONNECTED_PING] = function(host,packetID,guid,data)
    print("ID_UNCONNECTED_PING from " .. guid)
end

Client_InternalMsgHandling[PacketID.ID_UNCONNECTED_PONG] = function(host,packetID,guid,data)
    print("ID_UNCONNECTED_PONG from " .. guid)
end








