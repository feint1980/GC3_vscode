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
    local tTargetGUID, targetID, serverGUID , lobbyID ,combineData = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|([^|]+)|([^|]+)|$") 
    
    local lobbyName, lobbyPassword = string.match(combineData, "^{(.-)%$(.-)}$")
    --  = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|([^|]+)|([^|]+)|([^|]+)|$")

    -- local lobbyName, lobbyPassword = string.match(combineData, "^{(.-)%$(.-)}$")

    print("tTargetGUID " .. tTargetGUID)
    print("targetID " .. targetID)
    print("serverGUID " .. serverGUID)
    print("lobbyID " .. lobbyID)
    print("lobbyName " .. lobbyName)
    print("lobbyPassword " .. lobbyPassword)

    local targetClient = SV_getClientIPByGUID_CPP(tTargetGUID)
    if targetClient == nil then
        print("invalid user,  warning, craft packet found from ip " .. SV_GetIPString(ip))
        return
    end

    print("pass request to " .. SV_GetIPString(targetClient))
    SendReliable(host,targetClient, tTargetGUID,  PacketChannel.ArenaChannel, ArenaResponse.Arena_RequestLobbyResponse,
    {tTargetGUID,targetID,serverGUID,lobbyID,combineData} )

    print("pass throught request done")
    
end

BattleServerHandling[BattleChanel.Lobby][PaperWorkRequest.LobbiesListUpdate] = function(host, data,ip,guid)
    print("lobby list update detected")

    -- print("Data : " .. data)

    local tData = string.match(data, "^|([^|]+)|$")
    local lobbyList, pos, err = JSON_Decode(tData)
    if err then
        print("Ke3 F3i117 exception (PacketChannel.LobbyChannel][PaperWorkRequest.LobbiesListUpdate)  JSON decode error:", err)
    end
    if lobbyList == nil then
        print("Ke3 F3i117 exception (PacketChannel.LobbyChannel][PaperWorkRequest.LobbiesListUpdate)")
        return
    end

    if err then 
        print("[PacketChannel.LobbyChannel][PaperWorkRequest.LobbiesListUpdate] error", err)
        return
    end

    print("list of lobbies ")
    if BSEP_List[guid] == nil then
        print("warning, unregistered battle server " .. guid .. " trying to send lobbies list")
        return
    end
    -- reset lobbies list
    BSEP_List[guid].lobbyList = {}
    for k,v in pairs(lobbyList) do
        print("lobby # " .. k )
        BSEP_List[guid].lobbyList[k] = {}
        print("id " .. lobbyList[k].id)
        BSEP_List[guid].lobbyList[k].id = lobbyList[k].id
        print("name " .. lobbyList[k].name)
        BSEP_List[guid].lobbyList[k].name = lobbyList[k].name
        print("password " .. lobbyList[k].password)
        BSEP_List[guid].lobbyList[k].password = lobbyList[k].password
        print("state " .. lobbyList[k].lobbyState)
        BSEP_List[guid].lobbyList[k].lobbyState = lobbyList[k].lobbyState
        BSEP_List[guid].lobbyList[k].battleClientEP_List = {}
        for n,m in pairs(lobbyList[k].battleClientEP_List) do
            BSEP_List[guid].lobbyList[k].battleClientEP_List[n] = {}
            print("player " .. n)
            print("player id " .. lobbyList[k].battleClientEP_List[n].id)
            BSEP_List[guid].lobbyList[k].battleClientEP_List[n].id = lobbyList[k].battleClientEP_List[n].id
            print("player guid " .. lobbyList[k].battleClientEP_List[n].guid)
            BSEP_List[guid].lobbyList[k].battleClientEP_List[n].guid = lobbyList[k].battleClientEP_List[n].guid
        end
    end

    for k,v in pairs(ClientEPList) do
        print("broadcast to " .. v.name .. "(" .. k .. ")")
        SV_SendLobbyListToClientEP(host, v:getIP(), k)
    end

end