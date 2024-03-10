
#include "F_LuaBridgeObject.h"

F_LuaBridgeObject::F_LuaBridgeObject()
{

}


F_LuaBridgeObject::~F_LuaBridgeObject()
{

}


int davai(int x)
{
    return x * 2;
}

void F_LuaBridgeObject::init()
{

    std::cout << "init lua \n";
    m_LuaState = luaL_newstate();
    luaL_openlibs(m_LuaState);
    luaopen_base(m_LuaState);

    // Test 
    luabridge::getGlobalNamespace(m_LuaState)
    .beginNamespace("test")
    .addFunction ("davai", +[] (int x) { return x * 3; })
    .endNamespace();

    // std::string cmd = "print(\"Hello world \")";

    std::cout << "reading file \n";

    // int resultDostring = luaL_dostring(m_LuaState, cmd.c_str());


    // if(resultDostring != LUA_OK)
    // {
    //     std::cout << lua_tostring(m_LuaState, -1) << "\n";
    //     return;
    // }

    int resultDofile = luaL_dofile(m_LuaState, "Assets/Lua/test.lua");


    if(resultDofile != LUA_OK)
    {
        std::cout << "unable to read file \n";
        std::cout << lua_tostring(m_LuaState, -1) << "\n";
    }

    std::cout << "test end \n";


    // run file Lua


}