#include "LuaEventHandler.h"
static bool LuaHandler_isCounting = false;
int lua_EventHandlerStart(lua_State * L)
{
    std::cout << "[C++] lua_EventHandlerStart called \n";
    if(lua_gettop(L) != 0)
    {   
        std::cout << "gettop failed (lua_EventHandlerStart) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        std::cout << "[C++] lua_EventHandlerStart pass \n";
        
        LuaHandler_isCounting = true;
        
        return 0;
    }
}

int lua_EventHandlerStop(lua_State * L)
{
    if(lua_gettop(L) != 0)
    {   
        std::cout << "gettop failed (lua_EventHandlerStop) " << lua_gettop(L) << "\n";
        return -1;
    }
    else
    {
        LuaHandler_isCounting = false;
        return 0;
    }
}

LuaEventHandler::LuaEventHandler()
{
    // m_accumulator =f;
    // LuaHandler_isCounting = true;
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

    if(LuaManager::Instance()->checkLua(m_script, luaL_dofile(m_script, "../../Lua/system/event/LuaEventHandler.lua")))    
    {
        std::cout << "Run script LuaEventHandler OK \n";
    
    }

    lua_getglobal(m_script, "InitEventHandler");
    if(lua_isfunction(m_script, -1))
    {
        lua_pushlightuserdata(m_script, this);
        // std::cout << "ref is " << this << "\n";
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
    // std::cout << "delta " << deltaTime << "\n";
    if(LuaHandler_isCounting)
    {
        m_accumulator += deltaTime;
        if(m_accumulator >= 0.25f)
        {
            // m_time += m_accumulator;
            
            lua_getglobal(m_script, "EventHandlerUpdate");
            if(lua_isfunction(m_script, -1))
            {
                // lua_pushlightuserdata(m_script, this);
                lua_pushnumber(m_script, m_accumulator);
                const int argc = 1;
                const int returnCount = 0;
                if(LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, argc, returnCount, 0)))
                {
                    // std::cout << "EventHandlerUpdate " << m_time << " OK \n";
                }
            }
            m_accumulator = 0.0f;
        }
    }
}

void LuaEventHandler::startCounting()
{
    LuaHandler_isCounting = true;
}

void LuaEventHandler::stopCounting()
{
    LuaHandler_isCounting = false;
    m_time = 0;
}
