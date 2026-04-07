package.path = package.path .. ';../../Lua/system/Networking/?.lua;' .. ';../../Lua/TouhouTB/?.lua;' .. ';../../Lua/TouhouTB/Lobby/?.lua;'

require "clientGlobal"

TurnOrderHandling_Fn[CombatTurnOrder.Sync] = function(data)

    print("Turn order sync ")
    print("data " .. data)

    TM_addTask(function()
        CombatField_instance:showBannerMsg("Roll phase")
        end,50)
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
        
        TurnDisplayer_instance:addIcon(v.characterId,tonumber(v.side),tonumber(v.order))

        local tCharacter = TurnDisplayer_instance:getCharacterIcon(v.characterId,v.side)
        if tCharacter ~= nil then
            CTD_SetCharacterSpeed(tCharacter,v.speed)
            CTD_SetCharacterDisplaySpeed(tCharacter,v.speed)
        end
        -- for k2,v2 in pairs(v) do
        --     print("     k2 " .. k2 .. " v2 " .. v2)
            
        -- end
    end

    TurnDisplayer_instance:updateOrder()

end


TurnOrderHandling_Fn[CombatTurnOrder.RollResult] = function(data)

    print("Roll Result ")
    
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
        print("roll result " .. v.rollResult)
        print("speed " .. v.speed)
        
        local tCharacter = TurnDisplayer_instance:getCharacterIcon(v.characterId,v.side)
        if tCharacter ~= nil then
            CTD_SetCharacterOrder(tCharacter,v.order)
            CTD_SetCharacterSpeedChange(tCharacter,v.rollResult)
            CTD_SetCharacterSpeed(tCharacter,v.speed)
        end
    end

    EP_SetPollSignal("TurnDisplayerIsReady", false)

    TM_addTask(function()
        TurnDisplayer_instance:setUpdateSpeedChange(true)
    end
    ,50
    )

end


TurnOrderHandling_Fn[CombatTurnOrder.PlayerCharacterTurn] = function(data)

    print("CombatTurnOrder.PlayerCharacterTurn get")

    local tData, pos ,err = JSON_Decode(data)
    if err then
        print("Ke3 F3i117 exception (PacketChannel.Combat][CCombatResponse.Combat_TurnOrder]  JSON decode error:", err)
    end
    if tData == nil then
        print("Ke3 F3i117 exception (PacketChannel.Combat][CCombatResponse.Combat_TurnOrder)")
        return
    end

    print("player " .. tData.playerId .. " on the side " .. tData.characterSide .. " controlling " .. tData.characterId .. " turn ")

    -- EventPipeline.emit("COMBAT_ON_PLAYER_TURN", {data = tData})
    Poll_AddTask("TurnDisplayReady", function()
            TM_addTask(function()

                CombatField_instance:showBannerMsg("Player " .. tData.playerId .. "'s turn")
            end,30)
        end)
    --- handle turn here 
    

end