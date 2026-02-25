package.path = package.path .. ';../../Lua/system/Networking/?.lua;' .. ';../../Lua/TouhouTB/?.lua;' .. ';../../Lua/TouhouTB/Lobby/?.lua;'
require "clientWrapper"
require "clientGlobal"

Combat_HandleNetwork = {}

CombatMessageHandling = {}

CombatBattleHandling = {}

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