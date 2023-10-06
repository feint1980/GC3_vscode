#include "F_LuaDynamicObject.h"

namespace Feintgine
{

	F_LuaDynamicObject::F_LuaDynamicObject()
	{
		m_moveState = 0;
		glm::vec2 m_vel = glm::vec2(0);
		glm::vec2 m_direction = glm::vec2(0);
	}


	F_LuaDynamicObject::~F_LuaDynamicObject()
	{

	}

	void F_LuaDynamicObject::createObject(const glm::vec2 & pos,
		const Feintgine::F_AnimatedObject & t_animation,
		const glm::vec2 & scale, float depth, float angle /*= 0.0f*/)
	{
		m_pos = pos;
		m_animation = t_animation;
		m_scale = scale;
		m_depth = depth;
		m_angle = angle;
		m_animation.playAnimation("idle");
		m_isAnimated = true;
	}

	void F_LuaDynamicObject::createObject(const glm::vec2 & pos, const std::string & t_animationPath, const glm::vec2 & scale, float depth, float angle /*= 0.0f*/)
	{
		m_pos = pos;
		m_animation.init(t_animationPath);
		m_scale = scale;
		m_depth = depth;
		m_angle = angle;
		m_animation.playAnimation("idle");
		//setMoveLinear(glm::vec2(0, -400), 1.0f);
		m_isAnimated = true;
	}

	void F_LuaDynamicObject::draw(Feintgine::SpriteBatch & spriteBatch)
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
	}

	void F_LuaDynamicObject::update(float deltaTime)
	{
		m_pos += m_vel  * deltaTime;
		//updateMovement(deltaTime);
		if (m_isAnimated)
		{
			m_animation.update(deltaTime);
		}
	}

	void F_LuaDynamicObject::updateMovement(float deltaTime)
	{
		if (m_moveState & MOVE_STATE_LINEAR)
		{
			glm::vec2 t_direction = glm::normalize(m_moveDestination - m_pos);
			if (t_direction != glm::normalize(m_vel))
			{
				m_pos = m_moveDestination;
				m_moveState |= ~MOVE_STATE_LINEAR;
			}
		}
	}

	void F_LuaDynamicObject::setMoveLinear(const glm::vec2 & destination,
		float speed)
	{
		m_moveState |= MOVE_STATE_LINEAR;
		m_moveDestination = destination;
		m_vel = glm::normalize(m_moveDestination - m_pos) * speed;

	}

	void F_LuaDynamicObject::playAnimation(const std::string & animationName, int time /*= -1*/)
	{
		m_animation.playAnimation(animationName, time);
	}

	bool F_LuaDynamicObject::Lua_createObject(const std::string & luaPath)
	{
		m_script = luaL_newstate();
		if (LuaManager::Instance()->checkLua(m_script, luaL_dofile(m_script, luaPath.c_str())))
		{
			lua_getglobal(m_script, "createObject");
			if (lua_isfunction(m_script, -1))
			{
				lua_pushlightuserdata(m_script, this); // todo : push this pointer as param
				lua_pushnumber(m_script, -1); // todo : explain later

				/*
				 lua_pcall argument belike : 
				 1 lua_state | use as lua stack
				 2 number of params
				 3 expected number of return value 
				 4 ( which is 0 ) | error handling, no need just add 0 
				*/
				if (LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, 2, 1, 0)))
				{
					return true;
				}
			}
		}

		return false;
	}


	int F_LuaDynamicObject::wrap_CreateObject(lua_State * L)
	{
		int numberOfAgs = 2;
		if (lua_gettop(L) != numberOfAgs)
		{
			return -1; // not as expected ags, return false
		}
	}

	void F_LuaDynamicObject::setPos(const glm::vec2 & pos)
	{
		m_pos = pos;
	}

}