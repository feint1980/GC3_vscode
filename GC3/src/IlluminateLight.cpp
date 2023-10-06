#include "IlluminateLight.h"



IlluminateLight::IlluminateLight()
{
}


IlluminateLight::~IlluminateLight()
{
}

void IlluminateLight::create(glm::vec2 pos, glm::vec4 color, glm::vec3 attenuation, float radius)
{
	m_pos = pos;
	m_attenuation = attenuation;
	m_color = color;
	m_radius = radius;
}

void IlluminateLight::setPos(glm::vec2 pos)
{
	m_pos = pos;
}

void IlluminateLight::setAttenuation(glm::vec3 attenuation)
{
	m_attenuation = attenuation;
}

void IlluminateLight::setColor(glm::vec4 color)
{
	m_color = color;
}

void IlluminateLight::setRadius(float radius)
{
	m_radius = radius;
}
