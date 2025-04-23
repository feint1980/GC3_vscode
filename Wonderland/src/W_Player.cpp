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


void W_Player::initCharacter(const std::string & luaFile, lua_State * script)
{
    m_script = script;

    // register lua functions
}