#ifndef _CONTROL_HANDLER_
#define _CONTROL_HANDLER_

#include <InputManager.h>
#include "LuaManager.h"
#include <Window.h>
// #include "../../TGUI_theme/ThemeCreator.hpp"
#include "TGUIScriptingManager.h"

enum ControlSignalBit : uint64_t
{
    SIG_LEFT      = 1ULL << 0,
    SIG_RIGHT     = 1ULL << 1,
    SIG_UP        = 1ULL << 2,
    SIG_DOWN      = 1ULL << 3,
    SIG_RETURN    = 1ULL << 4,
    SIG_ESCAPE    = 1ULL << 5,
    SIG_MOUSE_L   = 1ULL << 6,
    SIG_MOUSE_R   = 1ULL << 7,
    SIG_ALT       = 1ULL << 8,
    SIG_CTRL      = 1ULL << 9,
    SIG_SHIFT     = 1ULL << 10,
    SIG_Q         = 1ULL << 11,
    SIG_W         = 1ULL << 12,
    SIG_E         = 1ULL << 13,
    SIG_R         = 1ULL << 14,
    SIG_A         = 1ULL << 15,
    SIG_S         = 1ULL << 16,
    SIG_D         = 1ULL << 17,
    SIG_F         = 1ULL << 18,
    SIG_Z         = 1ULL << 19,
    SIG_X         = 1ULL << 20,
    SIG_C         = 1ULL << 21,
    SIG_V         = 1ULL << 22,
    SIG_B         = 1ULL << 23,
    SIG_1         = 1ULL << 24,
    SIG_2         = 1ULL << 25,
    SIG_3         = 1ULL << 26,
    SIG_4         = 1ULL << 27,
    SIG_5         = 1ULL << 28,
    SIG_6         = 1ULL << 29,

    SIG_SPACE     = 1ULL << 30,

};

class ControlHandler
{
public:
    ControlHandler();
    ~ControlHandler();

    void init(lua_State * script,SDL_Window * window, TGUIScriptingManager * tgui);
    void update(float deltaTime);
    void handleInput(Feintgine::InputManager & inputManager);
    SDL_Window * getWindow() const { return m_window; }

    void sendEvent(const SDL_Event & evnt);

private:

    lua_State * m_script = nullptr;
    SDL_Window * m_window = nullptr;
    TGUIScriptingManager * m_tgui = nullptr;

};

#endif