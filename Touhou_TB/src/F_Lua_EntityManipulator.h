#pragma once

#include <F_oEvent.h>
#include "F_Lua_BaseEntity.h"


enum EntityState
{
    Move = 0,
    Animation,
    None,
};

class F_Lua_EntityManipulator
{
public:
    F_Lua_EntityManipulator();
    ~F_Lua_EntityManipulator();

    void moveToSlot(F_Lua_BaseEntity * entity, Slot * slot, float time);

    void playAnimation(F_Lua_BaseEntity * entity, const std::string & animationName, int time = -1, float totalTime = 500.0f);

    EntityState getState() const { return m_state; }

    bool update(float deltaTime);

    F_Lua_BaseEntity * getEntity() const { return m_entity; }

protected:

    float m_elaspedTime;
    float m_completionTime;

    bool m_animationUseTime = false;

    F_Lua_BaseEntity * m_entity = nullptr;
    glm::vec2 m_startPos;

	glm::vec2 m_endPos;


    EntityState m_state = EntityState::None;
};