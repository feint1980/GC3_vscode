
#include "ControlHandler.h"

ControlHandler::ControlHandler()
{
}

ControlHandler::~ControlHandler()
{
}

void ControlHandler::init(lua_State * script)
{
    m_script = script; 

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
}

void ControlHandler::update(float deltaTime)
{

}

void ControlHandler::handleInput(Feintgine::InputManager & inputManager)
{
    unsigned int signal = 0;
    if(inputManager.isKeyPressed(SDLK_LEFT) || inputManager.isKeyPressed(SDLK_a))
    {
        signal |= 1;
    }

    if(inputManager.isKeyPressed(SDLK_RIGHT) || inputManager.isKeyPressed(SDLK_d))
    {
        signal |= 2;
    }

    if(inputManager.isKeyPressed(SDLK_UP) || inputManager.isKeyPressed(SDLK_w))
    {
        signal |= 4;
    }

    if(inputManager.isKeyPressed(SDLK_DOWN) || inputManager.isKeyPressed(SDLK_s))
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
    
    if(signal > 0 )
    {
        lua_getglobal(m_script, "ControlHandler_DispatchSignal");
		if (lua_isfunction(m_script, -1))
		{

			lua_pushnumber(m_script, signal);

			if (!LuaManager::Instance()->checkLua(m_script, lua_pcall(m_script, 1, 1, 0)))
			{
				std::cout << "call handleInput failed \n";
			}
		}
    }


}