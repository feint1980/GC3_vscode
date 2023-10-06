#include "FTimer.h"

namespace Feintgine {

	FTimer::FTimer()
	{
		mStartTicks = 0;
		mPausedTicks = 0;

		mPaused = false;
		mStarted = false;

	}


	FTimer::~FTimer()
	{
	}

	void FTimer::start()
	{
		mStarted = true;

		//Unpause the timer
		mPaused = false;

		//Get the current clock time
		mStartTicks = SDL_GetTicks();
		mPausedTicks = 0;
	}

	void FTimer::stop()
	{
		mStarted = false;

		//Unpause the timer
		mPaused = false;

		//Clear tick variables
		mStartTicks = 0;
		mPausedTicks = 0;
	}

	void FTimer::pause()
	{
		if (mStarted && !mPaused)
		{
			//Pause the timer
			mPaused = true;

			//Calculate the paused ticks
			mPausedTicks = SDL_GetTicks() - mStartTicks;
			mStartTicks = 0;
		}
	}

	void FTimer::unpause()
	{
		if (mStarted && mPaused)
		{
			//Unpause the timer
			mPaused = false;

			//Reset the starting ticks
			mStartTicks = SDL_GetTicks() - mPausedTicks;

			//Reset the paused ticks
			mPausedTicks = 0;
		}
	}

	Uint32 FTimer::getTicks()
	{
		Uint32 time = 0;

		//If the timer is running
		if (mStarted)
		{
			//If the timer is paused
			if (mPaused)
			{
				//Return the number of ticks when the timer was paused
				time = mPausedTicks;
			}
			else
			{
				//Return the current time minus the start time
				time = SDL_GetTicks() - mStartTicks;
			}
		}
		return time;
	}
}