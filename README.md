# My Game Development Projects

🚀 Welcome to my GitHub! Here, you'll find projects showcasing my expertise in **C++, game engines, networking, and tooling for game development.**

## 🔥 Projects Overview

### 🎮 Custom 2D Game Engine (C++, SDL2, OpenGL, Lua, Protobuf, CEGUI, TGUI)
- Built from using SDL2, OpenGL to support **2D games** with real-time rendering and physics.
- Features a **Lua scripting system** for game logic.

### 🛠 Game Editor (Built using my engine)
- **2D Top-down Map Builder**: Create RPG-style maps with **custom objects and lighting**.
- **Sprite Animation Editor**: Design and preview **frame-based animations**.
- **Arc Calculator**: Useful for **Touhou-like projectile patterns**.
- **Enemy/Boss Editor**: Customize enemy behaviors and attack patterns.

### 🔥 Touhou-like Game (Built using my engine)
- **All core gameplay systems are implemented**, including movement, projectiles, and spell cards.
- **Content is still in development**.

### ⚔ Turn-Based Multiplayer Game (Prototype) (C++, RakNet, SQLite3)
- **Login & Account System** ✅
- **Basic movement, skills, animations, and hit calculations** (not yet fully playable).

### 🌐 Multiplayer Game Server (C++, RakNet, SQLite3, mbedTLS)
- **Manages player accounts** with secure login/register.
- **Encrypts & decrypts messages** between client and server using **mbedTLS** for security.

---

## 🛠 Tech Stack & Tools
- **Languages**: C++, Lua, SQL
- **Game Dev**: SDL2, OpenGL, RakNet, Protobuf
- **Networking & Security**: **mbedTLS** (for message encryption/decryption)
- **Tools**: CEGUI, TGUI, Visual Studio Code, MinGW-w64
- **Database**: SQLite3

---

## ⚙ Build Instructions
### **Prerequisites**
- Install **CMake** .
- Install **MinGW-w32** (https://gnutoolchains.com/mingw32/) Please select this specific compiler as I already use in my development, the other dependencies was compiled in this compiler too so it would save you time

### **Building the Project (Use Powershell)**
```sh
# Clone the repository
git clone https://github.com/feint1980/GC3_vscode.git
cd GC_vscode

#Build the engine (you must build this first to build other application) 
cd Feintgine/build/
cmake -G "MinGW Makefiles" ..
mingw32-make.exe -j 4

#Build the Editor 
cd ../../
cd Editor/build/
cmake -G "MinGW Makefiles" ..
mingw32-make.exe -j 4

#Build the Touhou game
cd ../../
cd GC3/build/
cmake -G "MinGW Makefiles" ..
mingw32-make.exe -j 4

#Build the Touhou turnbase game
cd ../../
cd Touhou_TB/build/
cmake -G "MinGW Makefiles" ..
mingw32-make.exe -j 4


#Build the Server for turnbase game
cd ../../
cd TB_Server/build/
cmake -G "MinGW Makefiles" ..
mingw32-make.exe -j 4
```
## Note
For the Editor and Game that you want to see but don't have time to build : 

[![YouTube](https://img.shields.io/badge/YouTube-FF0000?style=for-the-badge&logo=youtube&logoColor=white)](https://www.youtube.com/watch?v=HkZZ71s609o)
