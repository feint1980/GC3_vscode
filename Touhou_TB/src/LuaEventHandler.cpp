#include "LuaEventHandler.h"

int lua_EventHandlerStart(lua_State * L)
{
    if(lua_gettop(L) != 1)
    {   
        std::cout << "gettop failed (lua_EventHandlerStart) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        LuaEventHandler * eventHandler = static_cast<LuaEventHandler*>(lua_touserdata(L, 1));
        eventHandler->startCounting();
        return 0;
    }
}

int lua_EventHandlerStop(lua_State * L)
{
    if(lua_gettop(L) != 1)
    {   
        std::cout << "gettop failed (lua_EventHandlerStop) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        LuaEventHandler * eventHandler = static_cast<LuaEventHandler*>(lua_touserdata(L, 1));
        eventHandler->stopCounting();
        return 0;
    }
}

LuaEventHandler::LuaEventHandler()
{
    // m_accumulator =f;
}

LuaEventHandler::~LuaEventHandler()
{

}


void LuaEventHandler::init(lua_State * script)
{
    if(script == nullptr)
    {
        std::cout << "(LuaEventHandler::init) attemp to init script \n";
        return;
    }
    m_script = script;

    if(LuaManager::Instance()->checkLua(m_script, luaL_dofile(m_script, "./Assets/Lua/system/event/LuaEventHandler.lua")))    
    {
        std::cout << "Run script LuaEventHandler OK \n";
    }


    lua_getglobal(m_script, "InitHandler");
    if(lua_isfunction(m_script, -1))
    {
        lua_pushlightuserdata(m_script, this);
        const int argc = 1;
        const int returnCount = 0;
        if(LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, argc, returnCount, 0)))
        {
            std::cout << "InitHandler from C++ OK \n";
        }
    }

    lua_register(m_script, "cppEventHandlerStart", lua_EventHandlerStart);
    lua_register(m_script, "cppEventHandlerStop", lua_EventHandlerStop);

}

void LuaEventHandler::update(float deltaTime)
{
    if(m_isCounting)
    {
        m_accumulator += deltaTime;
        if(m_accumulator >= 0.25f)
        {
            m_accumulator = 0.0f;
            m_time += m_accumulator;
            lua_getglobal(m_script, "EventHandlerUpdate");
            if(lua_isfunction(m_script, -1))
            {
                // lua_pushlightuserdata(m_script, this);
                lua_pushnumber(m_script, m_time);
                const int argc = 1;
                const int returnCount = 0;
                if(LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, argc, returnCount, 0)))
                {
                    std::cout << "EventHandlerUpdate " << m_time << " OK \n";
                }
            }
        }

    }
}

void LuaEventHandler::startCounting()
{
    m_isCounting = true;
  
}


void LuaEventHandler::stopCounting()
{
    m_isCounting = false;
    m_time = 0;
}
