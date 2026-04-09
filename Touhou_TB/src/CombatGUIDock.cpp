#include "CombatGUIDock.h"


CombatGUIDock::CombatGUIDock()
{


}

CombatGUIDock::~CombatGUIDock()
{

}

void CombatGUIDock::init()
{
    m_backgroundDock.init(Feintgine::ResourceManager::getTexture("./Assets/Textures/frame.png"),glm::vec2(0,0), glm::vec2(1600, 250),Feintgine::Color(255, 255, 255, 255));


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