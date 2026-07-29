#ifndef _F_COMPOSITEOBJECT_H_
#define _F_COMPOSITEOBJECT_H_

#include "EmptyObject.h"
#include "F_Sprite.h"
#include "F_Object.h"
#include "F_AnimatedObject.h"
#include "F_FramePanel.h"

#include "feint_common.h"

#include <functional>
#include <unordered_map>
#include <string>

struct lua_State; // forward declare - avoids pulling lua.hpp into every header that includes this one

#define UPDATE_SIGNAL_MOUSE_HOVER 1
// #define UPDATE_SIGNAL_  

namespace Feintgine
{

struct tObject
{
    F_Sprite sprite;
    glm::vec2 posOffset;
    glm::vec2 scale; // compare to F_Composite object
    Feintgine::Color color;
    float angle;
    float depth;

    void setSprite(const std::string & spriteName ) 
    { 
        this->sprite = Feintgine::SpriteManager::Instance()->getSprite(spriteName); 
    }

};


struct tAObject
{
    F_AnimatedObject animatedObject;// = nullptr; // need to be a pointer for some reason
    glm::vec2 posOffset;
    glm::vec2 scale; // compare to F_Composite object
    Feintgine::Color color;
    float angle;
    float depth;

    void setAnimatedObject(const std::string & animFile, const std::string & defaultAnim) { 
        animatedObject.init(animFile); 
        animatedObject.playAnimation(defaultAnim);
    }
};

struct tTextObject
{
    glm::vec2 posOffset = glm::vec2(0, 0);
    std::wstring text = L"";
    alignas(16) Feintgine::Color color = Feintgine::Color(255, 255, 255, 255);
    float scale = 1.0f;
    unsigned char justification = ALIGN_FT_LEFT;
    float angle = 0.0f;

    void changeText(const std::wstring & newText) { text = newText; }
    void changeText(const std::string & newText)
    {
        text = feint_common::Instance()->convertStringtoWstring(newText);
    }
};


class F_CompositeObject
{


enum ObjectTypes
{
    TNoObject = 0,
    TFEmptyObject = 1,
    TF_Sprite = 2,
    TF_Object = 4,
    TF_AnimatedObject = 8,
    // reserved for future
    TF_FramePanel = 32 //
};

public:
    F_CompositeObject(); // wow, such a lesson to learn, if I put body in this, my vector object size go brrrrrrr
    ~F_CompositeObject();

    // move constructor 
    F_CompositeObject(const F_CompositeObject&other);

    // NOTE: this used to be a no-op (`{ return *this; }`), which silently broke
    // vector::erase()-driven removal: erase() shifts trailing elements down via
    // assignment, and a no-op assignment meant erased objects never actually got
    // their data replaced. This is now a real member-wise copy.
    //
    // Known remaining caveat: m_callbackRefs/m_luaState below are copied by value
    // (shallow copy of the map, no luaL_ref duplication logic). If this object is
    // ever assigned as part of an erase()-shift *after* Lua callbacks have been
    // registered on it, the registry ref ownership semantics get muddy (same class
    // of issue as the raw-pointer-into-vector problem discussed for
    // F_LuaRenderContext::removeCompositeObject). Fine for now since nothing calls
    // registerCallback before an object settles into its final vector slot, but
    // flagging it here so it isn't forgotten if that assumption changes.
    F_CompositeObject& operator=(const F_CompositeObject& other)
    {
        if (this == &other)
        {
            return *this;
        }

        m_type = other.m_type;
        m_maxObject = other.m_maxObject;
        m_isVisible = other.m_isVisible;
        m_isHovered = other.m_isHovered;
        m_signalUpdateFlag = other.m_signalUpdateFlag;
        m_pos = other.m_pos;
        m_dim = other.m_dim;
        m_angle = other.m_angle;
        m_depth = other.m_depth;

        m_objectList = other.m_objectList;
        m_animatedObjectList = other.m_animatedObjectList;
        m_textObjectList = other.m_textObjectList;
        m_objectList.reserve(m_maxObject);
        m_animatedObjectList.reserve(m_maxObject);
        m_textObjectList.reserve(m_maxObject);

        // These map keys are pointers into OUR OWN vectors - never copy other's
        // map verbatim, always rebuild against our own just-copied storage.
        m_objectIndexMap.clear();
        for (size_t i = 0; i < m_objectList.size(); ++i)
        {
            m_objectIndexMap[&m_objectList[i]] = i;
        }

        m_animatedObjectIndexMap.clear();
        for (size_t i = 0; i < m_animatedObjectList.size(); ++i)
        {
            m_animatedObjectIndexMap[&m_animatedObjectList[i]] = i;
        }

        m_textObjectIndexMap.clear();
        for (size_t i = 0; i < m_textObjectList.size(); ++i)
        {
            m_textObjectIndexMap[&m_textObjectList[i]] = i;
        }

        m_framePanel = other.m_framePanel;

        m_luaState = other.m_luaState;
        m_callbackRefs = other.m_callbackRefs;

        return *this;
    }
    // F_CompositeObject(F_CompositeObject && other) noexcept
    // {
    //     m_type = other.m_type;
    //     m_maxObject = other.m_maxObject;
    //     m_pos = other.m_pos;
    //     m_dim = other.m_dim;
    //     m_angle = other.m_angle;
    //     m_depth = other.m_depth;
    //     m_objectList = std::move(other.m_objectList);
    //     m_animatedObjectList = std::move(other.m_animatedObjectList);
    //     m_textObjectList = std::move(other.m_textObjectList);
    //     m_framePanel = std::move(other.m_framePanel);
    // }
    // F_CompositeObject& operator=(F_CompositeObject&& other) noexcept;

