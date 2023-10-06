#ifndef _F_EVENT_H_
#define _F_EVENT_H_
 
#ifdef __GLIBC__
#if !defined(_POSIX_C_SOURCE) && !defined(_POSIX_SOURCE)
struct timeval {
	time_t      tv_sec;     /* seconds */
	long        tv_usec;    /* microseconds */
};

struct timespec {
	time_t      tv_sec;     /* seconds */
	long        tv_nsec;    /* nanoseconds */
};
#endif
#endif

#include <functional>
#include <queue>
#include <chrono>
#include <time.h>
#include <iostream>
//#include <sys/time.h>  // for `time_t` and `struct timeval`

struct t_timeval {
	time_t      tv_sec;     /* seconds */
	long        tv_usec;    /* microseconds */
};
namespace Feintgine
{


		struct event
		{
			typedef std::function<void()> callback_type;
			typedef std::chrono::time_point<std::chrono::system_clock> time_type;

			event(const callback_type &cb, const time_type &when)
				: callback_(cb), when_(when)
			{ }

			void operator()() const
			{
				callback_();
			}

			callback_type callback_;
			time_type     when_;
		};

		struct event_less : public std::less<event>
		{
			bool operator()(const event &e1, const event &e2) const
			{
				return (e2.when_ < e1.when_);
			}
		};
		class F_Event
		{
		public:
			std::priority_queue<event, std::vector<event>, event_less> event_queue;

// 			void add(const event::callback_type &cb, const time_t &when);
// 		
// 			void add(const event::callback_type &cb, const t_timeval &when);
// 			

			void add(const event::callback_type &cb,
				const std::chrono::time_point<std::chrono::system_clock> &when);
			

			void timer();
			

			static F_Event *Instance()
			{
				if (p_Instance == 0)
				{
					p_Instance = new F_Event;
					return p_Instance;
				}
				return p_Instance;
			}
		private:
			static F_Event *p_Instance;
		};
		
	

}

#endif