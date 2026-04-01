
#pragma once
#include "LuaManager.h"
#include <iostream>

// =============================================================================
//  LuaEventPipeline.h
//  C++ bridge for BS_EventPipeline.lua.
//  Drop-in alongside LuaTaskManager — identical interface, same usage pattern.
// =============================================================================

class LuaEventPipeline
{
public:
    LuaEventPipeline()  {}
    ~LuaEventPipeline() {}

    // Load BS_EventPipeline.lua into the given lua_State.
    // Call once at scene/match init, same as LuaTaskManager::init().
    void init(const std::string& scriptPath, lua_State* script);

    // Call every frame from your game loop, same as LuaTaskManager::update().
    // Skips the Lua call entirely when no tasks are queued (zero idle overhead).
    void update(float deltaTime);

    void sendSignal(const std::string& signalName);

    void sendPollSignal(const std::string& signalName,bool value);

private:
    lua_State* m_script = nullptr;
};
