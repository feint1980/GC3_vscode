#pragma once
#include <SDL2/SDL.h>
#include "FTimer.h"
#include <sstream>
#include <iostream>
namespace Feintgine {
	
	

	class FrameCounter
	{
	public:
		FrameCounter();
		~FrameCounter();
		void start();
		void update();

	private:
		//Main loop flag
		bool quit = false;

		//Event handler
		SDL_Event e;

		//Set text color as black
		SDL_Color textColor = { 0, 0, 0, 255 };

		//The frames per second timer
		FTimer fpsTimer;


		//In memory text stream
		std::stringstream timeText;

		//Start counting frames per second
		int countedFrames = 0;


	};

}