#pragma once
#include "F_Sprite.h"

#include <LightBatch.h>
class F_MasterSpark_Wave
{
public:
	F_MasterSpark_Wave();
	~F_MasterSpark_Wave();

	void draw(Feintgine::SpriteBatch & spriteBatch);
	void init(const glm::vec2 & pos, const glm::vec2 & scale, const Feintgine::F_Sprite & textureName,
		const Feintgine::Color & color);

	void drawLight(Feintgine::LightBatch & lightBatch);

	void update(float deltaTime);

	void handleScale(float deltaTime);

	glm::vec2 rotatePoint(const glm::vec2& pos, float angle);

	bool isAlive() const { return m_isAlive; }

	void setAngle(float angle);

private :


	glm::vec3 m_attentionua = glm::vec3(10.0f, 25.5f, 30.0f);

	bool m_isVisible = true;
	bool m_isSwitchHappen = false;
	bool m_isSwitchSizeHappen = false;

	bool m_isAlive = false;

	Feintgine::F_Sprite m_sprite;

	//float m_lifeTime = 5.0f;
		
	glm::vec2 m_scale;

	glm::vec2 t_scale;

	glm::vec2 m_pos;

	glm::vec4 desRect;

	Feintgine::Color m_color = Feintgine::Color(255, 255, 255, 255);

	float m_angle = 0.0;

	glm::vec2 m_vel = glm::vec2(0, 37);

	float m_tScaleMax = 2.9f;

	float maxColorVal = 1.0f;
	float minColorVal = -0.0001f;

	float m_lifeTime = 2.0f;
};

