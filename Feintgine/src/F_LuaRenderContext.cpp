#include "F_LuaRenderContext.h"




namespace Feintgine
{
int lua_CreateCompositeObject(lua_State * L)
{
    if(lua_gettop(L) != 7)
    {
        std::cout << "gettop failed (lua_CreateCompositeObject) " << lua_gettop(L) << "\n";
        return -1;
    }
    {
        F_LuaRenderContext * lrc = static_cast<F_LuaRenderContext*>(lua_touserdata(L, 1));
        glm::vec2 pos = glm::vec2(lua_tonumber(L, 2), lua_tonumber(L, 3));
        glm::vec2 dim = glm::vec2(lua_tonumber(L, 4), lua_tonumber(L, 5));
        float angle = lua_tonumber(L, 6);
        float depth = lua_tonumber(L, 7);
        F_CompositeObject * obj =  lrc->addObjectComposite(pos, dim, angle, depth);
        lua_pushlightuserdata(L, obj);
        return 1;
    }
    return 0;
}

int lua_CompositeObject_addSprite(lua_State * L)
{
    if(lua_gettop(L) != 6)
    {
        std::cout << "gettop failed (lua_CompositeObject_addSprite) " << lua_gettop(L) << "\n";
        return -1;
    }
    {
        F_CompositeObject * obj = static_cast<F_CompositeObject*>(lua_touserdata(L, 1));
        std::string spriteName = lua_tostring(L, 2);
        glm::vec2 pos = glm::vec2(lua_tonumber(L, 3), lua_tonumber(L, 4));
        glm::vec2 dim = glm::vec2(lua_tonumber(L, 5), lua_tonumber(L, 6));
        obj->addObject(spriteName, pos, dim);
        return 0;
    }
    return 0;
}

F_LuaRenderContext::F_LuaRenderContext()
{

}

F_LuaRenderContext::~F_LuaRenderContext()
{
    
}

void F_LuaRenderContext::init(lua_State * script,int maxCompositeObjects)
{
    m_script = script;
    std::cout << "Init LuaRenderContext \n";

    m_compositeObjects.reserve(maxCompositeObjects);

    // register C++ functions here

    if(LuaManager::Instance()->checkLua(m_script, luaL_dofile(m_script, "../../Lua/system/renderer/renderContext.lua")))
    {
        std::cout << "F_LuaRenderContext run script renderContext OK \n";
    }
    // dofile here 
    lua_register(m_script, "cpp_LRC_CreateCompositeObject", lua_CreateCompositeObject);
    lua_register(m_script, "cpp_CompositeObject_addSprite", lua_CompositeObject_addSprite);

}

void F_LuaRenderContext::update(float delta)
{
    for(int i = 0; i < m_compositeObjects.size(); i++)
    {
        m_compositeObjects[i].update(delta);
    }
}

F_CompositeObject * F_LuaRenderContext::addObjectComposite(const glm::vec2 & pos, const glm::vec2 & dim, float angle, float depth)
{
    int size = m_compositeObjects.size();
    if(size + 1 == m_compositeObjects.capacity())
    {
        std::cout << "F_LuaRenderContext Warning, Reach Maximum Composite Objects, We will stop adding instead of extend the cap and cause weird behavior, if you see this, adjust the maximum capacity \n";
        return nullptr;
    }

    F_CompositeObject obj;
    obj.init(pos, dim, angle, depth);
    m_compositeObjects.push_back(obj);
    return &m_compositeObjects[size];
    
}


void F_LuaRenderContext::draw(Feintgine::SpriteBatch & spriteBatch)
{
    for(int i = 0; i < m_compositeObjects.size(); i++)
    {
        m_compositeObjects[i].draw(spriteBatch);
    }
}


}