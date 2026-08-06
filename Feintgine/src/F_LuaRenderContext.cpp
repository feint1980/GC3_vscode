#include "F_LuaRenderContext.h"
#include <string>


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

int lua_CompositeObject_setAngle(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_CompositeObject_setAngle) " << lua_gettop(L) << "\n";
        return -1;
    }
    {
        F_CompositeObject * obj = static_cast<F_CompositeObject*>(lua_touserdata(L, 1));
        float angle = lua_tonumber(L, 2);
        obj->setAngle(angle);
        return 0;
    }
    return 0;
}

int lua_CompositeObject_addLine(lua_State * L)
{
    if(lua_gettop(L) != 5)
    {
        std::cout << "gettop failed (lua_CompositeObject_addLine) " << lua_gettop(L) << "\n";
        return -1;
    }
    {
        F_CompositeObject * obj = static_cast<F_CompositeObject*>(lua_touserdata(L, 1));
        glm::vec2 offset = glm::vec2(lua_tonumber(L, 2), lua_tonumber(L, 3));
        float width = lua_tonumber(L, 4);
        float depth = lua_tonumber(L, 5);
        obj->addLine(offset, width, depth);
        return 0;
    }
    return 0;
}

int lua_CompositeObject_addText(lua_State * L)
{
    if(lua_gettop(L) != 11)
    {
        std::cout << "gettop failed (lua_CompositeObject_addText) " << lua_gettop(L) << "\n";
        return -1;
    }
    {
        F_CompositeObject * obj = static_cast<F_CompositeObject*>(lua_touserdata(L, 1));
        const char* ttS = lua_tostring(L, 2);
        std::wstring text = feint_common::Instance()->convertStringtoWstring(ttS);

        glm::vec2 offset = glm::vec2(lua_tonumber(L, 3), lua_tonumber(L, 4));
        int alignment = lua_tonumber(L, 5);
        float scale = lua_tonumber(L, 6);
        float r = lua_tonumber(L, 7);
        float g = lua_tonumber(L, 8);
        float b = lua_tonumber(L, 9);
        float a = lua_tonumber(L, 10);
        Feintgine::Color color(r, g, b, a);
        float angle = lua_tonumber(L, 11);
        std::wcout << L"print " << ttS << L"\n";
        // std::cout << "C++ address " << obj << "\n";
        tTextObject * t_obj = obj->addText(ttS, offset,  color,scale, alignment, angle);
        lua_pushlightuserdata(L, t_obj);
        return 1;
    }
    return 0;
}

int lua_CompositeObject_showPanelBG(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_CompositeObject_showPanelBG) " << lua_gettop(L) << "\n";
        return -1;
    }
    {
        F_CompositeObject * obj = static_cast<F_CompositeObject*>(lua_touserdata(L, 1));
        bool show = lua_toboolean(L, 2);
        obj->showPanelBG(show);
        return 0;
    }
    return 0;
}

int lua_CompositeObject_setPanelBGColor(lua_State * L)
{
    if(lua_gettop(L) != 5)
    {
        std::cout << "gettop failed (lua_CompositeObject_setPanelBGColor) " << lua_gettop(L) << "\n";
        return -1;
    }
    {
        F_CompositeObject * obj = static_cast<F_CompositeObject*>(lua_touserdata(L, 1));
        float r = lua_tonumber(L, 2);
        float g = lua_tonumber(L, 3);
        float b = lua_tonumber(L, 4);
        float a = lua_tonumber(L, 5);
        obj->setPanelBGColor(Feintgine::Color(r, g, b, a));
        return 0;
    }
    return 0;
}

int lua_CompositeObject_setPanelBGScale(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_CompositeObject_setPanelBGScale) " << lua_gettop(L) << "\n";
        return -1;
    }
    {
        F_CompositeObject * obj = static_cast<F_CompositeObject*>(lua_touserdata(L, 1));
        float scale = lua_tonumber(L, 2);
        obj->setPanelScale(scale);
        return 0;
    }
    return 0;
}

int lua_CompositeObject_setVisible(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_CompositeObject_setVisible) " << lua_gettop(L) << "\n";
        return -1;
    }
    {
        F_CompositeObject * obj = static_cast<F_CompositeObject*>(lua_touserdata(L, 1));
        bool visible = lua_toboolean(L, 2);
        obj->setVisible(visible);
        return 0;
    }
    return 0;
}

int lua_CompositeObject_registerSignalUpdate(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_CompositeObject_registerSignalUpdate) " << lua_gettop(L) << "\n";
        return -1;
    }
    {
        F_CompositeObject * obj = static_cast<F_CompositeObject*>(lua_touserdata(L, 1));
        int flagValue = lua_toboolean(L, 2);
        obj->registerSignalUpdate(flagValue);
        return 0;
    }
    return 0;
}

