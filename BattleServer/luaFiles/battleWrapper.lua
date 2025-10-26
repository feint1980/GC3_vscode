BattlePacketType = {

    ID_TH_TB = 135, -- info from client to main server
	ID_TH_TB_BATTLE = 136, -- info from client to battle server
	ID_TH_INTERNAL = 137, -- main server to battle server
}

BattlePacketChanel = {
    PaperWork = 1,
    ClientRequest = 2,
    Combat = 3
}

PaperWorkRequest = {

    SelfRegister = 1,

}


---@description handle incoming connection
---@param host pointer instance of BattleMain
---@param packet pointer instance of RakNet::Packet
function BM_handleIncomingConnection(host, packet)
    cpp_handleIncomingConnection(host,packet)
end


---@Description: wrap packet with headers [channel][request][data * n]
---@param id number RakNet PacketID
---@param channel number channel
---@param request number request
---@param list table data
---@return string
function BM_WrapMsg(id,channel, request, list)
    -- print("WrapMsg called")
    local returnValue = ""
    returnValue = string.char(id) .. string.char(channel) .. string.char(request) .. "|"
    for i = 1, #list do
        returnValue = returnValue .. list[i] .. "|"
    end
    -- print("result check " .. returnValue)
    return returnValue
end

function BM_sendWrapData(host,targetIP, guid, id,channel, request, list)
    return cpp_BM_SendWrapData(host,targetIP,guid, BM_WrapMsg(id,channel, request, list))
end
