#include "F_Lua_Boss_State_MoveObject.h"



F_Lua_Boss_State_MoveObject::F_Lua_Boss_State_MoveObject()
{
}


F_Lua_Boss_State_MoveObject::~F_Lua_Boss_State_MoveObject()
{
}

// void F_Lua_Boss_State_MoveObject::moveObject(F_Lua_Boss *dynamicObject, const glm::vec2 & target, float time)
// {
// 	m_luaBoss = dynamicObject;
// 	m_startPos = m_luaBoss->getPos();
// 	m_endPos = target;
// 	m_completionTime = time;
// }
// 
// bool F_Lua_Boss_State_MoveObject::update(float deltaTime)
// {
// 	m_elaspedTime += deltaTime;
// 
// 	glm::vec2 tPos = (m_endPos - m_startPos) * (m_elaspedTime / m_completionTime) + m_startPos;
// 
// 
// 	if (m_elaspedTime >= m_completionTime)
// 	{
// 		tPos = m_endPos;
// 		m_isComplete = true;
// 		//std::cout << "m_isComplete set \n";
// 	}
// 	if (m_luaBoss)
// 	{
// 	 	m_luaBoss->setPos(tPos);
// 	}
// 
// 	return m_isComplete;
// }