    void init(const glm::vec2 & pos, const glm::vec2 & dim, float angle = 0, float depth = 5.0f);

    tObject * addObject( const std::string & spriteNameWithPacket, const glm::vec2 & posOffset, const glm::vec2 & scale, const Feintgine::Color & color = Feintgine::Color(255,255,255,255), float angle = 0, float depth = 5.0f);
    // void init()

    tAObject * addAnimatedObject(const std::string & animFile, const std::string & defaultAnim, const glm::vec2 & posOffset, const glm::vec2 & scale, const Feintgine::Color & color, float angle, float depth);

    void draw(Feintgine::SpriteBatch & spriteBatch);

    void drawText(TextRenderer & textRenderer);

    void update(float deltaTime);

    // void inputUpdate(,const glm::vec2 & mousePos);

    void updateInput(const glm::vec2 & mousePos);

    void setPos(const glm::vec2 & pos) 
    {
        m_pos = pos; 
        m_framePanel.setPos(pos);
    }

    void setDim(const glm::vec2 & dim) 
    { 
        m_dim = dim; 
        m_framePanel.setSize(dim);
    }

    void flagUpdate();    

    void addPanel(const std::string & borderPacket, float borderScale);

    void showPanelBG(bool show) 
    { 
        if(!(m_type & ObjectTypes::TF_FramePanel)) // no frame panel
        {
            std::cout << "No frame panel created (showPanelBG) !!!!!\n";
            return ;
        }
        m_framePanel.showPanelBG(show); 
    }
    void setPanelBGColor(const Feintgine::Color & color) 
    { 
        if(!(m_type & ObjectTypes::TF_FramePanel)) // no frame panel
        {
            std::cout << "No frame panel created (setPanelBGColor) !!!!!\n";
            return ;
        }
        m_framePanel.setPanelBGColor(color); 
    }
    void setFrameColor(const Feintgine::Color & color)
    {
        m_framePanel.setColor(color);
    }

    void setPanelScale(float scale) 
    { 
        if(!(m_type & ObjectTypes::TF_FramePanel)) // no frame panel
        {
            std::cout << "No frame panel created (setPanelScale) !!!!!\n";
            return ;
        }
        m_framePanel.setPanelBGScale(scale); 
    }

    void addPanelCornerEmblem(const std::string & emblemSprite, int placeMask, int hideMask, const glm::vec2 & offset, float scale);

    void addPanelLineEmblem(const std::string & emblemSprite, int placeMask, int hideMask, const glm::vec2 & offset, float scale);

    void addFrameLine(const glm::vec2 & offset, float width, float depth);

    F_FramePanel * getFramePanel() { return &m_framePanel; }

    void setAngle(float angle) 
    { 
        m_angle = angle;
        m_framePanel.setAngle(angle); 
    }

    void addLine(const glm::vec2 & offset, float width, float depth) { m_framePanel.addLine(offset, width, depth); }

    tTextObject * addText(const std::wstring & text, const glm::vec2 & posOffset, const Feintgine::Color & color, float scale, unsigned char justification, float angle);

    tTextObject * addText(const std::string & text, const glm::vec2 & posOffset, const Feintgine::Color & color, float scale, unsigned char justification, float angle);

    bool isVisible() const { return m_isVisible; }

    void setVisible(bool visible) { m_isVisible = visible; }

    bool isHovered() const { return m_isHovered; }

    void listenToSignals(const glm::vec2 & mousePos);

    void registerSignalUpdate(int type) { m_signalUpdateFlag |= type; }

    // Registers a Lua function (must be on top of the Lua stack when this is
    // called - it will be popped) under eventName, e.g. "onHoverEnter",
    // "onHoverExit", "onClick". Re-registering the same eventName overwrites
    // the previous callback (and releases its registry ref).
    void registerCallback(lua_State * L, const std::string & eventName);

    // Calls the Lua function registered under eventName, if any. Safe no-op
    // if nothing is registered or no callback has ever been set up for this
    // object (m_luaState == nullptr).
    void fireCallback(const std::string & eventName);

protected:

    Uint32 m_type = TNoObject;

    Uint8 m_maxObject = 10;

    bool m_isVisible = true;

    bool m_isHovered = false;
    bool wasHovered = false;

    int m_signalUpdateFlag = 0;

    glm::vec2 m_pos = glm::vec2(0.0f);
    glm::vec2 m_dim = glm::vec2(0.0f);
    
    float m_angle = 0.0;
    float m_depth = 5.0;

    std::vector<tObject> m_objectList;
    std::vector<tAObject> m_animatedObjectList;
    std::vector<tTextObject> m_textObjectList;

    std::unordered_map<tObject *, size_t> m_objectIndexMap;
    std::unordered_map<tAObject *, size_t> m_animatedObjectIndexMap;
    std::unordered_map<tTextObject *, size_t> m_textObjectIndexMap;

    F_FramePanel m_framePanel;

    // Lua callback storage. Keyed by event name ("onHoverEnter", "onClick", etc)
    // -> LUA_REGISTRYINDEX ref. m_luaState is cached so fireCallback() doesn't
    // need it passed in every time.
    //
    // TODO(leak, intentional for now): refs are never released via luaL_unref,
    // even on object destruction/removal. See the note above on operator=/erase()
    // - proper cleanup wants to happen exactly once, at the point a slot is
    // deliberately recycled, which isn't well-defined yet given F_LuaRenderContext
    // still removes objects via vector::erase(). Revisit together with that fix.
    // Until then this is a small bounded leak (a handful of registry refs per
    // removed composite object), not a correctness bug.
    lua_State * m_luaState = nullptr;
    std::unordered_map<std::string, int> m_callbackRefs;

};
}
#endif // _F_COMPOSITEOBJECT_H_