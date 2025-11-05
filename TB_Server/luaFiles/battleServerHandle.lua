package.path = package.path .. ";../luaFiles/?.lua" 

require "serverWrapper"
require "SV_global"


BattleServerHandling[BattleChanel.PaperWork][PaperWorkRequest.SelfRegister] = function(host, data,ip,guid)

    print("self register detected")
    print("From server IP:" .. SV_GetIPString(ip))
    print("GUID:" .. guid)
    print("Data:" .. data)
    if data == "v221" then
        print("battle server register accepted")
        SendReliable2BattleServer(host,ip,guid,BattleChanel.PaperWork,PaperWorkRequest.SelfRegisterAccepted,{guid} )
        --- handle battle server here


    end

end

