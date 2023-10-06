#include "LivingLabel.h"



LivingLabel::LivingLabel()
{
}


LivingLabel::~LivingLabel()
{
}

void LivingLabel::create(const std::wstring & message, const glm::vec2 &pos, const glm::vec2 & vel, const Feintgine::Color & color)
{
	m_message = message;
	m_pos = pos;
	m_vel = vel;
	m_color = color;
}

void LivingLabel::setPos(const glm::vec2 & pos)
{
	m_pos = pos;
}

void LivingLabel::setVel(const glm::vec2 & vel)
{
	m_vel = vel;
}

void LivingLabel::draw(TextRenderer * textRenderer)
{
	textRenderer->renderBorderText(*GlobalValueClass::Instance()->savedCamera, m_message, m_pos, 
	m_color, m_scale, ALIGN_FT_CENTER);
	if (!set)
	{
		set = true;
		totalWidth = textRenderer->getTotalScale();
	}
}

void LivingLabel::update(float deltaTime)
{
	if (lifeTime > 0)
	{
		m_color.a = lifeTime;
		lifeTime -= liveTime * deltaTime;
	}
}

void LivingLabel::setScale(float scale)
{
	m_scale = scale;
}
