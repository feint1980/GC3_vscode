#include "GuardianShield.h"



GuardianShield::GuardianShield()
{

	
}


GuardianShield::GuardianShield(const std::string & animationPath, const glm::vec2 & pos, float scale)
{
	m_animations.init(animationPath);
	m_pos = pos;
	m_scale = scale;

	m_animations.playAnimation("default");
	m_animations.setDepth(15.0f);
	m_animations.setScale(glm::vec2(m_scale));
	m_dim = m_animations.getDim() * m_scale;
	m_offsetPos = glm::vec2(0, -10);
}

GuardianShield::~GuardianShield()
{
}

void GuardianShield::init(const std::string & animationPath, const glm::vec2 & pos, float scale)
{
	m_animations.init(animationPath);
	m_pos = pos;
	m_scale = scale;
	
	m_animations.playAnimation("default");
	m_animations.setDepth(15.0f);
	m_animations.setScale(glm::vec2(m_scale));
	m_dim = m_animations.getDim() * m_scale;
	m_offsetPos = glm::vec2(0, -10);
	//std::cout << "init shield called \n";

}



void GuardianShield::update(float delta)
{
	m_animations.setPos(m_pos + m_offsetPos);
	m_animations.update(delta);
}

void GuardianShield::draw(Feintgine::SpriteBatch & spriteBatch)
{
	m_animations.draw(spriteBatch);
}

void GuardianShield::setPos(const glm::vec2 & pos)
{
	m_pos = pos;
	//std::cout << feint_common::Instance()->convertiVec2toString(m_pos) << "\n";
}

void GuardianShield::setOffsetPos(const glm::vec2 & pos)
{
	m_offsetPos = pos;
}

void GuardianShield::playAnimation(const std::string & animationName)
{
	m_animations.playAnimation(animationName);
	//std::cout << "play animationm " << animationName << "\n";
}
