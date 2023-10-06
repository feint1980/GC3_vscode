#pragma once

#include <vector>
#include "F_ShaderEvent_Float.h"
#include "F_ShaderEvent_Vec3.h"
#include <iostream>

namespace Feintgine
{

	class F_ShaderEventHandler
	{
	public:
		F_ShaderEventHandler();
		~F_ShaderEventHandler();

		void update(float deltaTime);
		void applyToShader();
		void addEvent(F_ShaderEventBase * t_event);


		F_ShaderEventBase * getEventByName(const std::string & name);

	private:
		std::vector <F_ShaderEventBase *> m_eventList;
	};

}