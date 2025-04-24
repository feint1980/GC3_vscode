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
    // here
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

// void W_Player::handleInput(Feintgine::InputManager & inputManager)
// {
 
// }

