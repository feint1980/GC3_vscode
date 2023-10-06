#pragma once
#include "LightBatch.h"
#include "F_BaseEnemy.h"
#include "EnemyBulletBase.h"
class F_Marisa_Laser_trail
{
public:
	F_Marisa_Laser_trail();
	~F_Marisa_Laser_trail();


	void drawLight(Feintgine::LightBatch & lightBatch);

	void update(float deltaTime, std::vector<F_BaseEnemy *>  enemy,
		std::vector<EnemyBulletBase * > bullets);
	void updateState(float deltaTime);

	void spawn(const glm::vec2 & pos, const glm::vec3 & attenuation,  int colorFlag, Feintgine::Color color);

	bool isRemoved() const { return m_isRemoved; }

	void setAngle(float angle);

private:

	bool m_isVisible = false;
	bool m_isSwitchHappen = false;

	glm::vec2 m_pos;
	glm::vec3 m_attenuation;
	glm::vec3 t_attenuation;
	Feintgine::Color m_color;
	float m_lifeTime;
	float m_angle;
	float maxColorVal = 0.6f;
	float minColorVal = -0.0001f;

	float m_attenuationScale = 0.0f;

	bool m_isRemoved = false;

	int m_colorFlag;
	
};

