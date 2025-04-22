#pragma once

#include <F_oEvent.h>
#include "W_BaseEntity.h"



class W_EntityManipulator
{
public:
    W_EntityManipulator();
    ~W_EntityManipulator();

    void playAnimation(W_BaseEntity * entity, const std::string & animationName, int time = -1, float totalTime = 500.0f);

    bool update(float deltaTime);

    void setPosition(W_BaseEntity * entity, const glm::vec2 & pos);

    void waitTime(W_BaseEntity * entity, float time);

    W_BaseEntity * getEntity() const { return m_entity; }

private:

    float m_elaspedTime;
    float m_completionTime;

    W_BaseEntity * m_entity = nullptr;

};