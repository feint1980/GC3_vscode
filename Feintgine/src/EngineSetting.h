#ifndef _ENGINESETTING_H_
#define _ENGINESETTING_H_

extern float  ENGINE_targetFPS; 
extern double ENGINE_current_tick ;
const double ENGINE_tick_speed = 0.0166667;
extern bool ENGINE_isGameRunning;

void togglePause();

#endif