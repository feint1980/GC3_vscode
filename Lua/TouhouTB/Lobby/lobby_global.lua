package.path = package.path .. ';../../Lua/system/Networking/?.lua;' .. ';../../Lua/TouhouTB/?.lua;' .. ';../../Lua/TouhouTB/Lobby/?.lua;'
require "clientWrapper"
require "clientGlobal"

LobbyMenuPanels = {}

Lobby_HandleNetwork = {}

LobbyMessageHandling = {}

LobbyBattleHandling = {}


Lobby_Formations_Info = {}
Lobby_Formation_Display = {}
Lobby_Fomration_CurrentPage = 1
Lobby_Fomration_MaxPage = 1

Lobby_Formation_FilterEdit = nil


for k,v in pairs(PacketChannel) do
    -- print(k,v)
    LobbyMessageHandling[v] = {}
end

function LobbyHandlerWrapResponse(host,chanel,request, data,guid)
    print("LobbyHandlerWrapResponse called" )

    if LobbyMessageHandling[chanel][request] ~= nil then
        LobbyMessageHandling[chanel][request](host,data,guid)
    end
end


for k,v in pairs(BattlePacketChannel) do

    print("init function for channel (BattlePacketChannel) " .. v)
    LobbyBattleHandling[v] = {}
end

function LobbyHandlerBattleResponse(host,chanel,request, data,guid)
    print("LobbyBattleHandling called" .. chanel .. " " .. request)
    if  LobbyBattleHandling[chanel] == nil then
        print("channel not found " .. chanel)
        return
    end
    if LobbyBattleHandling[chanel][request] ~= nil then
        LobbyBattleHandling[chanel][request](host,data,guid)
    end
end

require "lobby_client_network"


