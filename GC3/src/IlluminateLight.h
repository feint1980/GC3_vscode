#pragma once
#include <glm/glm.hpp>
class IlluminateLight
{
public:
	IlluminateLight();
	~IlluminateLight();

	glm::vec2 getPos() const { return m_pos; }
	glm::vec3 getAttenuation() const { return m_attenuation; }
	glm::vec4 getColor() const { return m_color; }
	float getRadius() const { return m_radius; }


	void create(glm::vec2 pos, glm::vec4 color, glm::vec3 attenuation, float radius);

	void setPos(glm::vec2 pos);
	void setAttenuation(glm::vec3 attenuation);
	void setColor(glm::vec4 color);
	void setRadius(float radius);

private:


	glm::vec2 m_pos;
	glm::vec4 m_color;
	glm::vec3 m_attenuation;
	float m_radius;


};

