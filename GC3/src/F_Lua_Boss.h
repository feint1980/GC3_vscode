#pragma once
#include <F_LuaDynamicObject.h>
#include "EnemyBulletBase.h"
//#include <>


#define ANIM_LEFT 0
#define ANIM_RIGHT 1
#define ANIM_CENTER 2

class F_Lua_Boss : public Feintgine::F_LuaDynamicObject
{
public:
	F_Lua_Boss();
	~F_Lua_Boss();

	virtual void update(float deltaTime)override;


	virtual void draw(Feintgine::SpriteBatch & spriteBatch)override;

	void setAnimOverRide(bool val);

	void eventTimer();

	void t_editor_reset();

	void clearEvent();

	void addEvent(const Feintgine::oEvent::f_callback & cb, double when);
	std::vector<EnemyBulletBase *> m_bullets;

private :

	void decideAnimation(const glm::vec2 & pos);

	void setMovementAnim(int val);

	bool m_isDeath;

	bool m_isAnimationOverride = false;

	std::string m_animation_left_name;
	std::string m_animation_right_name;
	std::string m_animation_center_name;
	glm::vec2 oldPos;


	std::priority_queue<Feintgine::oEvent,
		std::vector<Feintgine::oEvent>, Feintgine::oEvent_less> event_queue;

	int currentState = ANIM_CENTER;
	int state = ANIM_CENTER;

};

