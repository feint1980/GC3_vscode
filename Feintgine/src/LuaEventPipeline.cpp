
#include "LuaEventPipeline.h"

// =============================================================================
//  LuaEventPipeline.cpp
//  Mirrors LuaTaskManager.cpp exactly — same bridge pattern, same hasTasks guard.
// =============================================================================

void LuaEventPipeline::init(const std::string& scriptPath, lua_State* script)
{
    m_script = script;
    if (LuaManager::Instance()->checkLua(m_script, luaL_dofile(m_script, scriptPath.c_str())))
    {
        std::cout << "Run script " << scriptPath << " OK \n";
    }
    else
    {
        std::cout << "Run script " << scriptPath << " failed \n";
        return;
    }
}

void LuaEventPipeline::update(float deltaTime)
{
    if (!m_script)
    {
        return;
    }

    // Same hasTasks guard as LuaTaskManager — skip the Lua call when queue is empty.
    lua_getglobal(m_script, "EventPipeline_hasTasks");
    lua_call(m_script, 0, 1);
    bool hasTask = lua_toboolean(m_script, -1);
    lua_pop(m_script, 1);

    if (hasTask)
    {
        lua_getglobal(m_script, "EventPipeline_update");
        lua_pushnumber(m_script, deltaTime);
        lua_call(m_script, 1, 0);
    }
}
