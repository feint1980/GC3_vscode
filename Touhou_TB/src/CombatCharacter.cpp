
#include "CSlot.h"
#include "CombatCharacter.h"


CombatCharacter::CombatCharacter()
{


}

CombatCharacter::~CombatCharacter()
{

}


void CombatCharacter::init(CSlot * slot, const std::string & animationPath,const std::string & portraitPath, const glm::vec2 & scale , int side)
{
    m_currentSlot = slot; 
    if(!m_currentSlot)
    {
        std::cout << "slot is null \n";
        return;
    }

    m_side = side;
    m_pos = m_currentSlot->getPos();
    m_scale = scale;

    m_animation.init(animationPath, m_scale);
    m_animation.setPos(m_pos);
    m_animation.setScale(m_scale);
    if(m_side == 2)
    {
        m_animation.setInvertAnimation();
    }
    m_animation.playAnimation("idle");
    m_yOffset = m_animation.getDim().y * 0.5f;

}

void CombatCharacter::draw(Feintgine::SpriteBatch & spriteBatch)
{
    // m_animation.setPos(m_pos + glm::vec2(0.0f, m_yOffset));
    // m_animation.draw(spriteBatch);
}

void CombatCharacter::update(float deltaTime)
{
    m_animation.update(deltaTime);
}