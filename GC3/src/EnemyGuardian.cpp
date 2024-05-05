#include "EnemyGuardian.h"


//const int BORDER = 350;
EnemyGuardian::EnemyGuardian()
{

	m_internal_ID = GUARDIAN;
	m_pos = glm::vec2(0.0f, 1200.0f);
}


EnemyGuardian::~EnemyGuardian()
{
	
}



void EnemyGuardian::update(float deltaTime, std::vector<FairyBase *> enemy, const F_Player & player)
{
//	


// 	//std::cout << "update called \n";
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

		m_animation.rotate(0.9f * deltaTime);
		if (!m_animation.isPlaying())
		{
			m_isAlive = false;
		}
	}

// 	if (m_isMoveBerzier)
// 	{

// // 		m_perc = berzierRate;
// // 		berzierRate += 0.01f * deltaTime;
// // 		m_vel = glm::normalize(getBerzierPos(m_start, m_inter, m_des, m_perc)) * m_berzierSpeed;
// // 		m_vel.y = -m_vel.y;
// 	}

	if (m_shield)
	{
		m_shield->setPos(m_pos);
		m_shield->update(deltaTime);
		
	}
	m_intervalTime += m_intervalRate * deltaTime;

	if (!m_isDisabled)
	{

		if (m_intervalTime > m_intervalValue)
		{
			m_intervalTime = 0.0f;
			decideStrat(deltaTime, enemy, player);
		}
		glm::vec2 speed;
		if (protectingTarget)
		{
			//std::cout << "protecting target is " << protectingTarget->getInternalID() << "\n";
			glm::vec2 offsetPos = glm::vec2(0, 60);
			//m_pos = protectingTarget->getPos() + offsetPos;
			direction = glm::normalize(protectingTarget->getPos() - m_pos - offsetPos);
			float t_distance = glm::length(protectingTarget->getPos() - m_pos - offsetPos);

			if (t_distance > 70.0f)
			{
				speed = glm::vec2(20.5f);
			}

			if (t_distance > 10.0f)
			{
				speed = glm::vec2(6.5f);
			}
			else
			{
				speed = glm::vec2((protectingTarget->getVel().x + protectingTarget->getVel().y) * 0.05f);
			}

		}
		else
		{
			//std::cout << "no target \n";
			direction = glm::normalize(glm::vec2(0, 0) - m_pos);
			speed = glm::vec2(2.5f);

		}
		//std::cout << "speed " << feint_common::Instance()->convertVec2toString(speed) << "\n";
		//std::cout << "direction " << feint_common::Instance()->convertVec2toString(direction) << "\n";
		m_vel = direction * speed;
		//std::cout << "mvel " << feint_common::Instance()->convertVec2toString(m_vel) << "\n";

		m_pos += m_vel * deltaTime;

 	}
// 	//std::cout << abs(m_vel.x) << "\n";
// 	//m_pos +=  direction * speed * deltaTime;// * (1 / (m_dims.x/14))  ; 	
	
// 	std::cout << "mpos " << feint_common::Instance()->convertVec2toString(m_pos) << "\n";

 	timer();
}




void EnemyGuardian::decideStrat(float deltaTime, std::vector<FairyBase *> enemy
, const F_Player & player)
{
	protectingTarget = nullptr;//getHighestPriorityEnemy(enemy,player);



	FairyBase * p_enemy = getHighestPriorityEnemy(enemy, player);


//	EnemyAmplifier * p_amplifier = getHighestPriorityAmplifier(enemy, player);

	if (p_enemy)
	{
		protectingTarget = p_enemy;
		//std::cout << "foudn protecting target \n";
		direction = glm::normalize(p_enemy->getPos() - m_pos);
	}
	else
	{
		direction =glm::vec2(0);
	}

	// if (p_enemy)
	// {
	// 	if (glm::length(p_enemy->getPos() - player.getPos()) < glm::length(p_amplifier->getPos() - player.getPos()))
	// 	{
	// 		protectingTarget = p_enemy;
	// 		//direction = glm::normalize(p_enemy->getPos() - m_pos);
	// 	}
	// 	else
	// 	{
	// 		protectingTarget = p_amplifier;
	// 		//direction = glm::normalize(p_amplifier->getPos() - m_pos);
	// 	}

	// }
	// else
	// {
	// 	protectingTarget = p_amplifier;
	// 	//direction = glm::normalize(p_amplifier->getPos() - m_pos);
	// }


	//protectingTarget = 

	if (protectingTarget)
	{
		m_intervalRate = 5.0f;
		//std::cout << "protecting target " << protectingTarget << "\n";
		//std::cout << "protecting << " << feint_common::Instance()->convertiVec2toString(protectingTarget->getPos()) << "\n";
	}
	else
	{
		m_intervalRate = 5.0f;
		//decideStrat(deltaTime, enemy);
		//std::cout << "null, no target to protect  \n";
	}
	//handleShieldFormation(deltaTime);
}

