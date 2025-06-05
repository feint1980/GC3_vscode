#pragma once

#include <SpriteBatch.h>
#include <F_Sprite.h>
#include <F_AnimatedObject.h>
#include <LuaManager.h>
#include <F_oEvent.h>

#include "Slot.h"
#include "../PacketDescription/CharacterDes.h"

class F_Lua_BaseEntity
{
public:
    F_Lua_BaseEntity();
    ~F_Lua_BaseEntity();    

    void draw(Feintgine::SpriteBatch & spriteBatch);

    void update(float deltaTime);

    void setCharacterDesc(CharacterDesc characterDesc) { m_characterDesc = characterDesc; 
    }

    CharacterDesc getCharacterDesc() { return m_characterDesc; }

    void init(Slot * slot, const std::string & animationPath,const std::string & portraitPath, const glm::vec2 & scale = glm::vec2(1.0f, 1.0f));

    void setAttribute(const std::string & attributeName, int value);

    void setAttribute(const std::string & attributeName, const std::string & value);

    void setAttribute(Attribute attribute, float value);

    void setAttribute(Attribute attribute, const std::string & value);

    float getFloatAttributeByName(const std::string & attributeName);

    std::string getStrAttributeByName(const std::string & attributeName);

    void setPos(const glm::vec2 & pos);

    void playAnimation(const std::string & animationName, int time = -1);

    bool isAnimationStoped() const ;

    void setTargetSlot(Slot * slot);

    Slot * getTargetSlot() const { return m_moveTargetSlot; }

    float getYOffset() const { return m_yOffset; }

    glm::vec2 getPos() const { return m_pos; }

    bool isActive() const { return m_isActive; }

    void setActive(bool value);

    void setSide(int side) 
    { 
        m_side = side;
        if(m_side == 2)
        {
            m_animation.setInvertAnimation();
        }
    }

    int getSide() const { return m_side; }

    Slot * getCurrentSlot() const { return m_currentSlot; }

    void setCurrentSlot(Slot * slot) { m_currentSlot = slot; }
    EmptyObject * getPortrait() const { return m_portrait; }

protected:

    Slot * m_currentSlot = nullptr;
    Slot * m_moveTargetSlot = nullptr; 

    int m_side = 1;

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
    EmptyObject * m_portrait = nullptr;

    CharacterDesc m_characterDesc;

};