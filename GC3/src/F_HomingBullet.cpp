#include "F_HomingBullet.h"
#include "EnemyGuardian.h"


F_HomingBullet::F_HomingBullet()
{
}


F_HomingBullet::~F_HomingBullet()
{
}

F_BaseEnemy * F_HomingBullet::getNearstEnemy(const glm::vec2 & pos,  std::vector<F_BaseEnemy *> enemy)
{
	F_BaseEnemy * nearstEnemy = nullptr;
	
	float nearest = 1000.0f;

	for (int i = 0; i < enemy.size(); i++)
	{
		glm::vec2 disVec = enemy[i]->getPos() - pos;
		float distance = glm::length(disVec);
		if (!enemy[i]->isDeath())
		{
			if (distance < nearest)
			{
				nearest = distance;
				nearstEnemy = enemy[i];
				//std::cout << "found \n";
			}
		}
	}
	
	return nearstEnemy;
}


EnemyAmplifier * F_HomingBullet::getNearstAmplifier(const glm::vec2 & pos, std::vector<EnemyAmplifier *> enemy)
{
	EnemyAmplifier * nearstEnemy = nullptr;
	
	float nearest = 1000.0f;
	
	for (int i = 0; i < enemy.size(); i++)
	{
		glm::vec2 disVec = enemy[i]->getPos() - pos;
		float distance = glm::length(disVec);
		if (!enemy[i]->isDeath())
		{
			if (distance < nearest)
			{
				nearest = distance;
				nearstEnemy = enemy[i];

			}
		}
	}

	return nearstEnemy;
}

void F_HomingBullet::update(float deltaTime, std::vector<F_BaseEnemy *>  enemies,
	std::vector<EnemyGuardian *> guardians, std::vector<EnemyAmplifier *> amplifiers)
{
	
	if (m_isAlive)
	{
		m_lifeTime -= (0.03f * deltaTime);
		if (m_lifeTime < 0)
		{
			m_isAlive = false;
		}
	}	
	if (m_isAnimated)
	{
		m_animation.update(deltaTime);
		if (!m_animation.isPlaying())
		{
			m_isAlive = false;
		}
	}
	if (!isDone)
	{

		m_angle += 0.5 * deltaTime;
		if (m_isAnimated)
		{
			m_animation.setAngle(m_angle);
		}
		F_BaseEnemy * enemy = getNearstEnemy(m_pos, enemies);

		EnemyAmplifier * amplifier = getNearstAmplifier(m_pos, amplifiers);

		//F_BaseEnemy * enemy2 = getNearstEnemy(m_pos, gua);
		if (enemy)
		{
			direction = glm::normalize(enemy->getPos() - m_pos);
			//std::cout << "here \n";
		}
		else
		{
			direction = glm::vec2(0, 0.9f);
		}
		if (amplifier)
		{
			if (enemy)
			{
				if (glm::length(enemy->getPos() - m_pos) < glm::length(amplifier->getPos() - m_pos))
				{
					direction = glm::normalize(enemy->getPos() - m_pos);
				}
				else
				{
					direction = glm::normalize(amplifier->getPos() - m_pos);
				}

			}
			else
			{
				direction = glm::normalize(amplifier->getPos() - m_pos);
			}

		}
		else
		{
			if (!enemy)
			{
				direction = glm::vec2(0, 0.9f);
			}
			
		}

		m_pos += direction * 20.5f * deltaTime;// * (1 / (m_dims.x/14))  ; 	
		for (int i = 0; i < enemies.size(); i++)
		{
			if (checkColiderWithEmeny(*enemies[i]))
			{
				enemies[i]->takeDamage(m_damage);
				destroy();
				if (m_particleBatch)
				{
					float ranX = feint_common::Instance()->getRandomNum(-3.5f, 3.5f);
					float ranY = feint_common::Instance()->getRandomNum(-3.5f, 3.5f);
					glm::vec2 halfDim = enemies[i]->getDim() * 0.5f;
					m_particleBatch->addParticle(enemies[i]->getPos() - halfDim, glm::vec2(ranX, ranY), Feintgine::Color(255, 255, 255, 120), 1.4f);
				}
			}
		}
		// end of for loop
		for (int i = 0; i < guardians.size(); i++)
		{
			if (checkColiderWithGuardian(*guardians[i]))
			{
				guardians[i]->takeDamage(m_damage);
				destroy();
				if (m_particleBatch)
				{
					float ranX = feint_common::Instance()->getRandomNum(-3.5f, 3.5f);
					float ranY = feint_common::Instance()->getRandomNum(-3.5f, 3.5f);
					glm::vec2 halfDim = guardians[i]->getDim() * 0.5f;
					m_particleBatch->addParticle(guardians[i]->getPos() - halfDim, glm::vec2(ranX, ranY), Feintgine::Color(255, 255, 255, 120), 1.4f);
				}
			}
		}
		// end of for loop

		for (int i = 0; i < amplifiers.size(); i++)
		{
			if (checkColiderWithAmplifier(*amplifiers[i]))
			{
				amplifiers[i]->takeDamage(m_damage);
				destroy();
				if (m_particleBatch)
				{
					float ranX = feint_common::Instance()->getRandomNum(-3.5f, 3.5f);
					float ranY = feint_common::Instance()->getRandomNum(-3.5f, 3.5f);
					glm::vec2 halfDim = amplifiers[i]->getDim() * 0.5f;
					m_particleBatch->addParticle(amplifiers[i]->getPos() - halfDim, glm::vec2(ranX, ranY), Feintgine::Color(255, 255, 255, 120), 1.4f);
				}
			}
		}
		// end of for loop
	}
	
}



void F_HomingBullet::draw(Feintgine::SpriteBatch & spriteBatch)
{
	if (!m_isAnimated)
	{
		glm::vec4 desRect;
		desRect.x = m_pos.x - (m_sprite.getDim().x * m_scale.x) / 2.0f;
		desRect.y = m_pos.y - (m_sprite.getDim().y * m_scale.y) / 2.0f;
		desRect.z = m_sprite.getDim().x  * m_scale.x;
		desRect.w = m_sprite.getDim().y  * m_scale.y;
		spriteBatch.draw(desRect, m_sprite.getUV(), m_sprite.getTexture().id, m_depth, m_color, m_angle);
	}
	else
	{
		glm::vec2 additionalPos;
		//if (radToDegree(m_animation.getAngle() == 90))
		//{
		//additionalPos.x = (m_animation.getDim().x * 0.5f) - m_animation.getDim().y;
		//}


		m_animation.setPos(m_pos + additionalPos);
		//m_animation.setScale(glm::vec2(1.0));
		m_animation.draw(spriteBatch);
	}
}

void F_HomingBullet::destroy()
{
	if (m_isAnimated)
	{
		isDone = true;
		m_vel = glm::vec2(0, 0);
		m_animation.playAnimation("destroy", 1);
		m_scale *= 1.3f;
	}
}

