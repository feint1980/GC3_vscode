
#include "ControlHandler.h"


int lua_ControlHandler_Cursor_Set(lua_State * script)
{
    if(lua_gettop(script) != 3)
    {
        std::cout << "lua_ControlHandler_Cursor_Set Error\n";
        return -1;
    }
    else
    {
        
        ControlHandler * controlHandler = static_cast<ControlHandler*>(lua_touserdata(script, 1));
        int x = lua_tonumber(script, 2);
        int y = lua_tonumber(script, 3);

        // std::cout << "x : " << x << " y : " << y << controlHandler->getWindow() << "\n";
        SDL_WarpMouseInWindow(controlHandler->getWindow(), x, y);
    }
    return 0;
}

int lua_ControlHandler_Cursor_Get(lua_State * script)
{
    if(lua_gettop(script) != 0)
    {
        std::cout << "lua_ControlHandler_Cursor_Get Error\n";
        return -1;
    }
    else
    {
        int x = 0;
        int y = 0;
        SDL_GetMouseState(&x, &y);
        lua_pushnumber(script, x);
        lua_pushnumber(script, y);
    }
    return 2;
}

int lua_ControlHandler_Cursor_SendLeftClickEvent(lua_State * script)
{
    if (lua_gettop(script) != 4)
    {
        std::cout << "lua_ControlHandler_Cursor_SendLeftClickEvent Error\n";
        return -1;
    }
    else
    {

        ControlHandler * controlHandler = static_cast<ControlHandler*>(lua_touserdata(script, 1));
        int numberOfClick = lua_tonumber(script, 2);
        int x = lua_tonumber(script, 3);
        int y = lua_tonumber(script, 4);
        
        std::cout << "number of click : " << numberOfClick << "\n";
        for (int i = 0; i < numberOfClick; i++)
        {
            SDL_Event down;
            down.type = SDL_MOUSEBUTTONDOWN;
            down.button.button = SDL_BUTTON_LEFT;
            down.button.state = SDL_PRESSED;
            down.button.clicks = 1;
            down.button.x = x;
            down.button.y = y;
            controlHandler->sendEvent(down);
            SDL_PushEvent(&down);
            // std::cout << "sent a left click  " << SDL_PushEvent(&down) << "\n";
            
            // tgui::Gui::handleEvent(down);
            SDL_Delay(100);

            SDL_Event up;
            up.type = SDL_MOUSEBUTTONUP;
            up.button.button = SDL_BUTTON_LEFT;
            up.button.state = SDL_RELEASED;
            up.button.clicks = 1;
            up.button.x = x;
            up.button.y = y;
            controlHandler->sendEvent(up);
            SDL_PushEvent(&up);
            // std::cout << "sent a left click up " << SDL_PushEvent(&up) << "\n";
            std::cout << "sent a left click \n";
            
        }
        return 0;
    }
    return 0;
}


// ===================

ControlHandler::ControlHandler()
{

}

void ControlHandler::sendEvent(const SDL_Event & evnt)
{
    if(m_tgui)
    {
        std::cout << "send event " << evnt.type << "\n";
        m_tgui->getTGUI()->handleEvent(evnt);
    }
}

ControlHandler::~ControlHandler()
{
}

void ControlHandler::init(lua_State * script,SDL_Window * window, TGUIScriptingManager * tgui)
{
    m_script = script; 
    m_window = window;
    m_tgui = tgui;
    std::cout << "Init with SDL window : " << m_window << "\n";
    // init lua component
    if(LuaManager::Instance()->checkLua(m_script, luaL_dofile(m_script, "../../Lua/system/Input/controlHandler.lua")))
    {
        std::cout << "Run script OK \n";
    }

    lua_getglobal(m_script, "ControlHandler_Init");
    if(lua_isfunction(m_script, -1))
    {
        lua_pushlightuserdata(m_script, this);
        std::cout << "pass ref : " << this << "\n";
        const int argc = 1;
        const int returnCount = 0;
        if(LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, argc, returnCount, 0)))
        {
            std::cout << "Init Input module in C++ \n";
        }
    }
    lua_register(m_script, "cpp_ControlHandler_Cursor_Set", lua_ControlHandler_Cursor_Set);
    lua_register(m_script, "cpp_ControlHandler_Cursor_Get", lua_ControlHandler_Cursor_Get);
    lua_register(m_script, "cpp_ControlHandler_Cursor_SendLeftClickEvent", lua_ControlHandler_Cursor_SendLeftClickEvent);
}

void ControlHandler::update(float deltaTime)
{

}

void ControlHandler::handleInput(Feintgine::InputManager & inputManager)
{
    unsigned int signal = 0;
    if(inputManager.isKeyPressed(SDLK_LEFT) ) //|| inputManager.isKeyPressed(SDLK_a)
    {
        signal |= 1;
    }

    if(inputManager.isKeyPressed(SDLK_RIGHT) ) // || inputManager.isKeyPressed(SDLK_d)
    {
        signal |= 2;
    }

    if(inputManager.isKeyPressed(SDLK_UP) ) //|| inputManager.isKeyPressed(SDLK_w)
    {
        signal |= 4;
    }

    if(inputManager.isKeyPressed(SDLK_DOWN) ) //|| inputManager.isKeyPressed(SDLK_s)
    {
        signal |= 8;
    }

    if(inputManager.isKeyPressed(SDLK_RETURN))
    {
        signal |= 16;
    }

    if(inputManager.isKeyPressed(SDLK_ESCAPE))
    {
        signal |= 32;
    }
    
    if(inputManager.isKeyPressed(SDL_BUTTON_LEFT))
    {
        signal |= 64;
    }
    
    if(signal > 0 )
    {
        lua_getglobal(m_script, "ControlHandler_DispatchSignal");
		if (lua_isfunction(m_script, -1))
		{
            lua_pushlightuserdata(m_script, this);
            lua_pushlightuserdata(m_script, m_tgui);
			lua_pushnumber(m_script, signal);

            const int argc = 3;
            const int returnCount = 0;
			if (!LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, argc, returnCount, 0)))
			{
				std::cout << "call handleInput failed \n";
			}
		}
    }
}