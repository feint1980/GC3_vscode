package.path = package.path .. ';../../Lua/system/Networking/?.lua;' .. ';../../Lua/TouhouTB/?.lua;' .. ';../../Lua/TouhouTB/Lobby/?.lua;'


CombatBattleHandling[BattlePacketChannel.Combat][CCombatResponse.Combat_Match_Start] = function(host,data,guid)

    print("Combat_Match_Start detected from " .. guid)
end