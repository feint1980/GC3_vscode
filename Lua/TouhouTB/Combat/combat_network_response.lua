package.path = package.path .. ';../../Lua/system/Networking/?.lua;' .. ';../../Lua/TouhouTB/?.lua;' .. ';../../Lua/TouhouTB/Lobby/?.lua;'

require "clientGlobal"

-- AnimationPathMap = {

--     ["S_Reimu"] = "./Assets/F_AObjects/reimu_tb.xml",
--     ["S_Meiling"] = "./Assets/F_AObjects/meiling_tb.xml",
--     ["S_Yukari"] = "./Assets/F_AObjects/yukari_tb.xml",
--     ["S_Patchouli"] = "./Assets/F_AObjects/patchouli_tb.xml",

-- }

CombatHandling_Fn = {}



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

    -- CombatField_instance:addCharacter


    CombatScene_SetSceneReady()

end

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

