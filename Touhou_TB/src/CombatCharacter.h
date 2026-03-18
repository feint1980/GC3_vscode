#ifndef COMBATCHARACTER_H
#define COMBATCHARACTER_H

#include <F_AnimatedObject.h>
class Cslot;

// #include "../PacketDescription/CharacterDes.h"
class CombatCharacter
{
public:
    CombatCharacter();
    ~CombatCharacter();

    void init(CSlot * slot, const std::string & animationPath,const std::string & portraitPath, const glm::vec2 & scale , int side); 
    
    void draw(Feintgine::SpriteBatch & spriteBatch);

    void update(float deltaTime);

private:

    CSlot * m_currentSlot = nullptr;

    int m_side = 1;

    glm::vec2 m_pos;
    glm::vec2 m_scale;
    float m_yOffset = 0.0f;

    Feintgine::F_AnimatedObject m_animation;
    EmptyObject * m_portrait = nullptr;

    
};


#endif