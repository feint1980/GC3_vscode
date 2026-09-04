package.path = package.path .. ';../../Lua/system/Networking/?.lua;' .. ';../../Lua/TouhouTB/?.lua;' .. ';../../Lua/TouhouTB/Lobby/?.lua;' .. ';../../Lua/TouhouTB/Combat/UI/?.lua;'

require "clientGlobal"
require "dock_global"


TurnOrderHandling_Fn[CombatTurnOrder.Sync] = function(data)

    print("Turn order sync ")
    -- print("data " .. data)

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

    local selfID = InfoHolder_getStrVal("MainInfo.id")
    for k,v in pairs(orderList) do
        print("k " .. k)
        print("character ID " .. v.characterId)
        print("order " .. v.order)
        print("side " .. v.side)
        print('ownerId ' .. v.ownerId)
        CombatField_instance:setPlayerSide(v.ownerId,tonumber(v.side))
        -- if v.ownerId == selfID then
        --     CombatField_instance:setPlayerSide(tonumber(v.side))
        -- end
        -- if ()
        TurnDisplayer_instance:addIcon(v.characterId,tonumber(v.side),tonumber(v.order))

        local tCharacter = TurnDisplayer_instance:getCharacterIcon(v.characterId,v.side)
        if tCharacter ~= nil then
            CTD_SetCharacterSpeed(tCharacter,v.speed)
            CTD_SetCharacterDisplaySpeed(tCharacter,v.speed)
        end

    end





    TurnDisplayer_instance:updateOrder()

end


TurnOrderHandling_Fn[CombatTurnOrder.RollResult] = function(data)

    -- print("Roll Result ")

    -- print("data " .. data)

    local orderList, pos ,err = JSON_Decode(data)
    if err then
        print("Ke3 F3i117 exception (PacketChannel.Combat][CCombatResponse.Combat_TurnOrder]  JSON decode error:", err)
    end
    if orderList == nil then
        print("Ke3 F3i117 exception (PacketChannel.Combat][CCombatResponse.Combat_TurnOrder)")
        return
    end

    for k,v in pairs(orderList) do
        -- print("k " .. k)
        -- print("character ID " .. v.characterId)
        -- print("order " .. v.order)
        -- print("side " .. v.side)
        -- print("roll result " .. v.rollResult)
        -- print("speed " .. v.speed)
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

    -- Handle if it was the player turn. 
    local selfID = InfoHolder_getStrVal("MainInfo.id")
    print("selfID " .. selfID)

    print("compare result")
    print(selfID .. "/" .. tData.playerId)
    
    CombatField_instance:setCurrentCharacterInTurn(tData.playerId, tData.characterId)

    if selfID == tData.playerId then
        print("it is the player turn")

    else
        print("it is the opponent turn")
    end


end