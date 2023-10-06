#include "FairyBase.h"



FairyBase::FairyBase()
{
	m_animation_left_name  = "left";
	m_animation_right_name = "right";
	m_animation_center_name = "idle";


}


FairyBase::~FairyBase()
{
}

void FairyBase::decideAnimation(const glm::vec2 & pos)
{
	//std::cout << "deciding \n";
	if (!m_isDeath)
	{
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
			setMovementAnim(currentState);
		}
	}
		
}


void FairyBase::setMovementAnim(int val)
{

	switch (val)
	{
	case ANIM_LEFT:
	{
		playAnim(m_animation_left_name);
// 		if(m_shield)
// 		{
// 			std::cout << "passed left " << m_vel.x << "\n";
// 			if (abs(m_vel.x) > 0.4f)
// 			{
// 
// 				
// 				m_shield->playAnimation("turn_default_invert");
// 				m_shield->setOffsetPos(glm::vec2(-10, 0));
// 				
// 			}
// 			else
// 			{
// 				m_shield->playAnimation("default");
// 				m_shield->setOffsetPos(glm::vec2(0, -10));
// 			}
// 			lastAnim = val;
// 		}
	}
	break;
	case ANIM_RIGHT:
	{
		playAnim(m_animation_right_name);
// 		if (m_shield)
// 		{
// 
// 			std::cout << "passed  right" << m_vel.x << "\n";
// 			if (abs(m_vel.x) > 0.4f)
// 			{
// 
// 				m_shield->playAnimation("turn_default");
// 				m_shield->setOffsetPos(glm::vec2(10, 0));
// 				
// 			}
// 			else
// 			{
// 				m_shield->playAnimation("default");
// 				m_shield->setOffsetPos(glm::vec2(0, -10));
// 			}
// 			lastAnim = val;
// 		}
	}
	break;
	case ANIM_CENTER:
	{
		playAnim(m_animation_center_name);
// 		if (m_shield)
// 		{
// 			if (lastAnim == ANIM_LEFT)
// 			{
// 				m_shield->playAnimation("turn_side_invert");
// 				//lastAnim = val;
// 			}
// 			else if(lastAnim == ANIM_RIGHT)
// 			{
// 				m_shield->playAnimation("turn_side");
// 				//lastAnim = val;
// 			}
// 			else
// 			{
// 				m_shield->playAnimation("default");
// 				
// 			}
// 			lastAnim = val;
// 			m_shield->setOffsetPos(glm::vec2(0, -10));
// 			
// 		}
	}
	break;
	default:
		break;
	}

	
}

void FairyBase::setCustomAnim(int type, const std::string & name)
{
	switch (type)
	{
	case ANIM_LEFT:
	{
		m_animation_left_name = name;
	}
	break;
	case ANIM_RIGHT:
	{
		m_animation_right_name = name;
	}
	break;
	case ANIM_CENTER:
	{
		m_animation_center_name = name;
	}
	break;
	default:
		break;
	}
}


void FairyBase::update(float deltaTime)
{

	m_pos += m_vel * deltaTime;
	decideAnimation(m_pos);

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

	if (m_isMoveBerzier)
	{

		m_perc = berzierRate;
		berzierRate += 0.01f * deltaTime;
		m_vel = glm::normalize(getBerzierPos(m_start, m_inter, m_des, m_perc)) * m_berzierSpeed;
		m_vel.y = -m_vel.y;

	}

	if (m_shield)
	{
		m_shield->update(deltaTime);
		m_shield->setPos(m_pos);
	}

	timer();
}