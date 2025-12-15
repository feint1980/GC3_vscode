

#pragma once
#include "LuaManager.h"
#include <iostream>



class LuaTaskManager
{
public:
    LuaTaskManager()
    {

    }
    ~LuaTaskManager()
    {

    }

    void init(const std::string & scriptPath,lua_State * script);
    void update(float deltaTime);

    private:
    lua_State * m_script = nullptr;

};
