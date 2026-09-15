#ifndef COMBAT_FIELD_SELECTOR_H
#define COMBAT_FIELD_SELECTOR_H

#include <ResourceManager.h>
#include "EmptyObject.h"

class CSlot;

class CombatField_Selector
{
public:
    CombatField_Selector();
    ~CombatField_Selector();

    void init(const std::string & texturePath, float yPosOffset);

    void draw(Feintgine::SpriteBatch & spriteBatch);

    void update(float deltaTime);

    void setDestination(const glm::vec2 & pos) {
        m_targetPos = pos;
        m_isMoving = true;
    }

    void setPos(const glm::vec2 & pos) { m_pos = pos; }

    void setIndex (const glm::ivec2 & index) { m_index = index; }

    void setHoverSlot(CSlot * slot);

    void setVisible(bool value) { m_visible = value; }

    void setColor(const Feintgine::Color & color) { m_selector.setColor(color); }

private:

    CSlot * m_currentSlot = nullptr;

    EmptyObject m_selector;
    glm::vec2 m_pos; 

    glm::vec2 m_targetPos = glm::vec2(0,0);

    float m_yPosOffset = 0.0f;
    glm::ivec2 m_index = glm::ivec2(0,0);

    bool m_isVisible = false;
    bool m_isMoving = false; 
    bool m_visible = false;

};

#endif 





