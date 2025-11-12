package.path = package.path .. ";../luaFiles/?.lua" .. ";../luaFiles/BattleServer/?.lua" 

require "serverWrapper"
require "SV_global"
require "BSEP"

BattleServerHandling[BattleChanel.PaperWork][PaperWorkRequest.SelfRegister] = function(host, data,ip,guid)

    print("self register detected")
    print("From server IP:" .. SV_GetIPString(ip))
    print("GUID:" .. guid)
    -- print("Data:" .. data)
    local phrase, name = string.match(data, "^|([^|]+)|([^|]+)|$")

    if phrase == "v221" then
        print("battle server ".. name .. " accepted")
        SendReliable2BattleServer(host,ip,guid,BattleChanel.PaperWork,PaperWorkRequest.SelfRegisterAccepted,{guid} )

        BSEP_List[guid] = BSEP:new()
        BSEP_List[guid]:init(ip,guid,name, SV_GetPortFromIP(ip))
        BSEP_List[guid].IP = ip
        BSEP_List[guid].GUID = guid
        BSEP_List[guid].name = name
        BSEP_List[guid].port = SV_GetPortFromIP(ip)

    end
end

