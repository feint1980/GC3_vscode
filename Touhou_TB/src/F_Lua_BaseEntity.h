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

    void init(Slot * slot, const std::string & animationPath, const glm::vec2 & scale = glm::vec2(1.0f, 1.0f));

    void setAttribute(const std::string & attributeName, int value);

    void setAttribute(Attribute attribute, float value);

    void setPos(const glm::vec2 & pos);

    void playAnimation(const std::string & animationName, int time = -1);

    bool isAnimationStoped() const ;

    Attribute getAttributeByName(const std::string & attributeName);
    
    void setTargetSlot(Slot * slot);

    Slot * getTargetSlot() const { return m_moveTargetSlot; }

    float getYOffset() const { return m_yOffset; }

    glm::vec2 getPos() const { return m_pos; }

    bool isActive() const { return m_isActive; }

    void setActive(bool value);

    Slot * getCurrentSlot() const { return m_currentSlot; }

    

protected:

    Slot * m_currentSlot;
    Slot * m_moveTargetSlot;

    bool m_isActive = false;

    bool m_isMoving = false;

    glm::vec2 m_startPos;
    glm::vec2 m_endPos;
    float m_elaspedTime = 0.0f;
    float m_completionTime = 0.0f;    
    glm::vec2 m_pos;
    glm::vec2 m_scale;
    float m_yOffset  ;

    Feintgine::F_AnimatedObject m_animation;

    float m_strength;
    float m_vitality;
    float m_dexterity;
    float m_agility;
    float m_intelligence;
    float m_wisdom;

};