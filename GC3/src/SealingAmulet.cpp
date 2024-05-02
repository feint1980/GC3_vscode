#include "SealingAmulet.h"
#include "EnemyGuardian.h"



SealingAmulet::SealingAmulet()
{
	m_lifeTime = 40.0f;
}


SealingAmulet::~SealingAmulet()
{
}

void SealingAmulet::update(float deltaTime, std::vector<FairyBase *> enemies, 
	std::vector<EnemyGuardian *> guardians, std::vector<EnemyAmplifier *> amplifiers)
{

	if (m_animation.getCurrentAnimation())
	{
		if (m_animation.getCurrentAnimation()->getCurrentIndex() >= 0)
		{
			m_afterImageParticle.setScale(m_scale);
			m_afterImageParticle.update(deltaTime, m_animation.getCurrentAnimation()->getCurrentIndex(), m_angle);
		}
	}

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
		
		
		//std::cout << "yahd\n";
// 		m_angle += 0.5 * deltaTime;
		//m_angle = 
		
		F_BaseEnemy * enemy = getNearstEnemy(m_pos, enemies);

		EnemyGuardian * guardian = getNearstGuardians(m_pos, guardians);

		EnemyAmplifier * amplifier = getNearstAmplifier(m_pos, amplifiers);


// 		if (enemy)
// 		{
// 			direction = glm::normalize(enemy->getPos() - m_pos);
// 		}
// 		else
// 		{
// 			direction = glm::vec2(0, 0.9f);
// 		}
// 		if (guardian)
// 		{
// 			if (enemy)
// 			{
// 				if (glm::length(enemy->getPos() - m_pos) < glm::length(guardian->getPos() - m_pos))
// 				{
// 					direction = glm::normalize(enemy->getPos() - m_pos);
// 				}
// 				else
// 				{
// 					direction = glm::normalize(guardian->getPos() - m_pos);
// 				}
// 				
// 			}
// 			else
// 			{
// 				direction = glm::normalize(guardian->getPos() - m_pos);
// 			}
// 			
// 		}
// 		else
// 		{
// 			direction = glm::vec2(0, 0.9f);
// 		}

		switch (getNearestTypeID(enemy, guardian, amplifier))
		{
		case 0 : 
			direction = glm::vec2(0, 0.9f);
			break;
		case 1:
			direction = direction = glm::normalize(enemy->getPos() - m_pos);
			break;
		case 2:
			direction = glm::normalize(guardian->getPos() - m_pos);
			break;
		case 3:
			direction = glm::normalize(amplifier->getPos() - m_pos);
			break;
		}

		//direction = glm::vec2(0, 1.0f);
		m_angle = atan2(direction.y, direction.x) + degreeToRad(90);
		if (m_isAnimated)
		{
			m_animation.setAngle(m_angle);
		}
		m_pos += direction * 24.5f * deltaTime;// * (1 / (m_dims.x/14))  ; 	
		for (int i = 0; i < enemies.size(); i++)
		{
			if (checkColiderWithEmeny(*enemies[i]))
			{
				enemies[i]->takeDamage(m_damage);
				KanjiEffect kanjiEffect;
				kanjiEffect.init(Feintgine::SpriteManager::Instance()->getSprite("Amulet_effect/effect_disabled_prisoned.png"),
					enemies[i]->getPos(), m_color);
				m_kanjiEffectManager_p->addKanjiEffect(kanjiEffect);
				destroy();
				if (m_effectBatch)
				{
					m_effectBatch->addRippleEffectContinuos(&m_pos, .1f, 2.5f, -7.0f, 0.02f, 0.1f);
				}
				else
				{
					std::cout << "no effect batch registered (SealingAmulet) \n";
				}
				enemies[i]->clearEvent();
				enemies[i]->loadState("Disabled_sealed");
				//std::cout << " disabled \n";
				if (m_particleBatch)
				{
					glm::vec2 halfDim = enemies[i]->getDim() * 0.5f;
					for (int f = 0; f < 3; f++)
					{
						float ranX = feint_common::Instance()->getRandomNum(-3.5f, 3.5f);
						float ranY = feint_common::Instance()->getRandomNum(-3.5f, 3.5f);
						
						m_particleBatch->addParticle(enemies[i]->getPos() - halfDim,
							glm::vec2(ranX, ranY), Feintgine::Color(255, 255, 255, 120), 1.4f);
					}
				}
			}
		}
	// end of for loop

		for (int i = 0; i < guardians.size(); i++)
		{
			if (checkColiderWithGuardian(*guardians[i]))
			{
				//guardians[i]->takeDamage(m_damage);
				KanjiEffect kanjiEffect;
				kanjiEffect.init(Feintgine::SpriteManager::Instance()->getSprite("Amulet_effect/effect_disabled_prisoned.png"),
					guardians[i]->getPos(), m_color);
				m_kanjiEffectManager_p->addKanjiEffect(kanjiEffect);
				destroy();
				if (m_effectBatch)
				{
					m_effectBatch->addRippleEffectContinuos(&m_pos, .1f, 2.5f, -7.0f, 0.02f, 0.1f);
				}
				else
				{
					std::cout << "no effect batch registered (SealingAmulet) \n";
				}
				guardians[i]->setDisabled(true);
				guardians[i]->clearEvent();
				guardians[i]->loadState("Disabled_sealed");
				if (m_particleBatch)
				{
					glm::vec2 halfDim = guardians[i]->getDim() * 0.5f;
					for (int f = 0; f < 3; f++)
					{
						float ranX = feint_common::Instance()->getRandomNum(-3.5f, 3.5f);
						float ranY = feint_common::Instance()->getRandomNum(-3.5f, 3.5f);

						m_particleBatch->addParticle(guardians[i]->getPos() - halfDim,
							glm::vec2(ranX, ranY), Feintgine::Color(255, 255, 255, 120), 1.4f);
					}
				}
			}
		}
		// end of for loop

		for (int i = 0; i < amplifiers.size(); i++)
		{
			if (checkColiderWithAmplifier(*amplifiers[i]))
			{
				//guardians[i]->takeDamage(m_damage);
				KanjiEffect kanjiEffect;
				kanjiEffect.init(Feintgine::SpriteManager::Instance()->getSprite("Amulet_effect/effect_disabled_prisoned.png"),
					amplifiers[i]->getPos(), m_color);
				m_kanjiEffectManager_p->addKanjiEffect(kanjiEffect);
				destroy();
				if (m_effectBatch)
				{
					m_effectBatch->addRippleEffectContinuos(&m_pos, .1f, 2.5f, -7.0f, 0.02f, 0.1f);
				}
				else
				{
					std::cout << "no effect batch registered (SealingAmulet) \n";
				}
				amplifiers[i]->setDisabled(true);
				amplifiers[i]->clearEvent();
				amplifiers[i]->loadState("Disabled_sealed");
				if (m_particleBatch)
				{
					glm::vec2 halfDim = amplifiers[i]->getDim() * 0.5f;
					for (int f = 0; f < 3; f++)
					{
						float ranX = feint_common::Instance()->getRandomNum(-3.5f, 3.5f);
						float ranY = feint_common::Instance()->getRandomNum(-3.5f, 3.5f);

						m_particleBatch->addParticle(amplifiers[i]->getPos() - halfDim,
							glm::vec2(ranX, ranY), Feintgine::Color(255, 255, 255, 120), 1.4f);
					}
				}
			}
		}
		// end of for loop
	}
}

