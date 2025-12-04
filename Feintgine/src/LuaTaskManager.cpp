
#include "LuaTaskManager.h"


void LuaTaskManager::init(const std::string & scriptPath,lua_State * script)
{

    m_script = script;
    if(LuaManager::Instance()->checkLua(m_script, luaL_dofile(m_script, scriptPath.c_str())))
    {
        std::cout << "Run script " << scriptPath << " OK \n";
    }
    else
    {
        std::cout << "Run script " << scriptPath << " failed \n";
        return;
    }

}

void LuaTaskManager::update(float deltaTime)
{
    if(!m_script)
    {
        return;
    }

    lua_getglobal(m_script,"TaskManager_hasTasks");
    lua_call(m_script,0,1);

    bool hasTask = lua_toboolean(m_script,-1);
    lua_pop(m_script,1);
    if(hasTask)
    {

        lua_getglobal(m_script,"TaskManager_update");
        lua_pushnumber(m_script,deltaTime);
        lua_call(m_script,1,0);
        // lua_pop(m_script,1);

        // int top = lua_gettop(m_script);
        // std::cout << "top : " << top << "\n";
        // if(top > 0)
        // {
        //     lua_pop(m_script,top);
        // }
        
    }
    else
    {
        // std::cout << "no task \n";
    }

}
