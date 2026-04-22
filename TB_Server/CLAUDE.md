# TB_Server — Main Server

## Role
Handles accounts, user data, shop, formations, arena matchmaking.
Communicates with Clients AND with Battle Servers.

## Folder structure
```
TB_Server/
├── src/          # C++ source
├── luaFiles/
│   ├── BattleServer/   # Lua handlers for BS↔MS communication
│   ├── Client/         # Lua handlers for client requests
│   │   └── Skills/     # Per-character skill handlers
│   ├── Characters/
│   ├── Buffs/
│   └── Skills/
│       ├── S_Meiling/
│       ├── S_Patchouli/
│       ├── S_Reimu/
│       └── S_Yukari/
├── data/         # SQLite3 DB files
├── manual/
└── build/
```

## Key Lua files
- `../../Lua/system/Networking/serverWrapper.lua` — all send/receive wrappers, packet channel tables
- `luaFiles/Client/accountHandle.lua` — login, register, key request handlers

## Packet channels (Main Server side)
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
⚠️ Must stay in sync with `clientWrapper.lua` in `Lua/system/Networking/`

## Battle Server channels (MS↔BS)
```lua
BattleChanel = {
    PaperWork = 1,   -- BS self-registration
    ClientRequest = 2,
    Combat = 3,
    Lobby = 4,
    ClientData = 5,
}
```
⚠️ Must stay in sync with `MainServerChanel` in `battleWrapper.lua`

## Handler registration pattern
```lua
MessageHandling[PacketChannel.SomeChannel][SomeResponse.SomeThing] = function(host, data, ip, guid)
    local field1, field2 = string.match(data, "^|([^|]+)|([^|]+)|$")
    if field1 == nil then
        print("Ke3 F3i117 exception (PacketChannel.SomeChannel][SomeResponse.SomeThing)")
        return
    end
    -- logic here
    SendReliable(host, ip, guid, PacketChannel.SomeChannel, SomeResponse.SomeThing, { result })
end
```

## Send functions
- `SendReliable(host, ip, guid, channel, request, tList)` — to client, retries up to 5x
- `SendReliable2BattleServer(host, ip, guid, channel, request, tList)` — to BS, retries up to 5x
- `SV_SendWrapMsg(host, ip, guid, channel, request, list)` — raw send to client
- `SV_SendWrapMsg2BattleServer(host, ip, guid, channel, request, list)` — raw send to BS

## DB access pattern
```lua
local result = SVI_DoQuerySTMT(host, "SELECT col FROM table WHERE id = ?;", { id })
local value = result[1]
```

## Rules
- Never reuse or skip packet ID integers — always next sequential value
- Always nil-check parsed fields before using them
- `SendReliable` over `SV_SendWrapMsg` for anything important — it retries
