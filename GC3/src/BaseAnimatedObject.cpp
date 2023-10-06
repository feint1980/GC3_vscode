#include "BaseAnimatedObject.h"



BaseAnimatedObject::BaseAnimatedObject()
{

}


BaseAnimatedObject::BaseAnimatedObject(const glm::vec2 & pos, const std::string & animationPath)
{
	m_animation.init(animationPath);
	m_pos = pos;
	m_animation.setDepth(10);
	m_animation.playAnimation("idle");
}

void BaseAnimatedObject::draw(Feintgine::SpriteBatch & spriteBatch)
{
	m_animation.setPos(m_pos);

	m_animation.draw(spriteBatch);
}

void BaseAnimatedObject::update(float delta)
{
	m_animation.update(delta);
	m_pos += m_vel * delta;
}

BaseAnimatedObject::~BaseAnimatedObject()
{

}
