#include "Yin_Yang_Orb_Ex.h"

const float LIFE_TIME_RATE = 0.1f;
const float ALPHA_MULTIPLIER = 1.0f;

Yin_Yang_Orb_Ex::Yin_Yang_Orb_Ex()
{

	m_lightColor = glm::vec3(0.7f, 0.7f, 1.0f);
}


Yin_Yang_Orb_Ex::~Yin_Yang_Orb_Ex()
{

}

void Yin_Yang_Orb_Ex::registerEffectBatch(Feintgine::EffectBatch * effectBatch)
{
	m_effectBatch = effectBatch;
}

void Yin_Yang_Orb_Ex::update(float deltaTime, std::vector<F_BaseEnemy *>  enemy, std::vector<EnemyBulletBase * > bullets)
{
	m_lifeTime -= LIFE_TIME_RATE * deltaTime;

	m_pos += m_vel * deltaTime;


	suckScale = 1.2f;

	if (m_lifeTime < 8.0f)
	{
		suckScale = 2.8f;
	}
	if (m_lifeTime < 4.0f)
	{
		suckScale = 0.1f;
	}


	if (m_lifeTime > 4.0f)
	{
		if (m_animation.getCurrentAnimation())
		{
			m_dim = m_animation.getCurrentAnimation()->getAnims()[m_animation.getCurrentAnimation()->getCurrentIndex()].sprite.getDim();
		}
	}
	else
	{
		m_dim *= m_lifeTime * deltaTime *0.25f;
	}

	if (m_isVisible)
	{

		for (auto i = 0; i < bullets.size(); i++)
		{

			if (checkColliderWithEnemyBulletOuter(*bullets[i]))
			{
				glm::vec2 direction = glm::normalize(bullets[i]->getPos() - m_pos);
				if (m_lifeTime > 8.0f)
				{
					bullets[i]->setVel(-direction * 1.4f);
				}
				else if (m_lifeTime > 1.0f)
				{

					bullets[i]->setVel(-direction * 9.4f);
					bullets[i]->setDisabled(true);
					bullets[i]->setLifeTime(m_lifeTime * 0.05f);
				}

			}

			if (checkColliderWithEnemyBullet(*bullets[i]))
			{
				bullets[i]->setLifeTime(-1.0f);

			}
		}
	}
	if (m_isAlive)
	{

		for (auto i = 0; i < enemy.size(); i++)
		{

			if (checkColliderWithEnemy(*enemy[i]))
			{
				//std::cout << "deal dmg \n";
				enemy[i]->takeDamage(m_dmg *deltaTime, false);
			}
		}


		if (m_pos.y > 275.0f)
		{
			m_isAlive = false;
			//std::cout << "is out \n";
			m_animation.playAnimation("end", 1);
			m_animationFront.playAnimation("end", 1);
			m_vel *= 0.6f * deltaTime;
			m_lifeTime = 8.0f;
			if (m_effectBatch)
			{
				m_effectBatch->stopRippleEffect(&m_pos);
			}
		}

		if (m_lifeTime > 25.0f)
		{

			m_attentionua += 1.3f * deltaTime;
			m_lifeTime += LIFE_TIME_RATE * deltaTime;
			m_angle -= 0.025f * deltaTime;
			m_animation.setAngle(m_angle);
			m_animationFront.setAngle(m_angle);

		}
		if (m_lifeTime < 10)
		{
			m_attentionua += 1.5f * deltaTime;
		}
	}
	else
	{
		if (!m_animation.isPlaying())
		{

			m_isVisible = false;
			m_isPeak = false;
			m_afterImageParticle.clear();

		}
		if (m_lifeTime < 5.0f)
		{
			if (!isFinished)
			{
				if (m_deathCallback)
				{
					m_deathCallback();
				}
				//std::cout << "finished \n";
				m_endSound.playInChannel(0, 2);
				isFinished = true;
			}
		}
	}

	if (m_isVisible)
	{
		if (m_lifeTime < 7.5f)
		{
			m_attentionua -= 2.2f * deltaTime;
			colorRate -= 0.05f * deltaTime;
			t_color = glm::vec4(colorRate, colorRate, colorRate, colorRate);
			m_animationFront.setColor(t_color);
		}
		if (m_lifeTime < 6.5f)
		{

			m_animation.setAlpha(m_lifeTime * ALPHA_MULTIPLIER);

		
		}
		if (m_lifeTime < 29 && m_lifeTime > 8.0f)
		{
			if (m_animation.getCurrentAnimation())
			{
				if (m_animation.getCurrentAnimation()->getCurrentIndex() != -1)
				{
					m_afterImageParticle.update(deltaTime, m_animation.getCurrentAnimation()->getCurrentIndex(), m_angle);
				}
			}
		}
		if (m_lifeTime > 3.5f)
		{
			m_animation.update(deltaTime);
			m_animationFront.update(deltaTime);
		}
		else
		{
			m_animation.getCurrentAnimation()->stop();
			m_animationFront.getCurrentAnimation()->stop();
		}



	}
}
