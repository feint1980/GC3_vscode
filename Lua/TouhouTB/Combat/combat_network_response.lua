package.path = package.path .. ';../../Lua/system/Networking/?.lua;' .. ';../../Lua/TouhouTB/?.lua;' .. ';../../Lua/TouhouTB/Lobby/?.lua;'

require "clientGlobal"

require "combat_fn"
require "turnOrder_fn"

CombatBattleHandling[BattlePacketChannel.Combat][CCombatResponse.Combat_IngameData] = function(host,data,guid)

    print("Combat_IngameData detected from " .. guid)

    -- print(data)

    -- local guid,id,type,lobbyID, p1Id, p2Id, p1Formation, p2Formation = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|([^|]+)|([^|]+)|$")
    local guid,id,type,data = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|([^|]+)|$")


    print("guid " .. guid)
    print("id " .. id)
    print("type " .. type)

    local tType = tonumber(type)

    if CombatHandling_Fn[tType] == nil  then
        print("CombatHandling_Fn not available : " .. tType )
        return
    end
    CombatHandling_Fn[tType](data)

end


CombatBattleHandling[BattlePacketChannel.Combat][CCombatResponse.Combat_TurnOrder] = function(host,data,guid)

    print("Combat_IngameData detected from " .. guid)

    -- local guid,id,type,lobbyID, p1Id, p2Id, p1Formation, p2Formation = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|([^|]+)|([^|]+)|$")
    local guid,id,type,data = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|([^|]+)|$")

    print("guid " .. guid)
    print("id " .. id)
    print("type " .. type)

    local tType = tonumber(type)

    if TurnOrderHandling_Fn[tType] == nil  then
        print("TurnOrderHandling_Fn not available : " .. tType )
        return
    end
    TurnOrderHandling_Fn[tType](data)
end