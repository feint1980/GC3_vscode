#pragma once
#include <F_LuaObjectManipulator.h>
#include "F_Lua_Boss.h"


enum LuaBossState {

	Move, 
	StandIdle,
	AddEvent
};


class F_Lua_Boss_State //: public Feintgine::F_LuaObjectManipulator
{
public:
	F_Lua_Boss_State();
	~F_Lua_Boss_State();

	F_Lua_Boss * m_luaBoss;

	void moveObject(F_Lua_Boss *dynamicObject, const glm::vec2 & target, float time);

	void standIdle(F_Lua_Boss *dynamicObject, float time,const std::string & animName);

	void teleport(F_Lua_Boss *dynamicObject, const glm::vec2 & target);

	void addDelayedEvent(F_Lua_Boss * dynamicObject, const Feintgine::oEvent::f_callback & cb, double when);


	virtual bool update(float deltaTime);
protected:

	LuaBossState m_state;
	bool m_isComplete = false;

	glm::vec2 m_startPos;

	glm::vec2 m_endPos;

	float m_completionTime = 0.0f;
	float m_elaspedTime = 0.0f;

	
};