int lua_CompositeObject_registerCallback(lua_State * L)
{
    // args: (compositeObject, eventName, function)
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_CompositeObject_registerCallback) " << lua_gettop(L) << "\n";
        return -1;
    }
    {
        F_CompositeObject * obj = static_cast<F_CompositeObject*>(lua_touserdata(L, 1));
        if(!obj)
        {
            std::cout << "lua_CompositeObject_registerCallback: null/stale composite object pointer, ignoring\n";
            return 0;
        }

        std::string eventName = lua_tostring(L, 2);

        lua_pushvalue(L, 3);              // duplicate the function, since registerCallback
        obj->registerCallback(L, eventName); // consumes (pops) the top of the stack
        return 0;
    }
    return 0;
}

int lua_CompositeObject_isHovered(lua_State * L)
{
    if(lua_gettop(L) != 1)
    {
        std::cout << "gettop failed (lua_CompositeObject_isHovered) " << lua_gettop(L) << "\n";
        return -1;
    }
    {
        F_CompositeObject * obj = static_cast<F_CompositeObject*>(lua_touserdata(L, 1));
        bool hovered = obj->isHovered();
        lua_pushboolean(L, hovered);
        return 1;
    }
    return 0;
    
}

int lua_CompositeObject_fireCallback(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_CompositeObject_fireCallback) " << lua_gettop(L) << "\n";
        return -1;
    }
    {
        F_CompositeObject * obj = static_cast<F_CompositeObject*>(lua_touserdata(L, 1));
        std::string eventName = lua_tostring(L, 2);
        obj->fireCallback(eventName);
        return 0;
    }
    return 0;
}

int lua_CompositeObject_setFrameColor(lua_State * L)
{
    if(lua_gettop(L) != 5)
    {
        std::cout << "gettop failed (lua_CompositeObject_setFrameColor) " << lua_gettop(L) << "\n";
        return -1;
    }
    {
        F_CompositeObject * obj = static_cast<F_CompositeObject*>(lua_touserdata(L, 1));
        float r = lua_tonumber(L, 2);
        float g = lua_tonumber(L, 3);
        float b = lua_tonumber(L, 4);
        float a = lua_tonumber(L, 5);
        obj->setFrameColor(Feintgine::Color(r, g, b,a));
        return 0;
    }
    return 0;
}

int lua_CompositeObjectText_setText(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_CompositeObjectText_setText) " << lua_gettop(L) << "\n";
        return -1;
    }
    {
        tTextObject * obj = static_cast<tTextObject*>(lua_touserdata(L, 1));
        std::string text = lua_tostring(L, 2);
        obj->setText(text);
        return 0;
    }
    return 0;
}

int lua_CompositeObjectText_setColor(lua_State * L)
{
    if(lua_gettop(L) != 5)
    {
        std::cout << "gettop failed (lua_CompositeObjectText_setColor) " << lua_gettop(L) << "\n";
        return -1;
    }
    {
        tTextObject * obj = static_cast<tTextObject*>(lua_touserdata(L, 1));
        float r = lua_tonumber(L, 2);
        float g = lua_tonumber(L, 3);
        float b = lua_tonumber(L, 4);
        float a = lua_tonumber(L, 5);
        obj->setColor(Feintgine::Color(r, g, b,a));
        return 0;
    }
    return 0;
}

int lua_CompositeObjectText_setScale(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_CompositeObjectText_setScale) " << lua_gettop(L) << "\n";
        return -1;
    }
    {
        tTextObject * obj = static_cast<tTextObject*>(lua_touserdata(L, 1));
        float scale = lua_tonumber(L, 2);
        obj->setScale(scale);
        return 0;
    }
    return 0;
}

int lua_CompositeObjectText_setAlignment(lua_State * L)
{
    if(lua_gettop(L) != 2)
    {
        std::cout << "gettop failed (lua_CompositeObjectText_setAlignment) " << lua_gettop(L) << "\n";
        return -1;
    }
    {
        tTextObject * obj = static_cast<tTextObject*>(lua_touserdata(L, 1));
        int alignment = lua_tointeger(L, 2);
        obj->setAlignment(alignment);
        return 0;
    }
    return 0;
}

