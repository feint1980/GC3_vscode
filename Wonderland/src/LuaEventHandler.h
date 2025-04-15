#ifndef _LUA_EVENT_HANDLER_H_
#define _LUA_EVENT_HANDLER_H_

#include <Window.h>
#include <InputManager.h>  
#include "LuaManager.h"

class LuaEventHandler
{
    public:
    LuaEventHandler();
    ~LuaEventHandler();
    void init(lua_State * script);
    void update(float deltaTime);

    void startCounting();
    void stopCounting();

    private:

    double m_time = 0.0f;
  
    float m_accumulator = 0.0f;

    lua_State * m_script = nullptr;

};


#endif // _LUA_EVENT_HANDLER_H_