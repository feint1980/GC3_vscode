
#ifndef F_LUA_BRIDGE_OBJECT_H
#define F_LUA_BRIDGE_OBJECT_H


extern "C"
{
#include <lua.h>
#include <lauxlib.h> 
#include <lualib.h>
}
#ifdef _WIN32
#pragma comment(lib, "lua.a")
#endif
//#include <Lua/LuaLibrary.h>
#include <LuaBridge/LuaBridge.h>

// prefer link : 
// https://www.youtube.com/watch?v=mtjCgqyZ5wk

// https://www.youtube.com/watch?v=-E_L6-Yo8yQ

class F_LuaBridgeObject
{
public:

    F_LuaBridgeObject();
    ~F_LuaBridgeObject();

    void init();

    private:
    int m_id;
    lua_State * m_LuaState = nullptr;


};



#endif