void SealingAmulet::initParticle()
{
	m_afterImageParticle.init(&m_pos, &m_animation,&m_color,0.125f, 10);
	m_afterImageParticle.setTraceLifeTime(1.2f);
	
}

void SealingAmulet::setTimeLife(float ff)
{
	m_lifeTime = ff;
	isDone = false;
	//m_scale = glm::vec2(1.0f);
	m_vel = glm::vec2(0, 1);
	
}

EnemyGuardian * SealingAmulet::getNearstGuardians(const glm::vec2 & pos, std::vector<EnemyGuardian *> guardians)
{
	EnemyGuardian * nearstEnemy = nullptr;

	float nearest = 1000.0f;

	for (int i = 0; i < guardians.size(); i++)
	{
		glm::vec2 disVec = guardians[i]->getPos() - pos;
		float distance = glm::length(disVec);
		if (!guardians[i]->isDeath())
		{
			if (distance < nearest)
			{
				nearest = distance;
				nearstEnemy = guardians[i];

			}
		}
	}

	return nearstEnemy;
}

void SealingAmulet::destroy()
{
	if (m_isAnimated)
	{
		m_impactSound.playInChannel(0,3);
		isDone = true;
		m_vel = glm::vec2(0, 0);
		m_animation.playAnimation("end", 1);
		m_scale *= 1.3f;
	}
}

