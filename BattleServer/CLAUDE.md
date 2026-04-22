# BattleServer — Battle Server

## Role
Handles lobbies, combat, turn order, and match lifecycle.
Registers itself to the Main Server on startup via the PaperWork channel.
Clients connect here directly for combat after matchmaking via Main Server.

## Folder structure
```
BattleServer/
├── src/          # C++ source
├── luaFiles/
│   └── Characters/   # Per-character combat logic
└── build/
```

## Key Lua files
- `luaFiles/battleWrapper.lua` — all BS send/receive wrappers, packet tables
- `luaFiles/BS_lobbiesHandler.lua` — lobby creation, joining, match start

## Packet types (RakNet message IDs)
```lua
BattlePacketType = {
    ID_TH_TB = 135,         -- client → main server
    ID_TH_TB_BATTLE = 136,  -- client → battle server
    ID_TH_INTERNAL = 137,   -- main server → battle server
}
```

## Channels — BS side (for MS↔BS communication)
```lua
MainServerChanel = {
    PaperWork = 1,      -- self-registration handshake with MS
    ClientRequest = 2,
    Combat = 3,
    Lobby = 4,
    ClientData = 5,
}
```
⚠️ Must stay in sync with `BattleChanel` in `serverWrapper.lua`

## Channels — client side (for Client↔BS communication)
```lua
ClientChannel = {
    InfoChannel = 1,
    Lobby = 2,
    Combat = 3,
}
```
⚠️ Must stay in sync with `BattlePacketChannel` in `clientWrapper.lua`

## Response tables
```lua
CLobbyResponse      -- lobby join, sync, formations, match start
CCombatResponse     -- ready status, ingame data, turn order
CombatIngameData    -- sync, match start, character turn start
CombatTurnOrder     -- sync, roll result, speed affect, update order, player turn
LobbyResponse       -- MS-side lobby create/join
ClientDataResponse  -- formation and owned character data requests
```

## Send function
```lua
-- Primary send from BS to anywhere:
BM_sendWrapData(host, targetIP, guid, id, channel, request, list)
-- id = BattlePacketType.ID_TH_TB_BATTLE for client
-- id = BattlePacketType.ID_TH_INTERNAL for main server
```

## Handler registration pattern
```lua
-- Handlers for messages FROM clients:
ClientChannel_Handler[ClientChannel.Lobby][CLobbyResponse.SomeThing] = function(host, packet)
end

-- Handlers for messages FROM main server:
MainServerHandler[MainServerChanel.PaperWork][PaperWorkRequest.SomeThing] = function(host, packet)
end
```

## Lobby system
- `BM_CreateLobby(host, lobbyName, lobbyPassword)` — returns lobbyID
- `BM_JoinLobby(host, clientGUID, clientID, lobbyID, ip)` — returns boolean
- `BM_addToWhitelist(guid, id)` — whitelist client before they connect
- `BM_removeFromWhitelist_ByGUID(guid)`

## Session management
- `BM_addClientOnlineSession(guid, id, ip)` — register connected client
- `BM_getClientOnlineSessionByGUID(guid)` — look up session

## Rules
- Never reuse or skip packet ID integers
- BS must self-register to MS on startup via `PaperWork.SelfRegister` before handling any client traffic
- Whitelist clients before they're allowed to join a lobby
