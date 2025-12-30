LobbyEPState =
{
    LOBBY_STATE_OPEN = 0,
    LOBBY_STATE_CLOSED = 1,
    LOBBY_STATE_IN_GAME = 2
}

LobbyEP =
{
    id = "",
    name = "",
    password = "",
    state = LobbyEPState.LOBBY_STATE_CLOSED
}

function LobbyEP:new (o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function LobbyEP:init(id, name, password)
    print("Lua LobbyEP init")
    self.id = id
    self.name = name
    self.password = password
    self.state = LobbyEPState.LOBBY_STATE_OPEN
end