#ifndef _CONTROL_HANDLER_
#define _CONTROL_HANDLER_

#include <InputManager.h>
#include "LuaManager.h"
#include <Window.h>

class ControlHandler
{
public:
    ControlHandler();
    ~ControlHandler();

    void init(lua_State * script);
    void update(float deltaTime);
    void handleInput(Feintgine::InputManager & inputManager);

private:

    lua_State * m_script = nullptr;

};

#endif