package.path = package.path .. ';../../Lua/system/Networking/?.lua;' .. ';../../Lua/TouhouTB/?.lua;' .. ';../../Lua/TouhouTB/Lobby/?.lua;'

require "clientGlobal"


CombatHandling_Fn[CombatIngameData.Sync] = function(data)

    local tData , pos, err = JSON_Decode(data)
    if err then
        print("Ke3 F3i117 exception (PacketChannel.Combat][CCombatResponse.Combat_IngameData]  JSON decode error:", err)
    end

    print("Combat Sync get ")

    -- for k,v in pairs(tData) do
    --     print("k " .. k)
    -- end

    local lobbyID = tData[1]
    local p1Id = tData[2]
    local p2Id = tData[3]
    local p1Formation = tData[4]
    local p2Formation = tData[5]

    print("lobbyID " .. lobbyID)
    print("p1Id " .. p1Id)
    print("p2Id " .. p2Id)
    -- print("p1Formation " .. p1Formation)
    -- print("p2Formation " .. p2Formation)

    local p1FormationInfo, pos, err = JSON_Decode(p1Formation)
    if err then
        print("Ke3 F3i117 exception (PacketChannel.Combat][CCombatResponse.Combat_IngameData]  JSON decode error:", err)
    end
    local p2FormationInfo, pos, err = JSON_Decode(p2Formation)
    if err then
        print("Ke3 F3i117 exception (PacketChannel.Combat][CCombatResponse.Combat_IngameData]  JSON decode error:", err)
    end

    -- print("p1FormationInfo " .. p1FormationInfo.stats)
    -- print("p2FormationInfo " .. p2FormationInfo)

    for k,v in pairs(p1FormationInfo) do
        CombatField_instance:addCharacter(p1FormationInfo[k].colPos, 
        p1FormationInfo[k].rowPos, 1, p1FormationInfo[k].characterId,"" )

    end
    for k ,v in pairs(p2FormationInfo) do
        CombatField_instance:addCharacter(p2FormationInfo[k].colPos, 
        p2FormationInfo[k].rowPos, 2, p2FormationInfo[k].characterId,"" )
    end

    for k,v in pairs(p1FormationInfo) do
        local tCharacter = CombatField_instance:getCharacter(p1FormationInfo[k].characterId,1)
        print(p1FormationInfo[k].characterId)
        if tCharacter ~= nil then 
            print("character " .. p1FormationInfo[k].characterId .. " valid" )
        end
        
        for k2,v2 in pairs(v) do
            if k2 ~= "colPos" and k2 ~= "rowPos" then
                if type(v[k2]) == "number" then
                    CF_SetCharacterStatFloat(tCharacter, k2, v[k2])
                elseif type(v[k2]) == "string" then
                    CF_SetCharacterStatString(tCharacter, k2, v[k2])
                end
            end
            -- print("K2 " .. k2 .. ":" .. v[k2] .. " type " .. type(v[k2]))
        end
        -- CF_ListCharacterStats(tCharacter)
    end

    print("p2 check")
    for k,v in pairs(p2FormationInfo) do
        print(p2FormationInfo[k].characterId)
        local tCharacter = CombatField_instance:getCharacter(p2FormationInfo[k].characterId,2)
        if tCharacter ~= nil then 
            print("character " .. p2FormationInfo[k].characterId .. " valid" )
        end
        for k2,v2 in pairs(v) do
            if k2 ~= "colPos" and k2 ~= "rowPos" then
                if type(v[k2]) == "number" then
                    CF_SetCharacterStatFloat(tCharacter, k2, v[k2])
                elseif type(v[k2]) == "string" then
                    CF_SetCharacterStatString(tCharacter, k2, v[k2])
                end
            end
            -- print("K2 " .. k2 .. ":" .. v[k2] .. " type " .. type(v[k2]))
        end
        -- CF_ListCharacterStats(tCharacter)
    end

    -- CombatField_instance:addCharacter


    CombatScene_SetSceneReady()

end