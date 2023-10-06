#pragma once
#include <SDL2/SDL.h>

namespace Feintgine {


	typedef unsigned long long Uint32;
	class FTimer
	{
	public:
		FTimer();
		~FTimer();

		//The various clock actions
		void start();
		void stop();
		void pause();
		void unpause();

		//Gets the timer's time
		Uint32 getTicks();

		//Checks the status of the timer
		bool isStarted()
		{
			return mStarted;
		}
		bool isPaused()
		{
			return mPaused;
		}

	private:
		//The clock time when the timer started
		Uint32 mStartTicks;

		//The ticks stored when the timer was paused
		Uint32 mPausedTicks;

		//The timer status
		bool mPaused;
		bool mStarted;
	};
}

