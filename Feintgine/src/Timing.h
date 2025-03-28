
#ifndef _TIMMING_H_
#define _TIMMING_H_
#include "EngineSetting.h"
namespace Feintgine {

    ///Calculates FPS and also limits FPS
    class FpsLimiter {
    public:
        FpsLimiter();

        // Initializes the FPS limiter. For now, this is
        // analogous to setMaxFPS
        void init(float maxFPS);

        // Sets the desired max FPS
        void setMaxFPS(float maxFPS);

        void begin();

		float getFps() { return _fps; }

        // end() will return the current FPS as a float
        float end();
    private:
        // Calculates the current FPS
        void calculateFPS();

        // Variables
        float _fps;
        float _maxFPS;
        float _frameTime;
        unsigned int _startTicks;
    };

}

#endif