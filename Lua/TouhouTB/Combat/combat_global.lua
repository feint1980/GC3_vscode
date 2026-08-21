package.path = package.path .. ';../../Lua/system/Networking/?.lua;' .. ';../../Lua/TouhouTB/?.lua;' .. ';../../Lua/TouhouTB/Lobby/?.lua;'
require "clientGlobal"
require "clientWrapper"

-- control State | 
-- it has Level 
-- 1 . select characters 
-- 2 . select skill 
-- 3 . select target 

Combat_Control_StateValue = {
    SELECT_CHARACTER = 1,
    SELECT_SKILL = 2,
    SELECT_TARGET = 3
}

Combat_Control_State = Combat_Control_StateValue.SELECT_CHARACTER

Combat_HandleNetwork = {}

CombatMessageHandling = {}

CombatBattleHandling = {}

CombatHandling_Fn = {}

TurnOrderHandling_Fn = {}



for k,v in pairs(PacketChannel) do
    -- print(k,v)
    CombatMessageHandling[v] = {}
end

function CombatHandlerWrapResponse(host,chanel,request, data,guid)
    print("CombatHandlerWrapResponse called" )

    if CombatMessageHandling[chanel][request] ~= nil then
        CombatMessageHandling[chanel][request](host,data,guid)
    end
end

for k,v in pairs(BattlePacketChannel) do
    -- print(k,v)
    CombatBattleHandling[v] = {}
end

function CombatHandlerBattleResponse(host,chanel,request, data,guid)
    print("CombatBattleHandling called" .. chanel .. " " .. request)
    if  CombatBattleHandling[chanel] == nil then
        print("channel not found " .. chanel)
        return
    end
    if CombatBattleHandling[chanel][request] ~= nil then
        CombatBattleHandling[chanel][request](host,data,guid)
    end
end

require "combat_network"