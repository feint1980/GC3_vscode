

#include "F_CompositeObject.h"

namespace Feintgine
{


F_CompositeObject::F_CompositeObject() 
{
    m_objectList = std::vector<tObject>();
    m_animatedObjectList = std::vector<tAObject>();
    m_angle = 0.0f;
    m_type = 0;
    m_depth = 5.0f;
    m_objectList.reserve(m_maxObject);
    m_animatedObjectList.reserve(m_maxObject);
}

F_CompositeObject::~F_CompositeObject()
{

}

void F_CompositeObject::init(const glm::vec2 & pos, const glm::vec2 & dim, float angle, float depth)
{
    m_pos = pos;
    m_dim = dim;
    m_angle = angle;
    m_depth = depth;
}

tObject * F_CompositeObject::addObject( const std::string & spriteNameWithPacket, const glm::vec2 & posOffset, const glm::vec2 & scale, const Feintgine::Color & color, float angle, float depth)
{

    if(m_objectList.size() >= m_maxObject)
    {
        std::cout << "F_CompositeObject Warning, Reach Maximum Objects, We will stop adding instead of extend the cap and cause weird behavior, if you see this, adjust the maximum capacity \n";
        return nullptr;
    } 
    m_objectList.push_back({Feintgine::SpriteManager::Instance()->getSprite(spriteNameWithPacket), posOffset, scale, color, angle, depth});
    flagUpdate();
    return &m_objectList.back();
}

tAObject * F_CompositeObject::addAnimatedObject(const std::string & animFile,const std::string & defaultAnim, const glm::vec2 & posOffset, const glm::vec2 & scale, const Feintgine::Color & color, float angle, float depth)
{

    if(m_animatedObjectList.size() >= m_maxObject)
    {
        std::cout << "F_CompositeObject Warning, Reach Maximum Objects, We will stop adding instead of extend the cap and cause weird behavior, if you see this, adjust the maximum capacity \n";
        return nullptr;
    }

    tAObject tAnimatedObject;
    tAnimatedObject.animatedObject.init(animFile);
    tAnimatedObject.posOffset = posOffset;
    tAnimatedObject.scale = scale;
    tAnimatedObject.color = color;
    tAnimatedObject.angle = angle;
    tAnimatedObject.depth = depth;
    tAnimatedObject.animatedObject.playAnimation(defaultAnim);
    m_animatedObjectList.push_back(tAnimatedObject);
    flagUpdate();
    return &m_animatedObjectList.back();
}


void F_CompositeObject::draw(Feintgine::SpriteBatch & spriteBatch)
{
    if(m_type & ObjectTypes::TF_Sprite)
    {
        for (auto i = 0; i < m_objectList.size(); i++)
        {

            glm::vec4 desRect;
            desRect.x = (m_pos.x + m_objectList[i].posOffset.x ) - ((m_objectList[i].sprite.getDim().x * m_objectList[i].scale.x) / 2.0f); 
            desRect.y = (m_pos.y + m_objectList[i].posOffset.y ) - ((m_objectList[i].sprite.getDim().y * m_objectList[i].scale.y) / 2.0f);
            desRect.z = m_objectList[i].scale.x * m_objectList[i].sprite.getDim().x;
            desRect.w = m_objectList[i].scale.y * m_objectList[i].sprite.getDim().y;

            spriteBatch.draw(desRect, m_objectList[i].sprite.getUV(), m_objectList[i].sprite.getTexture().id, m_depth +  (m_objectList[i].depth * 0.1), m_objectList[i].color, ((m_angle / 57.2957795f) + m_objectList[i].angle) );
            // spriteBatch.draw();
            // m_objectList[i].sprite.draw(spriteBatch, m_pos + m_objectList[i].posOffset, m_objectList[i].scale, m_objectList[i].color, m_objectList[i].angle, m_objectList[i].depth);
        }
    }
    if(m_type & ObjectTypes::TF_AnimatedObject)
    {
        for (auto i = 0; i < m_animatedObjectList.size(); i++)
        {
            m_animatedObjectList[i].animatedObject.setPos(m_pos + m_animatedObjectList[i].posOffset);
            m_animatedObjectList[i].animatedObject.setScale(m_animatedObjectList[i].scale);
            m_animatedObjectList[i].animatedObject.setColor(m_animatedObjectList[i].color);
            m_animatedObjectList[i].animatedObject.setAngle((m_angle + m_animatedObjectList[i].angle) / 57.2957795f); // consider convert to degree
            m_animatedObjectList[i].animatedObject.setDepth(m_animatedObjectList[i].depth);
            m_animatedObjectList[i].animatedObject.draw(spriteBatch);
        }
    }
    if(m_type & ObjectTypes::TF_FramePanel)
    {
        m_framePanel.draw(spriteBatch);
    }
    
}

void F_CompositeObject::update(float deltaTime)
{
    if(m_type & ObjectTypes::TF_AnimatedObject)
    {
        for (auto i = 0; i < m_animatedObjectList.size(); i++)
        {
            m_animatedObjectList[i].animatedObject.update(deltaTime);
        }
    }
}

void F_CompositeObject::flagUpdate()
{
    if(m_objectList.size() > 0)
    {
        // bitwise add ObjectTypes::TEmptyObject
        m_type |= ObjectTypes::TF_Sprite;
    }
    else
    {
        m_type &= ~ObjectTypes::TF_Sprite;
    }
    if(m_animatedObjectList.size() > 0)
    {
        // bitwise add ObjectTypes::TAnimatedObject
        m_type |= ObjectTypes::TF_AnimatedObject;
    }
    else
    {
        m_type &= ~ObjectTypes::TF_AnimatedObject;
    }
}

void F_CompositeObject::addPanel(const std::string & borderPacket, float borderScale)
{
    m_framePanel.init(borderPacket, m_pos, m_dim,m_depth + 1.0f);
    m_framePanel.setScale(borderScale);
    m_framePanel.setAngle(m_angle);
    // m_framePanel.
    // flagUpdate();
    m_type |= ObjectTypes::TF_FramePanel;
}

void F_CompositeObject::addPanelCornerEmblem(const std::string & emblemSprite, int placeMask, int hideMask, const glm::vec2 & offset, float scale)
{
    m_framePanel.addCornerEmblem(emblemSprite, placeMask, hideMask, offset, scale, m_depth + 1.2f);
    m_framePanel.setAngle(m_angle);
}

void F_CompositeObject::addPanelLineEmblem(const std::string & emblemSprite, int placeMask, int hideMask, const glm::vec2 & offset, float scale)
{
    m_framePanel.addLineEmblem(emblemSprite, placeMask, hideMask, offset, scale, m_depth + 1.5f);
    m_framePanel.setAngle(m_angle);
}

}