package.path = package.path .. ";../luaFiles/?.lua" 

require "battleWrapper"
require "BS_global"

BattleClientEP =
{
    id = "",
    guid = "",
    ip = nil,
    readyState = false,
    selected_formation_index = -1,
    lobbyID = "",
}

function BattleClientEP:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function BattleClientEP:init(id, guid, ip)
    self.id = id
    self.guid = guid
    self.ip = ip
    --- register ip in C++ here 
    BM_addClientOnlineSession(guid, id,ip)
    self.readyState = false
    self.selected_formation_index = -1
end

function BattleClientEP:getIP()
    return BM_getClientOnlineSessionByGUID(self.guid)
end

function BattleClientEP:setReady(value)
    self.readyState = value
end

function BattleClientEP:joinLobby(lobbyID)
    self.lobbyID = lobbyID
end
