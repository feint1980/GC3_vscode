#include "FrameCounter.h"

namespace Feintgine {


	FrameCounter::FrameCounter()
	{

	}


	FrameCounter::~FrameCounter()
	{
	}

	void FrameCounter::start()
	{

		fpsTimer.start();
		
	}
	

	void FrameCounter::update()
	{
		float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
// 		if (avgFPS > 2000000)
// 		{
// 			avgFPS = 0;
// 		}
		++countedFrames;
		std::cout << "counted " << countedFrames << "\n";
		std::cout << "FPS : " << avgFPS << "\n";
	}

}