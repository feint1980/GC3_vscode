#include "CombatField_Selector.h"

#include "CSlot.h"


CombatField_Selector::CombatField_Selector()
{

}


CombatField_Selector::~CombatField_Selector()
{

}


void CombatField_Selector::init(const std::string & texturePath, float yPosOffset)
{

    float tScale = 1.0f;
    m_selector.init(Feintgine::ResourceManager::getTexture(texturePath), glm::vec2(0, 0) , glm::vec2(120, 40) * tScale, Feintgine::Color(120, 255, 120, 255));

    m_yPosOffset = yPosOffset;
}

void CombatField_Selector::update(float deltaTime)
{
    if(!m_currentSlot)
    {
        return;
    }
    if(m_isMoving)
    {
        float distance = glm::length(m_targetPos - m_pos);
        glm::vec2 offset(0,10);
        if(distance > 2.5f)
        {
            m_selector.setPos(glm::mix(m_selector.getPos(), m_targetPos + offset, 0.25f));
        }
        else
        {
            m_selector.setPos(m_targetPos + offset);
            m_pos = m_targetPos;
            m_isMoving = false;
        }
    }
}

void CombatField_Selector::draw(Feintgine::SpriteBatch & spriteBatch)
{
    if(m_visible)
    {
        m_selector.draw(spriteBatch);
    }
    
}


void CombatField_Selector::setHoverSlot(CSlot * slot)
{
    if(slot)
    {
        if (m_currentSlot != slot) // must be difference slot
        {
            m_currentSlot = slot;
            m_isMoving = true;
            m_targetPos = slot->getPos();
        }
    }
    // m_currentSlot
}