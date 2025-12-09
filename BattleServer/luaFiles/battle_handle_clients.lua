package.path = package.path .. ";../luaFiles/?.lua" 

require "battleWrapper"
require "BS_global"

ClientPacketHandling[ClientChannel.InfoChannel][BattleInfoResponse.BattleInfo_AddCryptor_Request] = function(host, channel, request,data,ip, guid)

    print("add cryptor detected")
    -- print("add cryptor from " .. guid)
end

