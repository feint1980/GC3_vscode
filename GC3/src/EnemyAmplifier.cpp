#include "EnemyAmplifier.h"




EnemyAmplifier::EnemyAmplifier()
{
	m_typeID = 5;

	m_isLeft = true;
}


EnemyAmplifier::~EnemyAmplifier()
{

}
void EnemyAmplifier::decideAnimation(const glm::vec2 & pos)
{

	if (!m_isDeath)
	{
		animationLimitCounter = 1.3f;

		if (pos.x < oldPos.x)
		{
			state = ANIM_LEFT;
		}
		else if (pos.x > oldPos.x)
		{

			state = ANIM_RIGHT;
		}
		else if (pos.x == oldPos.x)
		{

			state = ANIM_CENTER;
		}

		if (!m_isDisabled)
		{

			if (m_isLeft)
			{
				if (m_pos.x <= (-1.0f * linkBorderX) + 10)
				{
					state = ANIM_CENTER;
				}

			}
			else
			{
				if (m_pos.x >= (linkBorderX)-10)
				{
					state = ANIM_CENTER;
				}
			}

			oldPos = pos;
			if (currentState != state)
			{

				currentState = state;
				animationLimitCounter = 1.0f;
				setMovementAnim(currentState);
			}
		}
	}

}

void EnemyAmplifier::setDisabled(bool value)
{
	m_isDisabled = value;
	//direction = glm::vec2(0, -4.0f);
	//m_vel = glm::vec2(0, 0);
}

void EnemyAmplifier::setCreateFlag(bool val)
{
	m_createFlag = val;
}

void EnemyAmplifier::update(float deltaTime, std::vector<EnemyAmplifier *> enemy, const F_Player & player)
{

	if (animationLimitCounter <= 0)
	{
		decideAnimation(m_pos);
	}
	else
	{
		animationLimitCounter -= 0.1f * deltaTime;
	}

	if (isAnimated)
	{
		m_animation.update(deltaTime);
		m_animation.setPos(m_pos);
	}
	if (m_isDeath)
	{
		//playAnim("death", 1);
		m_animation.rotate(0.9f * deltaTime);
		if (!m_animation.isPlaying())
		{
			m_isAlive = false;
		}

	}
	else
	{
		m_pos += m_vel * deltaTime;
		m_intervalTime += m_intervalRate * deltaTime;


		if (!m_isDisabled)
		{
			if (!m_linkPartner)
			{
				if (m_intervalTime > m_intervalValue)
				{
					m_intervalTime = 0.0f;
					handleAI(deltaTime, enemy);
				}
				if (m_linkingStatus > 0)
				{
					m_isDisabled = true;
					clearEvent();
					loadState("Disabled_sealed");
				}
			}
			else
			{

				if (!m_linkPartner->isAlive())
				{
					m_isDisabled = true;
					clearEvent();
					std::cout << "partner died \n";
					loadState("Disabled_sealed");
				}
				if (m_linkPartner->isDisabled() )
				{
					m_isDisabled = true;
					clearEvent();
					loadState("Disabled_sealed");
				}
				else
				{
					executeLink(deltaTime);
				}


			}
		}


		// 	if (m_linkingStatus > 0 && !m_linkPartner)
		// 	{
		// 		//m_isDisabled = true;
		// 		
		// 		//m_animation.playAnimation("idle");
		// 	}
		// 	if (m_linkPartner && m_linkPartner->m_isDisabled)
		// 	{
		// 		//m_isDisabled = true;
		// 		
		// 		//m_animation.playAnimation("idle");
		// 	}

	}
	timer();
	
}


EnemyAmplifier * EnemyAmplifier::getNearestPartner(std::vector<EnemyAmplifier * > enemy)
{

	EnemyAmplifier * nearstEnemy = nullptr;

	float nearest = 1000.0f;

	for (int i = 0; i < enemy.size(); i++)
	{
		if (enemy[i] != this && m_typeID == 5)
		{
			//std::cout << "looking for linking partner \n";
			glm::vec2 disVec = enemy[i]->getPos() - m_pos;
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
	}

	return nearstEnemy;

}

void EnemyAmplifier::handleAI(float deltaTime, std::vector<EnemyAmplifier *> enemy)
{
	//std::cout << "handling AI \n";
	EnemyAmplifier * partnerP = nullptr;
	if (!m_linkPartner)
	{
		partnerP = getNearestPartner(enemy);
		if (partnerP)
		{
			if (!partnerP->m_isDisabled)
			{
				m_linkPartner = partnerP;
			}
		}
		
	}
	else
	{
		//linkBreak = true;
	}
}

void EnemyAmplifier::executeLink(float deltaTime)
{
	//std::cout << "executeLink \n";
	if (m_isDeath)
	{
		m_isDisabled = false;
		return;
	}
	if (!m_isDisabled)
	{

		if (m_linkPartner)
		{

			if (m_linkPartner->isDeath())
			{
				clearEvent();

				loadState("Disabled_sealed");
			}

			glm::vec2 speed;
			switch (m_linkingStatus)
			{
				// phase 0 : determine if this amplifier is left or right
			case 0:
			{
				//std::cout << this << " on phase 0 \n";
				if (m_pos.x < m_linkPartner->getPos().x)
				{
					//std::cout << this << " is left \n";
					m_isLeft = true;
				}
				else
				{
					//std::cout << this << " is right \n";
					m_isLeft = false;
				}
				m_linkingStatus = 1;
			}
			break;

			// phase 1: after determine amplifier is left or right, action accordingly
			case 1:
			{
				//std::cout << this << " on phase 1 \n";
				float offsetValue = 60;
				if (m_isLeft)
				{
					offsetValue *= -1.0f;
				}
				glm::vec2 offsetPos = glm::vec2(offsetValue, 0);
				//m_pos = protectingTarget->getPos() + offsetPos;
				direction = glm::normalize(m_linkPartner->getPos() - m_pos - offsetPos);
				float t_distance = glm::length(m_linkPartner->getPos() - m_pos - offsetPos);

				// determine left/right
				//std::cout << "phase 1 " << t_distance << "\n";
				if (t_distance > 40.0f)
				{
					speed = glm::vec2(6.5f);
				}
				else if (t_distance > 1.0f)
				{
					speed = glm::vec2(0.5f);
					if (!m_createFlag2)
					{
						m_createFlag = false;
						m_createFlag2 = true;
					}

				}
				else
				{
					m_linkingStatus = 2;
				}

			}
			break;

			case 2:
			{

// 				if (m_isLeft)
// 				{
// 					m_createFlag = false;
// 				}
				//std::cout << "phase 2 start \n";
				m_phase2Timer += m_intervalRate* deltaTime;
				if (m_phase2Timer > 5.0f)
				{
					m_linkingStatus = 3;
				}
			}
			break;
			case 3:
			{
				float xDestination = linkBorderX;
				float yDestination = linkBorderY;
				if (m_isLeft)
				{
					xDestination *= -1.0f;
				}

				direction = glm::normalize(glm::vec2(xDestination, yDestination) - m_pos);
				//float t_distance = glm::length(glm::vec2(xDestination, yDestination) - m_pos);
				speed = glm::vec2(3.5f);

			}
			break;

			default:
				break;
			}

			//if (!m_isDisabled)
			//{
				m_vel = direction * speed;
				/*speed = glm::vec2(0);*/
			//}
		}
	}
	else
	{
		clearEvent();

		loadState("Disabled_sealed");
	}
	
}
