# Touhou TB — Repo Overview

## What this project is
A turn-based online Touhou fangame with a custom C++ engine (Feitgine), a Lua scripting
layer, and a 3-app networked architecture. C++ handles the engine/runtime; Lua handles
game logic, packet handling, and UI scripting.

## The 3 core apps
| Folder | Role |
|---|---|
| `TB_Server/` | Main Server — accounts, user data, shop, formations, arena matchmaking |
| `BattleServer/` | Battle Server — lobbies, combat, turn order, match lifecycle |
| `Touhou_TB/` | Client — the actual game, SDL2 + OpenGL via Feitgine |

Each app has its own `CLAUDE.md` with full details. Open from inside the app folder
to get that context loaded automatically.

## Other folders
| Folder | Role |
|---|---|
| `Lua/` | Shared Lua across all apps — `system/` for engine-level, `TouhouTB/` for game logic |
| `Feitgine/` | Custom engine source |
| `FeitgineGC_deps/` | All third-party dependencies (headers + libs) |
| `TB_ServerInquiry/` | Admin tool — checks server stats, manages register keys |
| `Editor/` | Engine editor |
| `GC3/` | Separate Touhou game, not the turnbase one |

## Shared Lua conventions (applies to all apps)
- Nil guard every parsed packet field — log with `print("Ke3 F3i117 exception (...)")`
- Pipe-delimited parse pattern: `string.match(data, "^|([^|]+)|([^|]+)|$")`
- `LOG_INFO`, `LOG_WARN`, `LOG_COOKED(code, msg)` for logging
- JSON via `dkjson` — use `JSON_Encode` / `JSON_Decode` wrappers

## Compiler & build (all apps)
- **Toolchain:** Sysprogs MinGW32 — GCC 32-bit for Windows
- **Compiler:** `C:/SysGCC/mingw32/bin/i686-w64-mingw32-g++.exe`
- **Build:** `cmake .. -G "MinGW Makefiles"` then `mingw32-make`
- **Deps:** headers in `FeitgineGC_deps/include/`, libs in `FeitgineGC_deps/lib/`

## Characters implemented
Reimu, Patchouli, Meiling, Yukari (each with passive skills)
