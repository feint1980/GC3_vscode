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

int lua_RemoveCompositeObject(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_RemoveCompositeObject) " << lua_gettop(L) << "\n";
        return -1;
    }
    {
        F_LuaRenderContext * lrc = static_cast<F_LuaRenderContext*>(lua_touserdata(L, 1));
        F_CompositeObject * obj = static_cast<F_CompositeObject*>(lua_touserdata(L, 2));
        lrc->removeCompositeObject(obj);
    }
    return 0;
}

int lua_CompositeObject_addPanel(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_CompositeObject_addPanel) " << lua_gettop(L) << "\n";
        return -1;
    }
    {
        F_CompositeObject * obj = static_cast<F_CompositeObject*>(lua_touserdata(L, 1));
        std::string borderName = lua_tostring(L, 2);
        float scale = lua_tonumber(L, 3);
        obj->addPanel(borderName, scale);
        return 0;
    }
    return 0;
}

int lua_CompositeObject_addAnimatedObject(lua_State * L)
{
    if(lua_gettop(L) != 13)
    {
        std::cout << "gettop failed (lua_CompositeObject_addAnimatedObject) " << lua_gettop(L) << "\n";
        return -1;
    }
    {
        F_CompositeObject * obj = static_cast<F_CompositeObject*>(lua_touserdata(L, 1));
        std::string filePath = lua_tostring(L, 2);
        std::string startAnim = lua_tostring(L, 3);
        glm::vec2 pos = glm::vec2(lua_tonumber(L, 4), lua_tonumber(L, 5));
        glm::vec2 scale = glm::vec2(lua_tonumber(L, 6), lua_tonumber(L, 7));
        int colorR = lua_tonumber(L, 8);
        int colorG = lua_tonumber(L, 9);
        int colorB = lua_tonumber(L, 10);
        int colorA = lua_tonumber(L, 11);
        float angle = lua_tonumber(L, 12);
        float depth = lua_tonumber(L, 13);
        tAObject * aObj = obj->addAnimatedObject(filePath, startAnim, pos, scale, Feintgine::Color(colorR, colorG, colorB, colorA), angle, depth);

        lua_pushlightuserdata(L, aObj);
        return 1;
    }
    return 0;
}

int lua_CompositeObject_addSprite(lua_State * L)
{
    if(lua_gettop(L) != 12)
    {
        std::cout << "gettop failed (lua_CompositeObject_addSprite) " << lua_gettop(L) << "\n";
        return -1;
    }
    {
        F_CompositeObject * obj = static_cast<F_CompositeObject*>(lua_touserdata(L, 1));
        std::string spriteName = lua_tostring(L, 2);
        glm::vec2 pos = glm::vec2(lua_tonumber(L, 3), lua_tonumber(L, 4));
        glm::vec2 dim = glm::vec2(lua_tonumber(L, 5), lua_tonumber(L, 6));
        int colorR = lua_tonumber(L, 7);
        int colorG = lua_tonumber(L, 8);
        int colorB = lua_tonumber(L, 9);
        int colorA = lua_tonumber(L, 10);
        float angle = lua_tonumber(L, 11);
        float depth = lua_tonumber(L, 12);
        Feintgine::Color color(colorR, colorG, colorB, colorA);
        tObject * t_obj =  obj->addObject(spriteName, pos, dim,color, angle, depth);
        
        lua_pushlightuserdata(L, t_obj);
        return 1;
    }
    return 0;
}

int lua_CompositeObject_AddEmblem(lua_State * L)
{
    if(lua_gettop(L) != 8)
    {
        std::cout << "gettop failed (lua_CompositeObject_AddEmblem) " << lua_gettop(L) << "\n";
        return -1;
    }
    {
        F_CompositeObject * obj = static_cast<F_CompositeObject*>(lua_touserdata(L, 1));
        int type = lua_tonumber(L, 2);
        std::string emblemName = lua_tostring(L, 3);
        int placeFlag = lua_tonumber(L, 4);
        int hideFlag = lua_tonumber(L, 5);
        float offsetX = lua_tonumber(L, 6);
        float offsetY = lua_tonumber(L, 7);
        float scale = lua_tonumber(L, 8);
        // float depth = lua_tonumber(L, 9);
        switch(type)
        {
            case EMBLEM_LINE:
            {
                obj->addPanelLineEmblem(emblemName, placeFlag, hideFlag, glm::vec2(offsetX, offsetY), scale);
                break;
            }
            case EMBLEM_CORNER:
            {
                obj->addPanelCornerEmblem(emblemName, placeFlag, hideFlag, glm::vec2(offsetX, offsetY), scale);
                break;
            }
            default:
            {
                std::cout << "Unknown emblem type " << type << "\n";
                break;
            }
        }

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

void F_LuaRenderContext::removeCompositeObject(F_CompositeObject * compositeObject)
{
    for(size_t i = 0; i < m_compositeObjects.size(); i++)
    {
        if(compositeObject == &m_compositeObjects[i] )
        {
            m_compositeObjects.erase(m_compositeObjects.begin() + i);
            return;
        }
    }
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

    // LRC (Lua Render Context)
    lua_register(m_script, "cpp_LRC_CreateCompositeObject", lua_CreateCompositeObject);
    lua_register(m_script, "cpp_LRC_RemoveCompositeObject", lua_RemoveCompositeObject);

    // Composite Object
    lua_register(m_script, "cpp_CompositeObject_addSprite", lua_CompositeObject_addSprite);
    lua_register(m_script, "cpp_CompositeObject_addAnimatedObject", lua_CompositeObject_addAnimatedObject);
    lua_register(m_script, "cpp_CompositeObject_addPanel", lua_CompositeObject_addPanel);
    lua_register(m_script, "cpp_CompositeObject_AddEmblem", lua_CompositeObject_AddEmblem);


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