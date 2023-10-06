#include "F_Event.h"


namespace Feintgine
{

// 	void F_Event::add(const event::callback_type &cb, const time_t &when)
// 	{
// 		auto real_when = std::chrono::system_clock::from_time_t(when);
// 
// 		event_queue.emplace(cb, real_when);
// 	}
// 
// 	void F_Event::add(const event::callback_type &cb, const t_timeval &when)
// 	{
// 		auto real_when = std::chrono::system_clock::from_time_t(when.tv_sec) +
// 			std::chrono::microseconds(when.tv_usec);
// 
// 		event_queue.emplace(cb, real_when);
// 	}

	void F_Event::add(const event::callback_type &cb, const std::chrono::time_point<std::chrono::system_clock> &when)
	{
		event_queue.emplace(cb, when);
	}

	void F_Event::timer()
	{
		event::time_type now = std::chrono::system_clock::now();

		while (!event_queue.empty() &&
			(event_queue.top().when_ < now))
		{
			event_queue.top()();
			event_queue.pop();
		}
	}


	F_Event *F_Event::p_Instance = 0;


}