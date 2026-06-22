#ifndef _F_COMPOSITEOBJECT_H_
#define _F_COMPOSITEOBJECT_H_

#include "EmptyObject.h"
#include "F_Sprite.h"
#include "F_Object.h"
#include "F_AnimatedObject.h"
#include "F_FramePanel.h"

#include "feint_common.h"

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
    
};

struct tAObject
{
    F_AnimatedObject animatedObject;// = nullptr; // need to be a pointer for some reason
    glm::vec2 posOffset;
    glm::vec2 scale; // compare to F_Composite object
    Feintgine::Color color;
    float angle;
    float depth;
};

struct tTextObject
{
    glm::vec2 posOffset = glm::vec2(0, 0);
    std::wstring text = L"";
    alignas(16) Feintgine::Color color = Feintgine::Color(255, 255, 255, 255);
    float scale = 1.0f;
    unsigned char justification = ALIGN_FT_LEFT;
    float angle = 0.0f;

    // void changeText(const std::wstring & newText) { text = newText; }
    // void changeText(const std::string & newText)
    // {
    //     text = feint_common::Instance()->convertStringtoWstring(newText);
    // }
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
    F_CompositeObject& operator=(const F_CompositeObject&)
    {
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


protected:

    Uint32 m_type = TNoObject;

    Uint8 m_maxObject = 10;

    glm::vec2 m_pos = glm::vec2(0.0f);
    glm::vec2 m_dim = glm::vec2(0.0f);
    
    float m_angle = 0.0;
    float m_depth = 5.0;

    std::vector<tObject> m_objectList;
    std::vector<tAObject> m_animatedObjectList;
    std::vector<tTextObject> m_textObjectList;


    F_FramePanel m_framePanel;

};
}
#endif // _F_COMPOSITEOBJECT_H_