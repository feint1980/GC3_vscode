#pragma once
#include "EnemyBulletBase.h"


class BulletManager
{
public:
	BulletManager();
	~BulletManager();

	void spawnBullet(const glm::vec2 & pos, 
		const Feintgine::F_Sprite & sprite, float speed, float angle,
		float accel, float maxSpeed, float delay);

	void spawnBullet(const glm::vec2 & pos,
		const Feintgine::F_AnimatedObject & animObj, float speed, float angle,
		float accel, float maxSpeed, float delay);


	void draw(Feintgine::SpriteBatch & spriteBatch);

	void update(float deltaTime);

private:

	std::vector<EnemyBulletBase *> m_bullets;


};

