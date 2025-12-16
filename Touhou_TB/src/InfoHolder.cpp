#include "InfoHolder.h"

InfoHolder *InfoHolder::m_inforHolder = 0;


int lua_infoHolder_setStrValue(lua_State * L) 
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "lua_storeStrValue bad gettop " << lua_gettop(L) << " \n";
        return -1;
    }
    else
    {
        std::string key = lua_tostring(L, 1);
        std::string value = lua_tostring(L, 2);
        InfoHolder::getInstance()->saveStrValue(key, value);
    }
    return 0;
}

int lua_infoHolder_getStrValue(lua_State * L)
{
    if(lua_gettop(L) != 1)
    {
        std::cout << "lua_getStrValue bad gettop " << lua_gettop(L) << " \n";
        return -1;
    }
    else
    {
        std::string key = lua_tostring(L, 1);
        std::string value = InfoHolder::getInstance()->getStrValue(key);
        lua_pushstring(L, value.c_str());
        return 1;
    }
    return 0;
}

int lua_infoHolder_setNumberValue(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "lua_storeNumberValue bad gettop " << lua_gettop(L) << " \n";
        return -1;
    }
    else
    {
        std::string key = lua_tostring(L, 1);
        int value = lua_tonumber(L, 2);
        InfoHolder::getInstance()->saveNumberValue(key, value);
    }
    return 0;
}

int lua_infoHolder_getNumberValue(lua_State * L)
{
    if(lua_gettop(L) != 1)
    {
        std::cout << "lua_getNumberValue bad gettop " << lua_gettop(L) << " \n";
        return -1;
    }
    else
    {
        std::string key = lua_tostring(L, 1);
        int value = InfoHolder::getInstance()->getNumberValue(key);
        lua_pushnumber(L, value);
        return 1;
    }
    return 0;
}

int lua_infoHolder_setUserLightData(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "lua_storeUserLightData bad gettop " << lua_gettop(L) << " \n";
        return -1;
    }
    else
    {
        std::string key = lua_tostring(L, 1);
        void *  value = lua_touserdata(L, 2);
        InfoHolder::getInstance()->setUserLightData(key, value);
        
    }
    return 0;
}

int lua_infoHolder_getUserLightData(lua_State * L)
{
    if(lua_gettop(L) != 1)
    {
        std::cout << "lua_getUserLightData bad gettop " << lua_gettop(L) << " \n";
        return -1;
    }
    else
    {
        std::string key = lua_tostring(L, 1);
        void * value = InfoHolder::getInstance()->getUserLightData(key);
        lua_pushlightuserdata(L, value);
        return 1;
    }
    return 0;
}

void InfoHolder::initLuaInterface(lua_State * script)
{
    m_script = script;
    lua_register(m_script, "cpp_infoHolder_setStrValue", lua_infoHolder_setStrValue);
    lua_register(m_script, "cpp_infoHolder_getStrValue", lua_infoHolder_getStrValue);
    lua_register(m_script, "cpp_infoHolder_setNumberValue", lua_infoHolder_setNumberValue);
    lua_register(m_script, "cpp_infoHolder_getNumberValue", lua_infoHolder_getNumberValue);
    lua_register(m_script, "cpp_infoHolder_setUserLightData", lua_infoHolder_setUserLightData);
    lua_register(m_script, "cpp_infoHolder_getUserLightData", lua_infoHolder_getUserLightData);

    
}