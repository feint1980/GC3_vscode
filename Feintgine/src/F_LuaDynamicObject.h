#pragma once
#include "SpriteBatch.h"
#include "F_Sprite.h"
#include "F_AnimatedObject.h"
#include "LuaManager.h"

// move table define
/*
1 -> straight
2 -> berzier
*/

#define MOVE_STATE_LINEAR 1
#define MOVE_STATE_BERZIER 2



namespace Feintgine
{


	class F_LuaDynamicObject
	{
	public:


		F_LuaDynamicObject();
		~F_LuaDynamicObject();

		void createObject(const glm::vec2 & pos,
			const Feintgine::F_AnimatedObject & t_animation,
			const glm::vec2 & scale, float depth, float angle = 0.0f);

		void createObject(const glm::vec2 & pos,
			const std::string & t_animationPath,
			const glm::vec2 & scale, float depth, float angle = 0.0f);

		virtual void draw(Feintgine::SpriteBatch & spriteBatch);

		virtual void update(float deltaTime);

		void updateMovement(float deltaTime);

		void setMoveLinear(const glm::vec2 & destination, float speed);

		void playAnimation(const std::string & animationName, int time = -1);

		bool Lua_createObject(const std::string & luaPath);

		int wrap_CreateObject(lua_State * L); // all lua handler must be int 

		glm::vec2 getPos() const { return m_pos; }


		void setPos(const glm::vec2 & pos);
		

	protected:


		// Custom states declare below 
		// move table 
		/*
			1 -> straight 
			2 -> berzier
		*/
		int m_moveState;

		// move variable declare bellow
		
		glm::vec2 m_moveDestination; //
		glm::vec2 m_currentDirection;

		// Custom state declare above 


		glm::vec2 m_pos;
		glm::vec2 m_scale;
		float m_angle;
		float m_depth;
		bool m_isAnimated = false;

		glm::vec2 m_vel;
		glm::vec2 m_direction;

		float m_speed;

		lua_State * m_script;

		F_Sprite m_sprite;
		Color m_color;
		F_AnimatedObject m_animation;

	};
}

