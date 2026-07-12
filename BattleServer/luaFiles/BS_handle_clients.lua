package.path = package.path .. ";../luaFiles/?.lua" 

require "battleWrapper"
require "BS_global"

---@class BattleClientEP
---@field id string
---@field guid string
---@field ip? pointer instance of RakNet::SystemAddress
---@field index number
---@field readyState boolean
---@field selected_formation_index number
---@field lobbyID string
BattleClientEP = {}
BattleClientEP.__index = BattleClientEP

function BattleClientEP:new()
    local o = setmetatable({}, self)
    o.id = ""
    o.guid = ""
    o.ip = nil
    o.index = 1
    o.readyState = false
    o.selected_formation_index = -1
    o.lobbyID = ""
    self.__index = self
    return o
end

function BattleClientEP:init(id, guid, ip,tIndex)
    self.id = id
    self.guid = guid
    self.ip = ip
    self.index = tIndex
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
