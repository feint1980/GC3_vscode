#include "F_Lua_GenericObject.h"


F_Lua_GenericObject::F_Lua_GenericObject()
{
	
	m_isDeath = false;
	m_animation_left_name = "left";
	m_animation_right_name = "right";
	m_animation_center_name = "idle";
	m_chargingHandler.registerTargetPos(&m_pos);

}


F_Lua_GenericObject::~F_Lua_GenericObject()
{

}

void F_Lua_GenericObject::t_editor_reset()
{
    for (int i = 0; i < m_bullets.size(); i++)
    {
        m_bullets[i]->setLifeTime(0.0f);
        clearEvent();
    }
}


void F_Lua_GenericObject::draw(Feintgine::SpriteBatch & spriteBatch)
{
	F_LuaDynamicObject::draw(spriteBatch);
	for (int i = 0; i < m_bullets.size(); i++)
	{
		
		m_bullets[i]->draw(spriteBatch);
	}
}

void F_Lua_GenericObject::update(float deltaTime)
{
	//std::cout << "updated 121212121 \n";
	F_LuaDynamicObject::update(deltaTime);
	
	if (!m_isAnimationOverride)
	{
		decideAnimation(m_pos);
	}
	
	//m_pos += m_vel  * deltaTime;


	// if (m_isAnimated)
	// {
	// 	m_animation.update(deltaTime);
	// 	m_animation.setPos(m_pos);
	// }

	for (int i = 0; i < m_bullets.size(); i++)
	{
		m_bullets[i]->update(deltaTime);
	}
	

}
