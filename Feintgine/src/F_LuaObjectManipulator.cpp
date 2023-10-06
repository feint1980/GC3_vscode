#include "F_LuaObjectManipulator.h"





Feintgine::F_LuaObjectManipulator::F_LuaObjectManipulator()
{
}


Feintgine::F_LuaObjectManipulator::~F_LuaObjectManipulator()
{
}

void Feintgine::F_LuaObjectManipulator::moveObject(F_LuaDynamicObject *dynamicObject,
	const glm::vec2 & target, float time)
{
// 	m_dynamicObject = dynamicObject;
// 	m_startPos = m_dynamicObject->getPos();
// 	m_endPos = target;
// 	m_completionTime = time;
	//m_dynamicObject->playAnimation("idle");
}


bool Feintgine::F_LuaObjectManipulator::update(float deltaTime)
{
	//std::cout << "manipulator update \n";
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
// 	if (m_dynamicObject)
// 	{
// 		m_dynamicObject->setPos(tPos);
// 	}
	
	return m_isComplete;
	
}
