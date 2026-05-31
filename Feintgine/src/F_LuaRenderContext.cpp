#include "F_LuaRenderContext.h"


namespace Feintgine
{

F_LuaRenderContext::F_LuaRenderContext()
{

}

F_LuaRenderContext::~F_LuaRenderContext()
{
    
}

void F_LuaRenderContext::init(lua_State * script)
{
    m_script = script;
    std::cout << "Init LuaRenderContext \n";

    // register C++ functions here

    if(LuaManager::Instance()->checkLua(m_script, luaL_dofile(m_script, "../../Lua/system/renderer/renderContext.lua")))
    {
        std::cout << "F_LuaRenderContext run script renderContext OK \n";
    }
    // dofile here 

}

void F_LuaRenderContext::update(float delta)
{

}

void F_LuaRenderContext::draw(Feintgine::SpriteBatch & spriteBatch)
{

}





}