#pragma once

#include <SpriteBatch.h>
#include <F_Sprite.h>
#include <F_AnimatedObject.h>
#include <LuaManager.h>
#include <F_oEvent.h>

#include "Slot.h"


enum Attribute
{
    Strength = 0,
    Vitality,
    Dexterity,
    Agility,
    Intelligence,
    Wisdom,
    Invalid
};


class F_Lua_BaseEntity
{
public:
    F_Lua_BaseEntity();
    ~F_Lua_BaseEntity();    

    void draw(Feintgine::SpriteBatch & spriteBatch);

    void update(float deltaTime);

    void init(Slot * slot, const std::string & animationPath, const glm::vec2 & scale );

    void setAttribute(const std::string & attributeName, int value);

    void setAttribute(Attribute attribute, float value);

    Attribute getAttributeByName(const std::string & attributeName);


protected:

    Slot * m_currentSlot;
    Slot * m_moveTargetSlot;


    glm::vec2 m_pos;
    glm::vec2 m_scale;

    Feintgine::F_AnimatedObject m_animation;

    float m_strength;
    float m_vitality;
    float m_dexterity;
    float m_agility;
    float m_intelligence;
    float m_wisdom;

};