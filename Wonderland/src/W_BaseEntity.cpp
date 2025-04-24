#include "W_BaseEntity.h"

W_BaseEntity::W_BaseEntity()
{

}

W_BaseEntity::~W_BaseEntity()
{

}

void W_BaseEntity::init(const std::string & animPath, const glm::vec2 & pos)
{
    m_animations.init(animPath);
    m_pos = pos;
}

void W_BaseEntity::draw(Feintgine::SpriteBatch & spriteBatch)
{
    m_animations.setPos(m_pos);
    m_animations.draw(spriteBatch);
}

void W_BaseEntity::update(float deltaTime)
{
    m_animations.update(deltaTime);
}

void W_BaseEntity::playAnimation(const std::string & animationName, int time /*= -1*/)
{
    m_animations.playAnimation(animationName, time);
}