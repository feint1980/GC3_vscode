#include "CombatGUIDock.h"


CombatGUIDock::CombatGUIDock()
{


}

CombatGUIDock::~CombatGUIDock()
{

}

void CombatGUIDock::init()
{
    
}

void CombatGUIDock::draw(Feintgine::SpriteBatch & spriteBatch)
{   
    m_backgroundDock.draw(spriteBatch);
    m_leftPanel.draw(spriteBatch);
    m_rightPanel.draw(spriteBatch);
}

void CombatGUIDock::update(float deltaTime)
{

}