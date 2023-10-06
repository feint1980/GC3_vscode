#ifndef _F_OEVENT_H_
#define _F_OEVENT_H_

#include <functional>
#include <queue>
#include <iostream>
namespace Feintgine
{
	struct oEvent
	{
		typedef std::function<void()> f_callback;
		oEvent(const f_callback & cb, const double & t_when) : callback(cb), when(t_when)
		{
		}


		f_callback callback;
		double when;

		void operator()() const
		{
			callback();
		}
	};

	struct oEvent_less : public std::less<oEvent>
	{
		bool operator()(const oEvent &e1, const oEvent & e2) const
		{
			return (e2.when < e1.when);
		}

	};

	class F_oEvent
	{
	public:

		std::priority_queue<oEvent, std::vector<oEvent>, oEvent_less> event_queue;
		//void add(const oEvent::f_callback & cb, const double & when);

		void add(const oEvent::f_callback & cb, const unsigned int& when);

		static double convertMSToS(unsigned int val)
		{
			double returnVal = ((double)val / 1000.0f);
			return returnVal;
		}

		void timer();
		static F_oEvent * getInstance()
		{
			if (!p_instance)
			{
				p_instance = new F_oEvent;
				return p_instance;
			}
			return p_instance;
		}

		void clearEvent();

		F_oEvent();
		~F_oEvent();

	private :
		static F_oEvent * p_instance;
	};
}
#endif

