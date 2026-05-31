#ifndef _F_COMPOSITEOBJECT_H_
#define _F_COMPOSITEOBJECT_H_

#include "EmptyObject.h"
#include "F_Sprite.h"
#include "F_Object.h"
#include "F_AnimatedObject.h"
#include "F_FramePanel.h"

namespace Feintgine
{

enum ObjectTypes
{
    TNoObject = 0,
    TEmptyObject = 1,
    TF_Sprite = 2,
    TF_Object = 4,
    TF_AnimatedObject = 8,
    // reserved for future
    TF_FramePanel = 32 //
};

// struct DrawQuad
// {
//     glm::vec4 desRect; 
//     glm::vec4 uv;
// }

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
    F_AnimatedObject animatedObject;
    glm::vec2 posOffset;
    glm::vec2 scale; // compare to F_Composite object
    Feintgine::Color color;
    float angle;
    float depth;
};

class F_CompositeObject
{

public:
    F_CompositeObject() {}
    ~F_CompositeObject(){}

    void init(const glm::vec2 & pos, const glm::vec2 & dim)
    { m_pos = pos; m_dim = dim; }

    void addObject( const std::string & spriteNameWithPacket, const glm::vec2 & posOffset, const glm::vec2 & scale, const Feintgine::Color & color, float angle, float depth);
    // void init()

    void draw(Feintgine::SpriteBatch & spriteBatch);

protected:
    glm::vec2 m_pos;
    glm::vec2 m_dim;
    
    std::vector<tObject> m_objectList;
    std::vector<tAObject> m_animatedObjectList;

};
}
#endif // _F_COMPOSITEOBJECT_H_