FairyBase * EnemyGuardian::getHighestPriorityEnemy(std::vector<FairyBase *> enemy, const F_Player & player)
{
	FairyBase * returnVal = nullptr;
	//int maxPrio = 0;
	int selectCount = 0;
	float nearest = 1000.0f;
	for (int i = 0; i < enemy.size(); i++)
	{
		if(enemy[i]->getInternalID() == FAIRY_BASE || enemy[i]->getInternalID() == AMPLIFIER)
		{
			
			glm::vec2 targetPos = enemy[i]->getPos();
			if (targetPos.x > -BORDER && targetPos.x < BORDER
				&& targetPos.y > -BORDER && targetPos.y < BORDER)
			{
				glm::vec2 disVec = enemy[i]->getPos() - player.getPos();
				float distance = glm::length(disVec);
				if (!enemy[i]->isDeath())
				{
					if (distance < nearest)
					{
						nearest = distance;
						returnVal = enemy[i];
					}
				}
						
			}
			selectCount = i;
		}
	}
	//std::cout << "selected " << selectCount << "\n";
	return returnVal;
}

FairyBase * EnemyGuardian::getHighestPriorityAmplifier(std::vector<FairyBase *> amplifier, const F_Player & player)
{
	EnemyAmplifier * returnVal = nullptr;
	//int maxPrio = 0;
	int selectCount = 0;
	float nearest = 1000.0f;
	for (int i = 0; i < amplifier.size(); i++)
	{
		if(amplifier[i]->getInternalID() == AMPLIFIER)
		{

		
			glm::vec2 targetPos = amplifier[i]->getPos();
			if (targetPos.x > -BORDER && targetPos.x < BORDER
				&& targetPos.y > -BORDER && targetPos.y < BORDER)
			{
				glm::vec2 disVec = amplifier[i]->getPos() - player.getPos();
				float distance = glm::length(disVec);
				if (!amplifier[i]->isDeath())
				{
					if (distance < nearest)
					{
						nearest = distance;
						returnVal = dynamic_cast<EnemyAmplifier *>(amplifier[i]);
					}
				}

			}
			selectCount = i;
		}
	}
	//std::cout << "selected " << selectCount << "\n";
	return returnVal;
}

void EnemyGuardian::handleShieldFormation(float deltaTime)
{
// 	std::cout << "start >>>>>>>>>>>>>>>>>>>>>>>>>> \n";
// 	std::cout << m_vel.x << "\n";
	if (m_shield)
	{
		//std::cout << "state " << state << "\n";
		switch (state)
		{
		case ANIM_LEFT:
			if (!protectingTarget)
			{
				//std::cout << "turn left \n";

				m_shield->playAnimation("turn_default_invert");
				m_shield->setOffsetPos(glm::vec2(-10, 0));

			}
			else
			{
				//std::cout << "turn default left \n";
				m_shield->playAnimation("default");
				m_shield->setOffsetPos(glm::vec2(0, -10));
			}
			break;

		case ANIM_RIGHT:
			if (!protectingTarget)
			{
				//std::cout << "turn right \n";
				m_shield->playAnimation("turn_default");
				m_shield->setOffsetPos(glm::vec2(10, 0));
			}
			else
			{
				//std::cout << "turn default right \n";
				m_shield->playAnimation("default");
				m_shield->setOffsetPos(glm::vec2(0, -10));
			}
			break;

		default:

			break;
		}	
	}
/*	std::cout << "end <<<<<<<<<<<<<<<<<<<<<<<<<< \n";*/

// 	if (m_shield)
// 	{
// 		if (lastAnim == ANIM_LEFT)
// 		{
// 			m_shield->playAnimation("turn_side_invert");
// 			//lastAnim = val;
// 		}
// 		else if (lastAnim == ANIM_RIGHT)
// 		{
// 			m_shield->playAnimation("turn_side");
// 			//lastAnim = val;
// 		}
// 		else
// 		{
// 			m_shield->playAnimation("default");
// 
// 		}
// 		m_shield->setOffsetPos(glm::vec2(0, -10));

//	}

}

void EnemyGuardian::decideAnimation(const glm::vec2 & pos)
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
		oldPos = pos;
		if (currentState != state)
		{

			currentState = state;
			animationLimitCounter = 1.0f;
			setMovementAnim(currentState);
			if (m_vel.x < 0)
			{
				handleShieldFormation(1.0f);
			}
			if (m_vel.x > 0)
			{
				handleShieldFormation(1.0f);
			}

		}

	}
	
}

void EnemyGuardian::setDisabled(bool value)
{
	m_isDisabled = value;
}
