#include "F_Lua_Boss.h"
#include <EngineSetting.h>


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

void F_Lua_Boss::decideAnimation(const glm::vec2 & pos)
{
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

void F_Lua_Boss::setMovementAnim(int val)
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

void F_Lua_Boss::setAnimOverRide(bool val)
{
	m_isAnimationOverride = val;
}


void F_Lua_Boss::eventTimer()
{
	while (!event_queue.empty() &&
		(event_queue.top().when < ENGINE_current_tick))
	{
		//std::cout << "exccute event at " << event_queue.top().when << "\n";
		event_queue.top()();
		event_queue.pop();
	}
}

void F_Lua_Boss::clearEvent()
{
	while (!event_queue.empty())
	{
		event_queue.pop();
	}	
}

void F_Lua_Boss::addEvent(const Feintgine::oEvent::f_callback & cb, double when)
{
	event_queue.emplace(cb, when);
}

void F_Lua_Boss::draw(Feintgine::SpriteBatch & spriteBatch)
{
	if (m_isAnimated)
	{
		m_animation.setPos(m_pos);
		m_animation.setScale(m_scale);
		m_animation.setAngle(m_angle);
		m_animation.draw(spriteBatch);
		//std::cout << "called \n";
	}
	else
	{
		glm::vec4 desRect;
		desRect.x = m_pos.x - (m_sprite.getDim().x * m_scale.x) / 2.0f;
		desRect.y = m_pos.y - (m_sprite.getDim().y * m_scale.y) / 2.0f;
		desRect.z = m_sprite.getDim().x  * m_scale.x;
		desRect.w = m_sprite.getDim().y  * m_scale.y;
		spriteBatch.draw(desRect, m_sprite.getUV(), m_sprite.getTexture().id, m_depth, m_color, m_angle);
	}

	//std::cout << "draw size " << m_bullets.size() << "\n";
	for (int i = 0; i < m_bullets.size(); i++)
	{
		
		m_bullets[i]->draw(spriteBatch);
	}
}

void F_Lua_Boss::t_editor_reset()
{
	for (int i = 0; i < m_bullets.size(); i++)
	{
		m_bullets[i]->setLifeTime(0.0f);
		clearEvent();
	}
}

