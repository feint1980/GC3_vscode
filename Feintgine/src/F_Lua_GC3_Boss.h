#pragma once
#include "F_LuaDynamicObject.h"

#define ANIM_LEFT 0
#define ANIM_RIGHT 1
#define ANIM_CENTER 2
namespace Feintgine
{
	class F_Lua_GC3_Boss : public F_LuaDynamicObject
	{
	public:
		F_Lua_GC3_Boss();
		~F_Lua_GC3_Boss();

		virtual void update(float deltaTime)override;

	protected: 
		void decideAnimation(const glm::vec2 & pos);

		void setMovementAnim(int val);

		bool m_isDeath;

		std::string m_animation_left_name;
		std::string m_animation_right_name;
		std::string m_animation_center_name;
		glm::vec2 oldPos;

		int currentState = ANIM_CENTER;
		int state = ANIM_CENTER;
	};
}

