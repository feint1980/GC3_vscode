#pragma once
#include "SpriteBatch.h"
#include "F_Sprite.h"
#include "F_AnimatedObject.h"
#include "LuaManager.h"
#include "F_oEvent.h"
#include "AfterImageParticle.h"

// move table define
/*
1 -> straight
2 -> berzier
*/

#define MOVE_STATE_LINEAR 1
#define MOVE_STATE_BERZIER 2


#define ANIM_LEFT 0
#define ANIM_RIGHT 1
#define ANIM_CENTER 2


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

		void updateCharging(float deltaTime);

		void setCharging(bool val);

		void setMoveLinear(const glm::vec2 & destination, float speed);

		void playAnimation(const std::string & animationName, int time = -1);

		bool Lua_createObject(const std::string & luaPath);

		int wrap_CreateObject(lua_State * L); // all lua handler must be int 

		glm::vec2 getPos() const { return m_pos; }

		void setAnimOverRide(bool val) { m_isAnimationOverride = val; }

		void setPos(const glm::vec2 & pos);

		void decideAnimation(const glm::vec2 & pos);

		void clearEvent();

		void addEvent(const Feintgine::oEvent::f_callback & cb, double when);

		void eventTimer();

		void setVel(const glm::vec2 & vel);

		void setTrace(float interval, float lifeTime, int maxTrace ,float scaleRate,float alphaRate,float traceLifeTime);

		float getAngle() const { return m_angle; }


	protected:


		// protected functions

		void setMovementAnim(int val);

		// Custom states declare below 
		// move table 
		/*
			1 -> straight 
			2 -> berzier
		*/

		// protected variables

		int m_moveState;

		// move variable declare bellow

		bool m_isAnimationOverride = false;
		
		glm::vec2 m_moveDestination; //
		glm::vec2 m_currentDirection;

		// Custom state declare above 

		glm::vec2 * p_pos;
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
		
		int currentState = ANIM_CENTER;
		int state = ANIM_CENTER;
		bool m_isDeath;

		std::string m_animation_left_name;
		std::string m_animation_right_name;
		std::string m_animation_center_name;
		glm::vec2 oldPos;

		std::priority_queue<Feintgine::oEvent,
			std::vector<Feintgine::oEvent>, Feintgine::oEvent_less> event_queue;

		float m_afterImageTime = 0.0f;

		AfterImageObject m_afterImageParticle;


		// todo: put it in other class
		// std::vector<Feintgine::F_Sprite> m_chargingSprites;
		// float m_chargeTime;
		// float m_chargeRadius;
		// int m_chargeMaxCount;
		// float m_chargeMoveSpeed;
		

	};
}

