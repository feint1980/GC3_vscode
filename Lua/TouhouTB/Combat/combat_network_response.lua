package.path = package.path .. ';../../Lua/system/Networking/?.lua;' .. ';../../Lua/TouhouTB/?.lua;' .. ';../../Lua/TouhouTB/Lobby/?.lua;'


CombatBattleHandling[BattlePacketChannel.Combat][CCombatResponse.Combat_Match_Start] = function(host,data,guid)

    print("Combat_Match_Start detected from " .. guid)

    -- print(data)

    local lobbyID, p1Id, p2Id, p1Formation, p2Formation = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|([^|]+)|([^|]+)|$")

    print("lobbyID " .. lobbyID)
    print("p1Id " .. p1Id)
    print("p2Id " .. p2Id)
    print("p1Formation " .. p1Formation)
    print("p2Formation " .. p2Formation)

end