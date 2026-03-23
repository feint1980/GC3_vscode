package.path = package.path .. ';../../Lua/system/Networking/?.lua;' .. ';../../Lua/TouhouTB/?.lua;' .. ';../../Lua/TouhouTB/Lobby/?.lua;'

require "clientGlobal"

TurnOrderHandling_Fn[CombatTurnOrder.Sync] = function(data)

    print("Turn order sync ")
    
    print("data " .. data)

    local orderList, pos ,err = JSON_Decode(data)
    if err then
        print("Ke3 F3i117 exception (PacketChannel.Combat][CCombatResponse.Combat_TurnOrder]  JSON decode error:", err)
    end
    if orderList == nil then
        print("Ke3 F3i117 exception (PacketChannel.Combat][CCombatResponse.Combat_TurnOrder)")
        return
    end

    for k,v in pairs(orderList) do
        print("k " .. k)
        print("character ID " .. v.characterId)
        print("order " .. v.order)
        print("side " .. v.side)
        TurnDisplayer_instance:addPortrait(v.characterId,tonumber(v.side))
        -- for k2,v2 in pairs(v) do
        --     print("     k2 " .. k2 .. " v2 " .. v2)
            
        -- end
    end



end