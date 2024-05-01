#include "F_Lua_Boss.h"

F_Lua_Boss::F_Lua_Boss()
{
	m_isDeath = false;
	m_animation_left_name = "left";
	m_animation_right_name = "right";
	m_animation_center_name = "idle";
}


F_Lua_Boss::~F_Lua_Boss()
{
}


void F_Lua_Boss::update(float deltaTime)
{
	if (!m_isAnimationOverride)
	{
		decideAnimation(m_pos);
	}
	
	m_pos += m_vel  * deltaTime;

	if (m_isAnimated)
	{
		m_animation.update(deltaTime);
	}

	for (int i = 0; i < m_bullets.size(); i++)
	{
		m_bullets[i]->update(deltaTime);
	}

	eventTimer();
}
