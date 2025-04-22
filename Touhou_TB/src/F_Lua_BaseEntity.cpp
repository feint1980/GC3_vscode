#include "F_Lua_BaseEntity.h"

F_Lua_BaseEntity::F_Lua_BaseEntity()
{

}

F_Lua_BaseEntity::~F_Lua_BaseEntity()
{

}

void F_Lua_BaseEntity::init(Slot * slot, const std::string & animationPath,const std::string & portraitPath , const glm::vec2 & scale)
{

    m_currentSlot = slot;
    m_moveTargetSlot = nullptr;
    m_scale = scale;

    m_animation.init(animationPath, m_scale);
    m_animation.playAnimation("idle");
    m_yOffset = m_animation.getDim().y * 0.5f;

    m_pos = m_currentSlot->getPos();
    m_pos.y += m_yOffset;
    m_isActive = false;

    m_portrait = new EmptyObject();
    m_portrait->init(Feintgine::ResourceManager::getTexture(portraitPath), glm::vec2(0),glm::vec2(100,100),Feintgine::Color(255, 255, 255, 255));
    m_portrait->setDepth(22);
}

void F_Lua_BaseEntity::setPos(const glm::vec2 & pos)
{
    m_pos = pos;
}

void F_Lua_BaseEntity::playAnimation(const std::string & animationName, int time)
{
    // std::cout << "entity play animation " << animationName <<  " " << time << std::endl; 
    m_animation.playAnimation(animationName, time);
}

bool F_Lua_BaseEntity::isAnimationStoped() const
{
    return  m_animation.isPlaying() == false;
}

void F_Lua_BaseEntity::setActive(bool value)
{
    m_isActive = value;
}
void F_Lua_BaseEntity::draw(Feintgine::SpriteBatch & spriteBatch)
{

    m_animation.setScale(m_scale);
    m_animation.setPos(m_pos);
    m_animation.draw(spriteBatch);

    if(m_portrait)
    {
        m_portrait->draw(spriteBatch);
    }
}

void F_Lua_BaseEntity::setTargetSlot(Slot * slot)
{
    m_moveTargetSlot = slot;
}

void F_Lua_BaseEntity::update(float deltaTime)
{
    m_animation.update(deltaTime);
}

void F_Lua_BaseEntity::setAttribute(const std::string & attributeName, int value)
{
    m_characterDesc.setAttribute(attributeName, value);
}

void F_Lua_BaseEntity::setAttribute(const std::string & attributeName, const std::string & value)
{
    m_characterDesc.setAttribute(attributeName, value);
}

float F_Lua_BaseEntity::getFloatAttributeByName(const std::string & attributeName)
{
    return m_characterDesc.getFloatAttributeByName(attributeName);
}

std::string F_Lua_BaseEntity::getStrAttributeByName(const std::string & attributeName)
{
    return m_characterDesc.getStrAttributeByName(attributeName);
}

void F_Lua_BaseEntity::setAttribute(Attribute attribute, const std::string & value)
{
    m_characterDesc.setAttribute(attribute, value);
}
void F_Lua_BaseEntity::setAttribute(Attribute attribute, float value)
{
    m_characterDesc.setAttribute(attribute, value);
}