package.path = package.path .. ";../luaFiles/?.lua" 

require "battleWrapper"
require "BS_global"

InternalPacketHandling[BattleChanel.PaperWork][PaperWorkRequest.SelfRegisterAccepted] = function(host, channel, request,data,ip, guid)


    local t_guid = string.match(data, "^|([^|]+)|$")

    if t_guid == nil then
        print("Ke3 F3i117 exception (InternalPacketHandling[BattleChanel.PaperWork][PaperWorkRequest.SelfRegisterAccepted])")
        return
    end

    if t_guid == MainInfo.guid then
        print("register accepted by server")
    else
        print("rejected by server main")
    end
    
end