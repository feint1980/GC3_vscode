#include "F_Lua_Boss_State.h"



F_Lua_Boss_State::F_Lua_Boss_State()
{
	m_state = LuaBossState::None;
}


F_Lua_Boss_State::~F_Lua_Boss_State()
{
}

void F_Lua_Boss_State::moveObject(F_Lua_GenericObject * dynamicObject, const glm::vec2 & target, float time)
{
	m_luaBoss = dynamicObject;
	m_startPos = m_luaBoss->getPos();
	m_endPos = target;
	m_completionTime = time;
	m_state = LuaBossState::Move;
	m_waitDone = true;
}

void  F_Lua_Boss_State::waitFor(F_Lua_GenericObject * dynamicObject, float time)
{
	std::cout << "wait for " << time << "\n";
	m_luaBoss = dynamicObject;
	m_elaspedTime = 0;
	m_completionTime = time;
	m_state = LuaBossState::Wait;
	m_isComplete = false;
	m_waitDone = false;
}

void F_Lua_Boss_State::setObjectVel(F_Lua_GenericObject * dynamicObject, const glm::vec2 & vel)
{
	m_luaBoss = dynamicObject;
	m_luaBoss->setVel(vel);
	//m_isComplete = true;
}

bool F_Lua_Boss_State::update(float deltaTime)
{
	m_elaspedTime += deltaTime;


	if (m_elaspedTime >= m_completionTime)
	{
		
		m_isComplete = true;
	}
	///
	switch (m_state)
	{
	case LuaBossState::Move:
	{
		glm::vec2 tPos = (m_endPos - m_startPos) * (m_elaspedTime / m_completionTime) + m_startPos;
		if (m_luaBoss)
		{
			if (m_isComplete)
			{
				tPos = m_endPos;
			}
			m_luaBoss->setPos(tPos);
			
		}
	}
	break;
	case LuaBossState::StandIdle:
		if (m_isComplete)
		{
			m_luaBoss->setAnimOverRide(false);
		}
		break;
	case LuaBossState::AddEvent:
	{

	}
	break;
	case LuaBossState::Wait:
	{
		//std::cout << "elapsed time " << m_elaspedTime << "\n";
		if(m_isComplete)
		{
			m_waitDone = true;
			std::cout << "real wait done \n";
		}
		
		//std::cout << "waiting \n";
	}
	break;
	default:
		break;
	}

	return m_isComplete && m_waitDone ;
}

void F_Lua_Boss_State::standIdle(F_Lua_GenericObject * dynamicObject, float time, const std::string & animName, bool isOverRide /*= false*/) 
{
	m_completionTime = time;
	m_elaspedTime = 0;
	m_luaBoss = dynamicObject;
	//m_luaBoss = dynamicObject;
	//std::cout << "use animation  " << animName << "\n";
	//m_luaBoss->playAnimation(animName,99);
	m_luaBoss->setAnimOverRide(isOverRide);
	m_luaBoss->playAnimation(animName);
	m_state = LuaBossState::StandIdle;
	m_waitDone = true;

}

void F_Lua_Boss_State::addDelayedEvent(F_Lua_GenericObject *  dynamicObject, const Feintgine::oEvent::f_callback & cb, double when)
{
	m_luaBoss = dynamicObject;
	//m_luaBoss->addEvent(cb, when);
	m_state = LuaBossState::AddEvent;
	m_completionTime = 1;
	m_isComplete = true;
	m_waitDone = true;
}
