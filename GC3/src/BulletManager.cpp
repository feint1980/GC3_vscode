#include "BulletManager.h"



BulletManager::BulletManager()
{
}


BulletManager::~BulletManager()
{
}

void BulletManager::spawnBullet(const glm::vec2 & pos, const Feintgine::F_Sprite & sprite,
	float speed, float angle, float accel, float maxSpeed, float delay)
{
	EnemyBulletBase * bullet = new EnemyBulletBase();
	bullet->init(pos, glm::vec2(1.0f), sprite, glm::vec2(speed), nullptr, 10);

	m_bullets.push_back(bullet);
}

void BulletManager::spawnBullet(const glm::vec2 & pos, const Feintgine::F_AnimatedObject & animObj, float speed, float angle, float accel, float maxSpeed, float delay)
{
	EnemyBulletBase * bullet = new EnemyBulletBase();
	bullet->init(pos, glm::vec2(1.0f), animObj, glm::vec2(speed), nullptr, 10);

	m_bullets.push_back(bullet);
}

void BulletManager::draw(Feintgine::SpriteBatch & spriteBatch)
{
	for (int i = 0; i < m_bullets.size(); i++)
	{
		m_bullets[i]->draw(spriteBatch);
	}
}

void BulletManager::update(float deltaTime)
{
	for (int i = 0; i < m_bullets.size(); i++)
	{
		m_bullets[i]->update(deltaTime);
	}
}

