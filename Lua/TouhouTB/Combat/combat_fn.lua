package.path = package.path .. ';../../Lua/system/Networking/?.lua;' .. ';../../Lua/TouhouTB/?.lua;' .. ';../../Lua/TouhouTB/Lobby/?.lua;'

-- require "clientGlobal"
-- require "combat_global"
require "combat_stage_sequence"



-- CombatHandling_Fn[CombatIngameData.Sync] = function(data)

--     local tData , pos, err = JSON_Decode(data)

--     print("[CombatIngameData.Sync] data dump" .. data )
--     if err then
--         print("Ke3 F3i117 exception (PacketChannel.Combat][CCombatResponse.Combat_IngameData]  JSON decode error:", err)
--     end

--     print("Combat Sync get ")

--     local lobbyID = tData[1]
--     local p1Id = tData[2]
--     local p2Id = tData[3]
--     local p1Formation = tData[4]
--     local p2Formation = tData[5]


--     local p1FormationInfo, pos, err = JSON_Decode(p1Formation)
--     if err then
--         print("Ke3 F3i117 exception (PacketChannel.Combat][CCombatResponse.Combat_IngameData]  JSON decode error:", err)
--     end
--     local p2FormationInfo, pos, err = JSON_Decode(p2Formation)
--     if err then
--         print("Ke3 F3i117 exception (PacketChannel.Combat][CCombatResponse.Combat_IngameData]  JSON decode error:", err)
--     end


--     --  Reset Combat_Combat_Formations
--     for k in pairs (Combat_Formations) do
--         Combat_Formations[k] = nil
--     end

--     Combat_Formations[p1Id] = p1FormationInfo
--     Combat_Formations[p2Id] = p2FormationInfo

--     for k,v in pairs(p1FormationInfo) do
--         CombatField_instance:addCharacter(p1FormationInfo[k].stats.colPos, 
--         p1FormationInfo[k].stats.rowPos, 1, p1FormationInfo[k].stats.characterID,"" )

--         -- convert to number ( if not c++ parse will error)
--         v.stats.colPos = tonumber(v.stats.colPos)
--         v.stats.rowPos = tonumber(v.stats.rowPos)
--         -- local jsonData = JSON_Encode(v) -> old version 
--         local jsonData = JSON_Encode(v.stats) -- New K2
--         CombatField_instance:SetCharacterStats(p1FormationInfo[k].stats.characterID,1,jsonData)
--     end
--     for k ,v in pairs(p2FormationInfo) do
--         CombatField_instance:addCharacter(p2FormationInfo[k].stats.colPos, 
--         p2FormationInfo[k].stats.rowPos, 2, p2FormationInfo[k].stats.characterID,"" )

--         -- convert to number ( if not c++ parse will error)
--         v.stats.colPos = tonumber(v.stats.colPos)
--         v.stats.rowPos = tonumber(v.stats.rowPos)
--         -- local jsonData = JSON_Encode(v) -> old version 
--         local jsonData = JSON_Encode(v.stats) -- New K2
--         CombatField_instance:SetCharacterStats(p2FormationInfo[k].stats.characterID,2,jsonData)
--     end

--     for k,v in pairs(p1FormationInfo) do
--         local tCharacter = CombatField_instance:getCharacter(p1FormationInfo[k].stats.characterID,1)
--         print(p1FormationInfo[k].stats.characterID)
--         if tCharacter ~= nil then 
--             print("character " .. p1FormationInfo[k].stats.characterID .. " valid" )
--         end
--         for k2,v2 in pairs(v) do
--             if k2 ~= "colPos" and k2 ~= "rowPos" then
--                 if type(v[k2]) == "number" then
--                     CF_SetCharacterStatFloat(tCharacter, k2, v[k2])
--                 elseif type(v[k2]) == "string" then
--                     CF_SetCharacterStatString(tCharacter, k2, v[k2])
--                 end
--             end
--         end
--     end

--     print("p2 check")
--     for k,v in pairs(p2FormationInfo) do
--         print(p2FormationInfo[k].stats.characterID)
--         local tCharacter = CombatField_instance:getCharacter(p2FormationInfo[k].stats.characterID,2)
--         if tCharacter ~= nil then 
--             print("character " .. p2FormationInfo[k].stats.characterID .. " valid" )
--         end
--         for k2,v2 in pairs(v) do
--             if k2 ~= "colPos" and k2 ~= "rowPos" then
--                 if type(v[k2]) == "number" then
--                     CF_SetCharacterStatFloat(tCharacter, k2, v[k2])
--                 elseif type(v[k2]) == "string" then
--                     CF_SetCharacterStatString(tCharacter, k2, v[k2])
--                 end
--             end
--         end
--     end
--     CombatScene_SetSceneReady()
--     EventPipeline.emit("COMBAT_ON_MATCH_START")

--     CombatField_instance:FieldInfo_ListAll()


--     print("Dump Combat_Formations data")
--     for k,v in pairs(Combat_Formations) do
--         print(k .. ">" .. tostring(v))
--     end
-- end


