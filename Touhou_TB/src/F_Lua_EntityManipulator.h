#pragma once

#include <F_oEvent.h>
#include "F_Lua_BaseEntity.h"


enum State
{
    Move = 0,
    Animation,
    Complete,
};

class F_Lua_EntityManipulator
{
public:
    F_Lua_EntityManipulator();
    ~F_Lua_EntityManipulator();


    void moveToSlot(F_Lua_BaseEntity * entity, Slot * slot, float time);

    void playAnimation(F_Lua_BaseEntity * entity, const std::string & animationName, int time = -1, float totalTime = 0.0f);

    bool update(float deltaTime);

protected:

    F_Lua_BaseEntity * m_entity = nullptr;


};