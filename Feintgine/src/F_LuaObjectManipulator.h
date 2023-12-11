#pragma once
#include "F_LuaDynamicObject.h"


namespace Feintgine
{



	class F_LuaObjectManipulator
	{
	public:
		F_LuaObjectManipulator();
		~F_LuaObjectManipulator();

		void moveObject(F_LuaDynamicObject *dynamicObject, const glm::vec2 & target, float time);

		void teleportObject(F_LuaDynamicObject *dynamicObject, const glm::vec2 & target);

		virtual bool update(float deltaTime);

		F_LuaDynamicObject * m_dynamicObject;

	protected:
		
		bool m_isComplete = false;

		glm::vec2 m_startPos; 

		glm::vec2 m_endPos;

		float m_completionTime = 0.0f;
		float m_elaspedTime = 0.0f; 

	};

}