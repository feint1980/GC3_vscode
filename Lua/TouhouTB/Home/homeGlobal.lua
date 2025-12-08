MenuPanels = {}

---@class S_Characters_Info
---@field data string
---@field isOwned boolean
Characters_Info = {
    data = "",
    isOwned  = false
}

function Characters_Info:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function Characters_Info:init(tData, tIsOwned)
    self.data = tData
    self.isOwned = tIsOwned
end

S_Characters_Info = {}
Shop_CharacterTable = {}

Owned_CharacterTable = {}
Owned_CharacterPannels = {}

Formation_Table = {}
Formation_OwnedCharacterPannels = {}

Skill_Serialized_Table = {}
Skill_Table = {}

---@table of Prompt
Prompt_UI_Table = {}

MainInfo = {
    id = "",
    guid = "",
    pw = ""
}

--- Arena Server

Arena_Ping_List = {

}

ArenaServer = {
    clientHost = nil,
    guid = "",
    name = "",
    port = 0,
    ping = 0,
    IP = nil,
}

function ArenaServer:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function ArenaServer:init(tClientHost,tGuid, tName, tPort, tPing, tIP)
    self.clientHost = tClientHost
    self.guid = tGuid
    self.name = tName
    self.port = tPort
    self.ping = tPing
    self.IP = tIP
end

function ArenaServer:setPing(ping)
    self.ping = ping
end
