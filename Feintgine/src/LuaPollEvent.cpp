#include "LuaPollEvent.h"


void LuaPollEvent::init(const std::string& scriptPath, lua_State* script)
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

void LuaPollEvent::update(float deltaTime)
{
    if (!m_script)
    {
        return;
    }

    // Same hasTasks guard as LuaTaskManager — skip the Lua call when queue is empty.
    lua_getglobal(m_script, "Poll_HasTasks");
    
    lua_call(m_script, 0, 1);
    bool hasTask = lua_toboolean(m_script, -1);
    lua_pop(m_script, 1);

    if (hasTask)
    {
        lua_getglobal(m_script, "Poll_Update");
        lua_pushnumber(m_script, deltaTime);
        lua_call(m_script, 1, 0);
    }
}
void LuaPollEvent::sendPollSignal(const std::string& signalName,bool value)
{
    if(!m_script)
    {
        return;
    }
    lua_getglobal(m_script, "Poll_SetSignal");
    lua_pushstring(m_script, signalName.c_str());
    lua_pushboolean(m_script, value);
    lua_call(m_script, 2, 0);

}