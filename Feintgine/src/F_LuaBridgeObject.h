
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
#include <glm/glm.hpp>  

#include "F_LuaObject.h"


// prefer link : 
// https://www.youtube.com/watch?v=mtjCgqyZ5wk

// https://www.youtube.com/watch?v=-E_L6-Yo8yQ


namespace Feintgine
{
    class F_LuaBridgeObject
    {
    public:

        F_LuaBridgeObject();
        ~F_LuaBridgeObject();

        void init();

        void test();

        void addObject(const std::string & tableName);
        void readFile(const std::string & filePath);

        void draw(Feintgine::SpriteBatch & spriteBatch);
        void update(float deltaTime);

        private:
        
        lua_State * m_LuaState = nullptr;

        std::vector<F_LuaObject> m_luaObjects; // decide to use pointer or not


    };

}

#endif