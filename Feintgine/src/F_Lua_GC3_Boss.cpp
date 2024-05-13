#include "F_Lua_GC3_Boss.h"


namespace Feintgine
{
	F_Lua_GC3_Boss::F_Lua_GC3_Boss()
	{
		m_isDeath = false;
		m_animation_left_name = "left";
		m_animation_right_name = "right";
		m_animation_center_name = "idle";
	}


	F_Lua_GC3_Boss::~F_Lua_GC3_Boss()
	{
	}

	void F_Lua_GC3_Boss::update(float deltaTime)
	{
		//std::cout << "update \n";
		decideAnimation(m_pos);
		m_pos += m_vel  * deltaTime;
	
		if (m_isAnimated)
		{
			m_animation.update(deltaTime);
		}
	}

	// void F_Lua_GC3_Boss::decideAnimation(const glm::vec2 & pos)
	// {
	// 	if (!m_isDeath)
	// 	{
	// 		if (pos.x < oldPos.x)
	// 		{
	// 			state = ANIM_LEFT;
	// 		}
	// 		else if (pos.x > oldPos.x)
	// 		{

	// 			state = ANIM_RIGHT;
	// 		}
	// 		else if (pos.x == oldPos.x)
	// 		{

	// 			state = ANIM_CENTER;
	// 		}
			
	// 		if (currentState != state)
	// 		{

	// 			currentState = state;
	// 			setMovementAnim(currentState);
	// 		}
	// 		oldPos = pos;

	// 	}
	// }

	void F_Lua_GC3_Boss::setMovementAnim(int val)
	{
		switch (val)
		{
		case ANIM_LEFT:
		{
			m_animation.playAnimation(m_animation_left_name);

		}
		break;
		case ANIM_RIGHT:
		{
			m_animation.playAnimation(m_animation_right_name);
	
		}
		break;
		case ANIM_CENTER:
		{
			m_animation.playAnimation(m_animation_center_name);
		}
		break;
		default:
			break;
		}
	}

}