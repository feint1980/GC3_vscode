#pragma once
#include <string.h>
#include "GlobalValueClass.h"
#include <TextRenderer.h>
class LivingLabel
{
public:
	LivingLabel();
	~LivingLabel();

	void create(const std::wstring & message, const glm::vec2 &pos, const glm::vec2 & vel,const Feintgine::Color & color);
	void setPos(const glm::vec2 & pos);
	void setVel(const glm::vec2 & vel);

	virtual void draw(TextRenderer * textRenderer);

	virtual void update(float deltaTime);

	bool isAlive()const { return lifeTime > 0; }

	void setScale(float scale);

	protected:

	std::wstring m_message;
	glm::vec2 m_pos;
	glm::vec2 m_vel;
	Feintgine::Color m_color;
	float lifeTime = 1.0f;
	float liveTime = 0.004f;
	float m_scale = 1.0f;
	float totalWidth = 0;
	bool set = false;


};

