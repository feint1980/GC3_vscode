#include "F_oEvent.h"
#include "EngineSetting.h"

Feintgine::F_oEvent * Feintgine::F_oEvent::p_instance = 0;
namespace Feintgine 
{


	void F_oEvent::add(const oEvent::f_callback & cb, const unsigned int& when)
	{
		
		double real_when = convertMSToS(when);
		
		event_queue.emplace(cb, real_when);

	}

	void F_oEvent::timer()
	{
	
		while (!event_queue.empty() && (event_queue.top().when < ENGINE_current_tick))
		{
			event_queue.top()();
			event_queue.pop();
		}
	}

	void F_oEvent::clearEvent()
	{
		while (!event_queue.empty())
		{
			event_queue.pop();
		}
	}

	F_oEvent::F_oEvent()
	{
	}


	F_oEvent::~F_oEvent()
	{
	}


}
