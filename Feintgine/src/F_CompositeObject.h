#ifndef _F_COMPOSITEOBJECT_H_
#define _F_COMPOSITEOBJECT_H_

#include "EmptyObject.h"
#include "F_Sprite.h"
#include "F_Object.h"
#include "F_AnimatedObject.h"
#include "F_FramePanel.h"

namespace Feintgine
{

class F_CompositeObject
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
    // std::unique_ptr<F_AnimatedObject> animatedObject= std::make_unique<F_AnimatedObject>(); //F_AnimatedObject animatedObject;
    F_AnimatedObject * animatedObject = nullptr;
    glm::vec2 posOffset;
    glm::vec2 scale; // compare to F_Composite object
    Feintgine::Color color;
    float angle;
    float depth;
};


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

    void init(const glm::vec2 & pos, const glm::vec2 & dim, float angle = 0, float depth = 5.0f);

    void addObject( const std::string & spriteNameWithPacket, const glm::vec2 & posOffset, const glm::vec2 & scale, const Feintgine::Color & color, float angle, float depth);
    // void init()

    void addAnimatedObject(const std::string & animFile, const std::string & defaultAnim, const glm::vec2 & posOffset, const glm::vec2 & scale, const Feintgine::Color & color, float angle, float depth);

    void draw(Feintgine::SpriteBatch & spriteBatch);

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
    
    void addPanelCornerEmblem(const std::string & emblemSprite, int placeMask, int hideMask, const glm::vec2 & offset, float scale);

    void addPanelLineEmblem(const std::string & emblemSprite, int placeMask, int hideMask, const glm::vec2 & offset, float scale);

    F_FramePanel * getFramePanel() { return &m_framePanel; }

protected:

    Uint32 m_type;

    glm::vec2 m_pos;
    glm::vec2 m_dim;
    
    float m_angle = 0.0;
    float m_depth = 5.0;

    std::vector<tObject> m_objectList;
    std::vector<tAObject> m_animatedObjectList;
    F_FramePanel m_framePanel;

};
}
#endif // _F_COMPOSITEOBJECT_H_