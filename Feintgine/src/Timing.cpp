#include "Timing.h"

#include <SDL2/SDL.h>

namespace Feintgine {

    FpsLimiter::FpsLimiter() {
    }
    void FpsLimiter::init(float maxFPS) {
        setMaxFPS(maxFPS);
    }

    void FpsLimiter::setMaxFPS(float maxFPS) {
        _maxFPS = maxFPS;
    }

    void FpsLimiter::begin() {
        _startTicks = SDL_GetTicks();
    }

    float FpsLimiter::end() {
        calculateFPS();

        float frameTicks = SDL_GetTicks() - _startTicks;
        //Limit the FPS to the max FPS
        if (1000.0f / _maxFPS > frameTicks) {
            SDL_Delay((Uint32)(1000.0f / _maxFPS - frameTicks));
        }

        return _fps;
    }

    void FpsLimiter::calculateFPS() {
        //The number of frames to average
        static const int NUM_SAMPLES = 25;
        //Stores all the frametimes for each frame that we will average
        static float frameTimes[NUM_SAMPLES];
        //The current frame we are on
        static int currentFrame = 0;
        //the ticks of the previous frame
        static float prevTicks = SDL_GetTicks();

        //Ticks for the current frame
        float currentTicks = SDL_GetTicks();

        //Calculate the number of ticks (ms) for this frame
        _frameTime = currentTicks - prevTicks;
        frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

        //current ticks is now previous ticks
        prevTicks = currentTicks;

        //The number of frames to average
        int count;

        currentFrame++;
        if (currentFrame < NUM_SAMPLES) {
            count = currentFrame;
        } else {
            count = NUM_SAMPLES;
        }

        //Average all the frame times
        float frameTimeAverage = 0;
        for (int i = 0; i < count; i++) {
            frameTimeAverage += frameTimes[i];
        }
        frameTimeAverage /= count;

        //Calculate FPS
		if (frameTimeAverage > 0) {
			_fps = 1000.0f / frameTimeAverage;
		}
		else {
			_fps = ENGINE_targetFPS;
		}
    }

}
