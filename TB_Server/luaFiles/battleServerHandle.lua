--- Main server handle battle servers


package.path = package.path .. ";../luaFiles/?.lua" .. ";../luaFiles/BattleServer/?.lua" 

require "serverWrapper"
require "SV_global"
require "BSEP"


--- MARK: PaperWork 
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
        BSEP_List[guid]:init(host,ip,guid,name, SV_GetPortFromIP(ip))
        BSEP_List[guid].IP = ip
        BSEP_List[guid].GUID = guid
        BSEP_List[guid].name = name
        BSEP_List[guid].port = SV_GetPortFromIP(ip)
    end
end

---MARK: Lobbies
BattleServerHandling[BattleChanel.Lobby][LobbyResponse.Lobby_Create_Response] = function(host, data,ip,guid)

    print("lobby create response detected")
    print("From server IP:" .. SV_GetIPString(ip))
    print("GUID:" .. guid)
    print("Data:" .. data)
    local tTargetGUID, targetID, serverGUID , lobbyID , lobbyName, lobbyPassword = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|([^|]+)|([^|]+)|([^|]+)|$")

    -- local lobbyName, lobbyPassword = string.match(combineData, "^{(.-)%$(.-)}$")

    print("tTargetGUID " .. tTargetGUID)
    print("targetID " .. targetID)
    print("serverGUID " .. serverGUID)
    print("lobbyID " .. lobbyID)
    print("lobbyName " .. lobbyName)
    print("lobbyPassword " .. lobbyPassword)

    local targetClient = CH_FindClient(tTargetGUID)
    if targetClient == nil then
        print("invalid user,  warning, craft packet found from ip " .. SV_GetIPString(ip))
        return
    end

    print("pass request to " .. SV_GetIPString(targetClient.IP))
    SendReliable(host,targetClient.IP, tTargetGUID,  PacketChannel.ArenaChannel, ArenaResponse.Arena_RequestLobbyResponse,
    {tTargetGUID,targetID,serverGUID,lobbyID,lobbyName,lobbyPassword} )

    print("pass throught request done")
    
end