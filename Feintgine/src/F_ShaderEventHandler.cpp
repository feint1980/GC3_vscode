#include "F_ShaderEventHandler.h"

namespace Feintgine
{



	F_ShaderEventHandler::F_ShaderEventHandler()
	{
	}


	F_ShaderEventHandler::~F_ShaderEventHandler()
	{
	}

	void F_ShaderEventHandler::update(float deltaTime)
	{
		for (int i = 0; i < m_eventList.size(); i++)
		{
			m_eventList[i]->update(deltaTime);
		}
	}

	void F_ShaderEventHandler::applyToShader()
	{
		for (int i = 0; i < m_eventList.size(); i++)
		{
			m_eventList[i]->applyToShader();
		}
	}

	void F_ShaderEventHandler::addEvent(F_ShaderEventBase * t_event)
	{
		m_eventList.push_back(t_event);
	}

	Feintgine::F_ShaderEventBase * F_ShaderEventHandler::getEventByName(const std::string & name)
	{
		//std::cout << "search for " + name << "\n";
		for (int i = 0; i < m_eventList.size(); i++)
		{
			if (name == m_eventList[i]->getName())
			{
				return  m_eventList[i];
			}
		}
		return nullptr;
	}

}

