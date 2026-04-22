# Touhou_TB — Client

## Role
The actual game. Connects to Main Server for account/data ops, then directly to
Battle Server for combat. Built on Feitgine (custom SDL2 + OpenGL engine).

## Folder structure
```
Touhou_TB/
├── src/          # C++ source (engine integration, entry point)
└── build/
    ├── Assets/
    │   └── LuaFiles/
    │       └── common/
    ├── Shaders/
    ├── font/
    └── themes/   # TGUI themes
```

## Game Lua structure (lives in Lua/TouhouTB/)
```
Lua/TouhouTB/
├── Login/            # Login screen logic
├── Home/
│   └── Shop/         # Shop screen
├── Lobby/            # Pre-match lobby
├── Combat/
│   └── UI/           # Combat HUD
├── characters/       # Per-character logic
│   ├── Common/
│   ├── Reimu/
│   ├── Patchouli/  (Patchy)
│   ├── Meiling/
│   └── Yukari/
├── skills/           # Skill definitions
├── slots/            # Slot system
├── Icons/
└── data/
```

## Key Lua files
- `../../Lua/system/Networking/clientWrapper.lua` — all client send/receive wrappers

## Packet channels — Main Server
```lua
PacketChannel = {
    AccountChannel = 1,
    UserChannel = 2,
    ShopChannel = 3,
    TransactionChannel = 4,
    FormationChannel = 5,
    ArenaChannel = 6
}
```
⚠️ Must stay in sync with `serverWrapper.lua` in TB_Server

## Packet channels — Battle Server
```lua
BattlePacketChannel = {
    InfoChannel = 1,
    Lobby = 2,
    Combat = 3,
}
```
⚠️ Must stay in sync with `ClientChannel` in `battleWrapper.lua`

## Handler registration pattern
```lua
-- Responses from Main Server:
ClientMessageHandling[PacketChannel.SomeChannel][SomeResponse.SomeThing] = function(host, data)
    local field1 = string.match(data, "^|([^|]+)|$")
    -- update game state
end

-- Responses from Battle Server:
ClientBattleHandling[BattlePacketChannel.SomeChannel][SomeResponse.SomeThing] = function(host, data)
    -- update combat state
end
```

## Send functions
```lua
-- To Main Server:
WrapRequest(PacketChannel.SomeChannel, SomeResponse.SomeThing, { field1, field2 })

-- To Battle Server:
WrapRequest(BattlePacketChannel.SomeChannel, SomeResponse.SomeThing, { field1 })
```

## Connection flow
1. Connect to Main Server → login/register
2. Request arena server list from Main Server (`ArenaChannel`)
3. Connect to chosen Battle Server directly (`ClientConnectToBattleServer`)
4. Join lobby → sync formations → match start → combat

## Utility functions
- `ClientGetGUID(host)` — get own GUID
- `ClientGetPing(host)` — get ping to current server
- `ClientConnectToBattleServer(host, guid)` — connect to BS by GUID
- `ClientDisconnectFromCurrentBattleServer(host)`
- `Client_AddCryptor(host, key)` / `Client_RemoveCryptor(host, key)`

## Rules
- Never reuse or skip packet ID integers
- Always nil-check parsed fields from server responses
- `ClientMessageHandling` for MS responses, `ClientBattleHandling` for BS responses — don't mix them
