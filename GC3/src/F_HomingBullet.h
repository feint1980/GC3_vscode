#pragma once
#include "F_BulletBase.h"
#include "F_BaseEnemy.h"
#include <iostream>
#include <feint_common.h>



//float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/X));
class F_HomingBullet : public F_BulletBase
{
public:
	F_HomingBullet();
	~F_HomingBullet();

	F_BaseEnemy * getNearstEnemy(const glm::vec2 & pos, std::vector<FairyBase *> enemy);

	EnemyAmplifier * getNearstAmplifier(const glm::vec2 & pos, std::vector<EnemyAmplifier *> enemy);
	virtual void update(float deltaTime, std::vector<FairyBase *> enemy) override;

	virtual void draw(Feintgine::SpriteBatch & spriteBatch);

	void destroy();

protected:
	F_BaseEnemy * m_enemy;
	//float m_damage = 5.0f;

	bool isDone = false;

	glm::vec2 direction = glm::vec2(1);
	glm::vec2 m_vel = glm::vec2(0, 10);
	//glm::vec2 direction;

};

