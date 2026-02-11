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


---MARK: Client Data 
BattleServerHandling[BattleChanel.ClientData][ClientDataResponse.ClientData_Request_Fomration] = function(host, data,ip,guid)

    print("ClientDataResponse.ClientData_Request_Fomration request from " .. guid )

    local targetGUID, targetID = string.match(data, "^|([^|]+)|([^|]+)|$")
    
    print ("targetGUID " .. targetGUID)
    print ("targetID " .. targetID)

    local targetClient = CH_FindClient(targetGUID)
    if targetClient == nil then
        print("invalid user,  warning, craft packet found from ip " .. SV_GetIPString(ip))
        return
    end

    if targetClient.name ~= targetID then
        print("mismatch client session (ClientDataResponse.ClientData_Request_Fomration)") 
        return
    end

    local queriedFormations = {}

    local getFormationQuery = "SELECT " .. Table.formation.index .. "," .. Table.formation.name .. " FROM " .. Table.formation.tb_name .. " WHERE " .. Table.formation.account_id .. " = ?;"

    SVI_DoQuerySTMT(host,getFormationQuery,{targetID})

    local formationQueryResult = Table_DeepCopy(Query_val)

    for i=1,#formationQueryResult,2 do
        print(" index " .. formationQueryResult[i])
        local index = formationQueryResult[i]
        print(" name " .. formationQueryResult[i+1])
        local name = formationQueryResult[i+1]

        queriedFormations[index] = {}
        queriedFormations[index].name = name

        local formationDataQuery = "SELECT " .. Table.formation_info.character_id .. "," .. Table.formation_info.slot_index .. "," .. Table.formation_info.row_pos .. "," .. Table.formation_info.col_pos .. " FROM " .. Table.formation_info.tb_name .. " WHERE " .. Table.formation_info.account_id .. " = ? AND " .. Table.formation_info.formation_index .. " = ?;"

        SVI_DoQuerySTMT(host,formationDataQuery,{targetID,index})
        local formationDataQueryResult = Table_DeepCopy(Query_val)

        queriedFormations[index].formationData = {}
        -- local formationInfoIndex = 1
        for j=1,#formationDataQueryResult,4 do
            local tFormationData = {}
            tFormationData.character_id = formationDataQueryResult[j]
            tFormationData.slot_index = formationDataQueryResult[j+1]
            tFormationData.row_pos = formationDataQueryResult[j+2]
            tFormationData.col_pos = formationDataQueryResult[j+3]
            -- queriedFormations[index].formationData[ formationDataQueryResult[j+1]] = tFormationData

            table.insert(queriedFormations[index].formationData,tFormationData)
        end
    end

    local tData = JSON_Encode(queriedFormations,true)

    SV_SendWrapMsg2BattleServer(host, ip,guid, BattleChanel.ClientData,ClientDataResponse.ClientData_Response_Fomration,{targetGUID, targetID, tData})


end


BattleServerHandling[BattleChanel.ClientData][ClientDataResponse.ClientData_Request_OwnedCharacters] = function(host, data,ip,guid)

    print("ClientDataResponse.ClientData_Request_OwnedCharacters request from " .. guid )

    local targetGUID, targetID = string.match(data, "^|([^|]+)|([^|]+)|$")
    
    print ("targetGUID " .. targetGUID)
    print ("targetID " .. targetID)

    local targetClient = CH_FindClient(targetGUID)
    if targetClient == nil then
        print("invalid user,  warning, craft packet found from ip " .. SV_GetIPString(ip))
        return
    end

    if targetClient.name ~= targetID then
        print("mismatch client session (ClientDataResponse.ClientData_Request_OwnedCharacters)") 
        return
    end

    local queriedFormations = {}

    local getOwnedCharacterQuery = "SELECT " .. Table.user_character.character_id .. "," .. Table.user_character.level .. "," .. Table.user_character.exp .. "," .. Table.user_character.stats .. " FROM " .. Table.user_character.tb_name .. " WHERE " .. Table.user_character.id .. " = ?;"
    SVI_DoQuerySTMT(host,getOwnedCharacterQuery,{targetID})

    local ownedQueriedCharacterResult = Table_DeepCopy(Query_val)

    local ownedResult = {}
    for i = 1, #ownedQueriedCharacterResult,4 do
        local characterData = {}
        print("character_id " .. ownedQueriedCharacterResult[i])
        local character_id = ownedQueriedCharacterResult[i]
        characterData.ID = character_id
        print("level " .. ownedQueriedCharacterResult[i+1])
        local level = ownedQueriedCharacterResult[i+1]
        characterData.level = level
        print("exp " .. ownedQueriedCharacterResult[i+2])
        local exp = ownedQueriedCharacterResult[i+2]
        characterData.exp = exp
        print("stats " .. ownedQueriedCharacterResult[i+3])
        local stats = ownedQueriedCharacterResult[i+3]
        characterData.stats = stats
        ownedResult[character_id] = characterData
    end


    local tData = JSON_Encode(ownedResult,true)

    -- print("data check " .. tData)

    SV_SendWrapMsg2BattleServer(host, ip,guid, BattleChanel.ClientData,ClientDataResponse.ClientData_Response_OwnedCharacters,{targetGUID, targetID, tData})


end