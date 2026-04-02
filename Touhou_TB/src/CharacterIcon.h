
#ifndef CHARACTER_ICON_H
#define CHARACTER_ICON_H

#include "EmptyObject.h"
#include <ResourceManager.h>
#include <TextRenderer.h>
#include "InfoHolder.h"

#define ICON_POS_CHANGE 1
#define ICON_SPEED_CHANGE 2

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
        m_state |= ICON_SPEED_CHANGE;

    }
    float getSpeed() { return m_speed; }
    int getSpeedChange() { return m_speedChange; }

    void setDisplaySpeed(float speed) { m_displaySpeed = speed; }

    void removeSpeedChange() { m_speedChange = 0; }

    void setTargetPos(const glm::vec2 & pos) 
    { 
        m_targetPos = pos; 
        m_isUpdateMovement = true;
        m_state |= ICON_POS_CHANGE;
        InfoHolder::getInstance()->getLuaEventPipeline()->sendPollSignal("TurnDisplayerIsReady", false);
    }

    void setOrder(int order) { m_order = order; }
    int getOrder() { return m_order; }

    glm::vec2 getPos() { return m_portrait.getPos(); }

    int getUpdateSpeedChangeState() { return m_isUpdateSpeedChange; }
    void setUpdateSpeedChangeState(int state) {
        
        m_isUpdateSpeedChange = state;
        
        m_counter = 0; 
        if(state == 0)
        {
            m_state &= ~ICON_SPEED_CHANGE;
            // InfoHolder::getInstance()->getLuaEventPipeline()->sendPollSignal("TurnDisplayerIsReady", true);
        } 

    }

    int getState() { return m_state; }
    void setState(int state) { m_state = state; }

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

    int m_state = 0;

    float m_counter = 0;

    glm::vec2 m_pos = glm::vec2(0, 0);
    glm::vec2 m_dim = glm::vec2(0, 0);
    glm::vec2 m_targetPos = glm::vec2(0, 0);
    glm::vec2 m_displaySpeedPos = glm::vec2(0, 0);
    glm::vec2 m_speedChangeTextPos = glm::vec2(0, 0);
    glm::vec2 m_speedChangeTextPosOffset = glm::vec2(0, 0);
};


#endif // CHARACTER_ICON_H
