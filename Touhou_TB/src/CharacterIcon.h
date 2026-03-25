
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

    void setSpeed(float speed) { m_speed = speed; }
    void setSpeedChange(int changeValue) 
    {
        m_speedChange = changeValue;
        m_speedChangeTextPos = m_pos;
        m_isUpdateSpeedChange = 1;    
        m_speedChangeTextPosOffset = m_pos;
        m_speedChangeTextPosOffset.y -= (m_dim.y * .65f);

    }
    float getSpeed() { return m_speed; }
    int getSpeedChange() { return m_speedChange; }

    void setDisplaySpeed(float speed) { m_displaySpeed = speed; }

    void removeSpeedChange() { m_speedChange = 0; }

    void setTargetPos(const glm::vec2 & pos) 
    { 
        m_targetPos = pos; 
        m_isUpdateMovement = true;
    }

    void setOrder(int order) { m_order = order; }
    int getOrder() { return m_order; }


    int getUpdateSpeedChangeState() { return m_isUpdateSpeedChange; }
    void setUpdateSpeedChangeState(int state) { m_isUpdateSpeedChange = state; 
    m_counter = 0; }

    // void setUpdat
private:

    void updateMovement(float deltaTime);
    void updateSpeedChange(float deltaTime);

    EmptyObject m_portrait;
    EmptyObject m_border;
    int m_side = 0;
    float m_speed = 0;
    float m_displaySpeed = 0;
    int m_speedChange = 0;
    bool m_isInit = false;

    int m_order = 0;
    bool m_isUpdateMovement = false;
    int m_isUpdateSpeedChange = 0;

    float m_counter = 0;

    glm::vec2 m_pos = glm::vec2(0, 0);
    glm::vec2 m_dim = glm::vec2(0, 0);
    glm::vec2 m_targetPos = glm::vec2(0, 0);
    glm::vec2 m_displaySpeedPos = glm::vec2(0, 0);
    glm::vec2 m_speedChangeTextPos = glm::vec2(0, 0);
    glm::vec2 m_speedChangeTextPosOffset = glm::vec2(0, 0);
};


#endif // CHARACTER_ICON_H
