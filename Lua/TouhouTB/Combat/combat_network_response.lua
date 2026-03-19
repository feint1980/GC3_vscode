package.path = package.path .. ';../../Lua/system/Networking/?.lua;' .. ';../../Lua/TouhouTB/?.lua;' .. ';../../Lua/TouhouTB/Lobby/?.lua;'

require "clientGlobal"

-- AnimationPathMap = {

--     ["S_Reimu"] = "./Assets/F_AObjects/reimu_tb.xml",
--     ["S_Meiling"] = "./Assets/F_AObjects/meiling_tb.xml",
--     ["S_Yukari"] = "./Assets/F_AObjects/yukari_tb.xml",
--     ["S_Patchouli"] = "./Assets/F_AObjects/patchouli_tb.xml",

-- }

CombatBattleHandling[BattlePacketChannel.Combat][CCombatResponse.Combat_Match_Start] = function(host,data,guid)

    print("Combat_Match_Start detected from " .. guid)

    -- print(data)

    local lobbyID, p1Id, p2Id, p1Formation, p2Formation = string.match(data, "^|([^|]+)|([^|]+)|([^|]+)|([^|]+)|([^|]+)|$")

    print("lobbyID " .. lobbyID)
    print("p1Id " .. p1Id)
    print("p2Id " .. p2Id)
    -- print("p1Formation " .. p1Formation)
    -- print("p2Formation " .. p2Formation)

    local p1FormationInfo, pos, err = JSON_Decode(p1Formation)
    if err then
        print("Ke3 F3i117 exception (PacketChannel.Combat][CCombatResponse.Combat_Match_Start]  JSON decode error:", err)
    end
    local p2FormationInfo, pos, err = JSON_Decode(p2Formation)
    if err then
        print("Ke3 F3i117 exception (PacketChannel.Combat][CCombatResponse.Combat_Match_Start]  JSON decode error:", err)
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

    -- CombatField_instance:addCharacter


    CombatScene_SetSceneReady()

end