void SealingAmulet::setIsDone(bool val)
{
	isDone = val;
	m_afterImageParticle.clear();
}

void SealingAmulet::draw(Feintgine::SpriteBatch & spriteBatch)
{
	//std::cout << "draw \n";
	//F_HomingBullet::draw(spriteBatch);

// 	if (!m_isAnimated)
// 	{
// 		glm::vec4 desRect;
// 		desRect.x = m_pos.x - (m_sprite.getDim().x * m_scale.x) / 2.0f;
// 		desRect.y = m_pos.y - (m_sprite.getDim().y * m_scale.y) / 2.0f;
// 		desRect.z = m_sprite.getDim().x  * m_scale.x;
// 		desRect.w = m_sprite.getDim().y  * m_scale.y;
// 		spriteBatch.draw(desRect, m_sprite.getUV(), m_sprite.getTexture().id, m_depth, m_color, m_angle);
// 	}
// 	else
// 	{
		glm::vec2 additionalPos;
		//if (radToDegree(m_animation.getAngle() == 90))
		//{
		//additionalPos.x = (m_animation.getDim().x * 0.5f) - m_animation.getDim().y;
		//}


		m_animation.setPos(m_pos + additionalPos);
		//m_animation.setScale(glm::vec2(1.0));
		m_animation.draw(spriteBatch);
// 	}

	m_afterImageParticle.draw(spriteBatch);
}

void SealingAmulet::registerKanjiEffectManager(KanjiEffectManager * effectManager)
{
	m_kanjiEffectManager_p = effectManager;
}

void SealingAmulet::registerEffectBatch(Feintgine::EffectBatch * effectBatch)
{

	m_effectBatch = effectBatch;

}

void SealingAmulet::registerAudioEngine(Feintgine::AudioEngine * audioEngine)
{
	m_impactSound = audioEngine->loadSoundEffect("Sounds/sfx/sealing_impact.wav");
	m_impactSound.setVolume(24);
}


void SealingAmulet::setPos(const glm::vec2 & pos)
{
	m_pos = pos;
}

int SealingAmulet::getNearestTypeID(F_BaseEnemy * enemy, EnemyGuardian * guardian, EnemyAmplifier * amplifier)
{
	float t_distance = 1000.0f;
	int returnValue = 0;
	float r_distance;// = glm::length(enemy->getPos() - m_pos);
	if (enemy)
	{
		r_distance = glm::length(enemy->getPos() - m_pos);
		if (r_distance < t_distance)
		{
			t_distance = r_distance;
			returnValue = 1;
		}
	}
	if (guardian)
	{
		r_distance = glm::length(guardian->getPos() - m_pos);
		if (r_distance < t_distance)
		{
			t_distance = r_distance;
			returnValue = 2;
		}

	}
	if (amplifier)
	{
		r_distance = glm::length(amplifier->getPos() - m_pos);
		if (r_distance < t_distance)
		{
			t_distance = r_distance;
			returnValue = 3;
		}

	}
	return returnValue;
}
