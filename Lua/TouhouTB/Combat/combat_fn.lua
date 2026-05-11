package.path = package.path .. ';../../Lua/system/Networking/?.lua;' .. ';../../Lua/TouhouTB/?.lua;' .. ';../../Lua/TouhouTB/Lobby/?.lua;'

require "clientGlobal"
require "combat_stage_sequence"


CombatHandling_Fn[CombatIngameData.Sync] = function(data)

    local tData , pos, err = JSON_Decode(data)
    if err then
        print("Ke3 F3i117 exception (PacketChannel.Combat][CCombatResponse.Combat_IngameData]  JSON decode error:", err)
    end

    print("Combat Sync get ")

    local lobbyID = tData[1]
    local p1Id = tData[2]
    local p2Id = tData[3]
    local p1Formation = tData[4]
    local p2Formation = tData[5]

    local p1FormationInfo, pos, err = JSON_Decode(p1Formation)
    if err then
        print("Ke3 F3i117 exception (PacketChannel.Combat][CCombatResponse.Combat_IngameData]  JSON decode error:", err)
    end
    local p2FormationInfo, pos, err = JSON_Decode(p2Formation)
    if err then
        print("Ke3 F3i117 exception (PacketChannel.Combat][CCombatResponse.Combat_IngameData]  JSON decode error:", err)
    end

    for k,v in pairs(p1FormationInfo) do
        CombatField_instance:addCharacter(p1FormationInfo[k].colPos, 
        p1FormationInfo[k].rowPos, 1, p1FormationInfo[k].characterID,"" )

        -- convert to number ( if not c++ parse will error)
        v.colPos = tonumber(v.colPos)
        v.rowPos = tonumber(v.rowPos)
        local jsonData = JSON_Encode(v)
        CombatField_instance:FieldInfo_SetCharacter(p1FormationInfo[k].characterID,1,jsonData)
    end
    for k ,v in pairs(p2FormationInfo) do
        CombatField_instance:addCharacter(p2FormationInfo[k].colPos, 
        p2FormationInfo[k].rowPos, 2, p2FormationInfo[k].characterID,"" )
        
        -- convert to number ( if not c++ parse will error)
        v.colPos = tonumber(v.colPos)
        v.rowPos = tonumber(v.rowPos)
        local jsonData = JSON_Encode(v)
        CombatField_instance:FieldInfo_SetCharacter(p2FormationInfo[k].characterID,2,jsonData)
    end

    for k,v in pairs(p1FormationInfo) do
        local tCharacter = CombatField_instance:getCharacter(p1FormationInfo[k].characterID,1)
        print(p1FormationInfo[k].characterID)
        if tCharacter ~= nil then 
            print("character " .. p1FormationInfo[k].characterID .. " valid" )
        end
        for k2,v2 in pairs(v) do
            if k2 ~= "colPos" and k2 ~= "rowPos" then
                if type(v[k2]) == "number" then
                    CF_SetCharacterStatFloat(tCharacter, k2, v[k2])
                elseif type(v[k2]) == "string" then
                    CF_SetCharacterStatString(tCharacter, k2, v[k2])
                end
            end
        end
    end

    print("p2 check")
    for k,v in pairs(p2FormationInfo) do
        print(p2FormationInfo[k].characterID)
        local tCharacter = CombatField_instance:getCharacter(p2FormationInfo[k].characterID,2)
        if tCharacter ~= nil then 
            print("character " .. p2FormationInfo[k].characterID .. " valid" )
        end
        for k2,v2 in pairs(v) do
            if k2 ~= "colPos" and k2 ~= "rowPos" then
                if type(v[k2]) == "number" then
                    CF_SetCharacterStatFloat(tCharacter, k2, v[k2])
                elseif type(v[k2]) == "string" then
                    CF_SetCharacterStatString(tCharacter, k2, v[k2])
                end
            end
        end
    end
    CombatScene_SetSceneReady()
    EventPipeline.emit("COMBAT_ON_MATCH_START")
end

CombatHandling_Fn[CombatIngameData.OnCharacterTurnStart] = function(data)
    print("Combat OnCharacterTurnStart detected " .. data)

    local tCharacter, pos, err = JSON_Decode(data)
    if err then
        print("Ke3 F3i117 exception (PacketChannel.Combat][CCombatResponse.Combat_IngameData]  JSON decode error:", err)
    end

    -- local tCharacter = CombatField_instance:getCharacter(tCharacter.characterID,tCharacter.side)
    if tCharacter == nil then
        return
    end
    local characterID = tCharacter.characterID
    local side = tCharacter.characterSide
    local cAction = tCharacter.currentAp
    local cHp = tCharacter.currentHp
    local cMana = tCharacter.currentMana

    print("character " .. characterID .. " turn start")
    print("side " .. side)
    print("cAction " .. cAction)
    print("cHp " .. cHp)
    print("cMana " .. cMana)
    
    EventPipeline.emit("TURNDISPLAYER_SetSelection" , {characterID = characterID, side = side})

end