
#ifndef CHARACTER_ICON_H
#define CHARACTER_ICON_H

#include "EmptyObject.h"
#include <ResourceManager.h>
#include <TextRenderer.h>
class CharacterIcon
{
public:
    CharacterIcon();
    ~CharacterIcon();

    void init(const std::string & texturePath,int side , int order, const glm::vec2 & dim);

    void draw(Feintgine::SpriteBatch & spriteBatch);

    void drawText(TextRenderer * textRenderer);

    void setPos(const glm::vec2 & pos)
    {
        m_portrait.setPos(pos);
        m_border.setPos(pos);
    }

    void update(float deltaTime);

    void setSpeed(int speed) { m_speed = speed; }
    void setSpeedRoll(int speed) 
    {
        m_speedRoll = speed;
        m_rollTextPos = m_pos;
        m_isUpdateRoll = 1;    
        m_rollTextPosOffset = m_pos;
        m_rollTextPosOffset.y -= (m_dim.y * .65f);

    }
    int getSpeed() { return m_speed; }
    int getSpeedRoll() { return m_speedRoll; }

    void setDisplaySpeed(int speed) { m_displaySpeed = speed; }

    void removeRoll() { m_speedRoll = 0; }

    void setTargetPos(const glm::vec2 & pos) 
    { 
        m_targetPos = pos; 
        m_isUpdateMovement = true;
    }

    void setOrder(int order) { m_order = order; }
    int getOrder() { return m_order; }


    int getUpdateRollState() { return m_isUpdateRoll; }
    void setUpdateRollState(int state) { m_isUpdateRoll = state; 
    m_counter = 0; }

    // void setUpdat
private:

    void updateMovement(float deltaTime);
    void updateRoll(float deltaTime);

    EmptyObject m_portrait;
    EmptyObject m_border;
    int m_side = 0;
    int m_speed = 0;
    int m_displaySpeed = 0;
    int m_speedRoll = 0;
    bool m_isInit = false;

    int m_order = 0;
    bool m_isUpdateMovement = false;
    int m_isUpdateRoll = 0;

    float m_counter = 0;

    glm::vec2 m_pos = glm::vec2(0, 0);
    glm::vec2 m_dim = glm::vec2(0, 0);
    glm::vec2 m_targetPos = glm::vec2(0, 0);
    glm::vec2 m_displaySpeedPos = glm::vec2(0, 0);
    glm::vec2 m_rollTextPos = glm::vec2(0, 0);
    glm::vec2 m_rollTextPosOffset = glm::vec2(0, 0);
};


#endif // CHARACTER_ICON_H
