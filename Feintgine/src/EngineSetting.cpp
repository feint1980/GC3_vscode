#include "EngineSetting.h"

float ENGINE_targetFPS = 60.0;
double ENGINE_current_tick = 0.0;
bool ENGINE_isGameRunning = true;



void togglePause()
{
	if (ENGINE_isGameRunning)
	{
		ENGINE_isGameRunning = false;
	}
	else
	{
		ENGINE_isGameRunning = true;
	}

}