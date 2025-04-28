#include "W_Player.h"

W_Player::W_Player()
{

}
W_Player::~W_Player()
{

}

void W_Player::update(float deltaTime)
{
    m_animations.update(deltaTime); 
    // movement input 
    if(m_movementFlag != 0)
    {
        // 1 = left, 2 = right, 4 = up, 8 = down
        //check if flag has bit 1
        glm::vec2 moveSpeed = glm::vec2(0, 0);
        m_movement = 0;
        if(m_movementFlag & 1)
        {
            m_movement |= 1;
            moveSpeed.x = -m_walkSpeed  ;
        }
        //check if flag has bit 2
        if(m_movementFlag & 2)
        {
            m_movement |= 1;
            moveSpeed.x = m_walkSpeed  ;
        }
        //check if flag has bit 4
        if(m_movementFlag & 4)
        {
            m_movement |= 2;
            moveSpeed.y = m_walkSpeed  ;
        }
        //check if flag has bit 8
        if(m_movementFlag & 8)
        {
            m_movement |= 2;
            moveSpeed.y = -m_walkSpeed ;
        }
        if(m_movement & 1 && m_movement & 2)
        {
            m_crossScale = 0.75f;
        }
        else
        {
            m_crossScale = 1.0f;
        }
        m_pos += (moveSpeed * m_crossScale) * deltaTime;
    }
    m_animations.setPos(m_pos);
}

void W_Player::initCharacter(const std::string & animationPath, int hpCap, int staminaCap)
{
    m_animations.init(animationPath);
    m_animations.playAnimation("idle_down");
    m_hpCap = hpCap;
    m_staminaCap = staminaCap;
    m_hp = m_hpCap;
    m_stamina = m_staminaCap;
    m_pos = glm::vec2(0, 0);
}

void W_Player::setAttribute(W_PlayerAtt att, float value)
{
    switch (att)
    {
    case W_PlayerAtt::hp:
        m_hp = value;
        break;
    case W_PlayerAtt::hpCap:
        m_hpCap = value;
        break;
    case W_PlayerAtt::stamina:
        m_stamina = value;
        break;
    case W_PlayerAtt::staminaCap:
        m_staminaCap = value;
        break;
    case W_PlayerAtt::walkSpeed:
        m_walkSpeed = value;
        break;
    case W_PlayerAtt::runSpeedScale:
        m_runSpeedScale = value;
        break;
    default:
        std::cout << "Unknown attribute set \n";
        break;
    }
}

void W_Player::setAttribute(const std::string & att, float value)
{
    setAttribute(getAttribute(att), value);
}

W_PlayerAtt W_Player::getAttribute(const std::string & att)
{
    std::string lowerAtt = att;
    std::transform(lowerAtt.begin(), lowerAtt.end(), lowerAtt.begin(), [](unsigned char c) { return std::tolower(c); });    

    if (lowerAtt == "hp")
    {
        return W_PlayerAtt::hp; 
    }
    else if (lowerAtt == "hpcap")
    {
        return W_PlayerAtt::hpCap;
    }
    else if (lowerAtt == "stamina")
    {
        return W_PlayerAtt::stamina;
    }
    else if (lowerAtt == "staminacap")
    {
        return W_PlayerAtt::staminaCap;
    }
    else if (lowerAtt == "walkspeed")
    {
        return W_PlayerAtt::walkSpeed;
    }
    else if (lowerAtt == "runspeedscale")
    {
        return W_PlayerAtt::runSpeedScale;
    }
    else
    {
        std::cout << "Unknown attribute requested " << att << "\n";
        return W_PlayerAtt::unknown;
    }
}