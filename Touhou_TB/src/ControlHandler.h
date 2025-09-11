#ifndef _CONTROL_HANDLER_
#define _CONTROL_HANDLER_

#include <InputManager.h>
#include "LuaManager.h"
#include <Window.h>
#include "../../TGUI_theme/ThemeCreator.hpp"

class ControlHandler
{
public:
    ControlHandler();
    ~ControlHandler();

    void init(lua_State * script,SDL_Window * window, tgui::Gui * tgui);
    void update(float deltaTime);
    void handleInput(Feintgine::InputManager & inputManager);
    SDL_Window * getWindow() const { return m_window; }

    void sendEvent(const SDL_Event & evnt);

private:

    lua_State * m_script = nullptr;
    SDL_Window * m_window = nullptr;
    tgui::Gui * m_tgui = nullptr;

};

#endif