#include "Philosopher.h"
#include <iostream>

void Philosopher::update(glm::vec2 bossPos)
{
	
	m_circle_angle += 0.025f;
	m_pos.x = bossPos.x + cos(m_circle_angle) * m_radius;
	m_pos.y = bossPos.y + sin(m_circle_angle) * m_radius;
}

void Philosopher::setCirCleAngle(float angle)
{
	m_circle_angle = angle;
}

void Philosopher::fayde_alpha(float speed)
{
	alphaTagPoint += speed;
	setAlpha(cos(alphaTagPoint + 1.0f) * 255);
}

void Philosopher::setCore(bool value)
{
	v_isCore = value;
}