local function dumpTable(t, indent)
    indent = indent or "\t"
    for k, v in pairs(t) do
        if type(v) == "table" then
            print(indent .. ">" .. tostring(k) .. " : (table)")
            dumpTable(v, indent .. "\t")
        else
            print(indent .. ">" .. tostring(k) .. " : " .. tostring(v))
        end
    end
end



--------------------------------------------------------------------------------
--  COMBAT SYNC HANDLER
--  Fired when the server sends the initial battle field sync packet.
--  Payload layout (tData): { lobbyID, p1Id, p2Id, p1FormationJSON, p2FormationJSON }
--  Each formation is an array of entries shaped like (New K2):
--      { stats = { ownerID, characterID, colPos, rowPos, <all combat stats> },
--        skills = { ... } }
--
--  Combat_Formations is nested by lobbyID so that concurrent lobbies
--  (spectator mode, multi-battle tracking, etc.) can't stomp each other's
--  cached formation data: Combat_Formations[lobbyID][playerID] = formationInfo
--------------------------------------------------------------------------------
CombatHandling_Fn[CombatIngameData.Sync] = function(data)

    -- outer packet: [lobbyID, p1Id, p2Id, p1FormationJSON, p2FormationJSON]
    local tData, pos, err = JSON_Decode(data)

    print("[CombatIngameData.Sync] data dump" .. data)
    if err then
        print("Ke3 F3i117 exception (PacketChannel.Combat][CCombatResponse.Combat_IngameData]  JSON decode error:", err)
    end

    print("Combat Sync get")

    local lobbyID      = tData[1]
    local p1Id         = tData[2]
    local p2Id         = tData[3]
    local p1Formation  = tData[4]
    local p2Formation  = tData[5]

    -- each formation field is itself a JSON string — decode separately
    local p1FormationInfo, p1pos, p1err = JSON_Decode(p1Formation)
    if p1err then
        print("Ke3 F3i117 exception (PacketChannel.Combat][CCombatResponse.Combat_IngameData]  JSON decode error:", p1err)
    end
    local p2FormationInfo, p2pos, p2err = JSON_Decode(p2Formation)
    if p2err then
        print("Ke3 F3i117 exception (PacketChannel.Combat][CCombatResponse.Combat_IngameData]  JSON decode error:", p2err)
    end

    -- reset cached formation lookup for THIS lobby only — wipe just this

    Combat_Formations = {}

    Combat_Formations[p1Id] = p1FormationInfo
    Combat_Formations[p2Id] = p2FormationInfo

    --------------------------------------------------------------------------
    -- PLAYER 1 FORMATION
    -- For each character: spawn it on the field, then push its full
    -- stat block down to C++ in one shot via SetCharacterStats.
    --------------------------------------------------------------------------
    for k, v in pairs(p1FormationInfo) do
        -- spawn the character at its slot (col/row/side) on the combat field
        CombatField_instance:addCharacter(v.stats.colPos,
            v.stats.rowPos, 1, v.stats.characterID, "")

        -- colPos/rowPos may arrive as strings from JSON — coerce to number
        -- or the C++-side parse will error
        v.stats.colPos = tonumber(v.stats.colPos)
        v.stats.rowPos = tonumber(v.stats.rowPos)

        -- (New K2) stats is now the full record (identity + position + stats)
        -- send it whole — SetCharacterStats/setStats() sets everything in one call
        local jsonData = JSON_Encode(v.stats)
        CombatField_instance:setCharacterStats(v.stats.characterID, 1, jsonData)
    end

    --------------------------------------------------------------------------
    -- PLAYER 2 FORMATION
    -- Same as above, mirrored for side 2.
    --------------------------------------------------------------------------
    for k, v in pairs(p2FormationInfo) do
        CombatField_instance:addCharacter(v.stats.colPos,
            v.stats.rowPos, 2, v.stats.characterID, "")

        v.stats.colPos = tonumber(v.stats.colPos)
        v.stats.rowPos = tonumber(v.stats.rowPos)

        local jsonData = JSON_Encode(v.stats)
        CombatField_instance:setCharacterStats(v.stats.characterID, 2, jsonData)
    end

    -- NOTE: no per-key CF_SetCharacterStatFloat/String pass needed anymore —
    -- under the (New K2) shape, SetCharacterStats already assigns the entire
    -- dCharacterStats struct in one call. The old post-pass loops were left
    -- over from before stats got nested and are now dead (v only contains
    -- `stats`/`skills` tables, so the number/string type checks never fire).
    -- Removed here; see chat history if you ever need to resurrect them.

    -- tell the scene the battle field is populated and ready
    CombatScene_SetSceneReady()
    EventPipeline.emit("COMBAT_ON_MATCH_START")

    CombatField_instance:FieldInfo_ListAll()

    print("Dump Combat_Formations data")

    for k, v in pairs(Combat_Formations) do
        print(k)
        for t, character in pairs(v) do
            print("character " .. t)
            print("stats : ")
            dumpTable(character.stats)
            print("skills : ")
            dumpTable(character.skills)
        end
    end

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