int lua_CompositeObjectText_setOffsetPos(lua_State * L)
{
    if(lua_gettop(L) != 3)
    {
        std::cout << "gettop failed (lua_CompositeObjectText_setOffsetPos) " << lua_gettop(L) << "\n";
        return -1;
    }
    {
        tTextObject * obj = static_cast<tTextObject*>(lua_touserdata(L, 1));
        float x = lua_tonumber(L, 2);
        float y = lua_tonumber(L, 3);
        obj->setOffset(glm::vec2(x, y));
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
    lua_register(m_script, "cpp_CompositeObject_addEmblem", lua_CompositeObject_AddEmblem);
    lua_register(m_script, "cpp_CompositeObject_setAngle", lua_CompositeObject_setAngle);
    lua_register(m_script, "cpp_CompositeObject_addLine", lua_CompositeObject_addLine);
    lua_register(m_script, "cpp_CompositeObject_addText", lua_CompositeObject_addText);

    lua_register(m_script, "cpp_CompositeObject_showPanelBG", lua_CompositeObject_showPanelBG);
    lua_register(m_script, "cpp_CompositeObject_setPanelBGColor", lua_CompositeObject_setPanelBGColor);
    lua_register(m_script, "cpp_CompositeObject_setPanelBGScale", lua_CompositeObject_setPanelBGScale);

    lua_register(m_script, "cpp_CompositeObject_setVisible", lua_CompositeObject_setVisible);
    lua_register(m_script, "cpp_CompositeObject_registerSignalUpdate", lua_CompositeObject_registerSignalUpdate);
    lua_register(m_script, "cpp_CompositeObject_isHovered", lua_CompositeObject_isHovered);
    lua_register(m_script, "cpp_CompositeObject_registerCallback", lua_CompositeObject_registerCallback);
    lua_register(m_script, "cpp_CompositeObject_fireCallback", lua_CompositeObject_fireCallback);
    lua_register(m_script, "cpp_CompositeObject_setFrameColor", lua_CompositeObject_setFrameColor);

    // composite text section
    lua_register(m_script, "cpp_CompositeObjectText_setText", lua_CompositeObjectText_setText);
    lua_register(m_script, "cpp_CompositeObjectText_setColor", lua_CompositeObjectText_setColor);
    lua_register(m_script, "cpp_CompositeObjectText_setScale", lua_CompositeObjectText_setScale);
    lua_register(m_script, "cpp_CompositeObjectText_setAlignment", lua_CompositeObjectText_setAlignment); 
    lua_register(m_script, "cpp_CompositeObjectText_setOffsetPos", lua_CompositeObjectText_setOffsetPos);
    

}
void F_LuaRenderContext::initTextRenderer(int fontSize, int charCount, const std::string& fontFilePath)
{


    // m_textRenderer.init(fontSize, charCount, fontFilePath);
    std::vector<UnicodeRange> ranges = {
        { 0x0020, 0x007E } // space .. ~
    };

    // Corpus-scanned CJK/extended text (dialogue, character names, etc.)
    std::string allGameText = "黄昏結界方彼岸渡東風谷早苗こんやaz09!)%\\/" /* concatenate all non-ASCII UI/dialogue text here */;
    auto cjkRanges = m_textRenderer.rangesFromText(allGameText);
    ranges.insert(ranges.end(), cjkRanges.begin(), cjkRanges.end());

    m_textRenderer.init(fontSize, ranges, fontFilePath);
    std::cout << "fontSize " << fontSize << " fontFilePath " << fontFilePath << "\n";
}

void F_LuaRenderContext::initTextRendererByRange(int fontSize, const std::string & letters , const std::string& fontFilePath)
{
    std::vector<UnicodeRange> ranges = {
        { 0x0020, 0x007E } // space .. ~
    };

    // Corpus-scanned CJK/extended text (dialogue, character names, etc.)
    std::string allGameText = letters;
    auto cjkRanges = m_textRenderer.rangesFromText(allGameText);
    ranges.insert(ranges.end(), cjkRanges.begin(), cjkRanges.end());

    m_textRenderer.init(fontSize, ranges, fontFilePath);
    std::cout << "fontSize " << fontSize << " fontFilePath " << fontFilePath << "\n";
    
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

void F_LuaRenderContext::draw(Feintgine::SpriteBatch & spriteBatch,Feintgine::Camera2D * camera)
{
    m_tCam = camera;
    
    for(int i = 0; i < m_compositeObjects.size(); i++)
    {
        m_compositeObjects[i].draw(spriteBatch);
    }
}

void F_LuaRenderContext::drawText(const Feintgine::Camera2D & camera)
{
    m_textRenderer.begin();

    for(size_t i = 0; i < m_compositeObjects.size(); i++)
    {
        m_compositeObjects[i].drawText(m_textRenderer);
    }

    m_textRenderer.end(camera);
}



void F_LuaRenderContext::updateSignals(Feintgine::InputManager & inputManager)
{   
    // asd
    if(!m_tCam)
    {
        std::cout << "no cam registered \n";
        return;
    }

    
    glm::vec2 mousePos = m_tCam->convertScreenToWorld(inputManager.getMouseCoords());
    // bool isMousePressd = inputManager.isKeyPressed(SDL_BUTTON_LEFT)
    // std::cout << "mousePos " << mousePos.x << " " << mousePos.y << "\n";
    for(int i = 0; i < m_compositeObjects.size(); i++)
    {
        m_compositeObjects[i].listenToSignals(mousePos);
    }
    
}


}