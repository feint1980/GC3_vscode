
#include "CombatGUIPanel.h"


CombatGUIPanel::CombatGUIPanel()
{
    
}

CombatGUIPanel::~CombatGUIPanel()
{

}

void CombatGUIPanel::draw(Feintgine::SpriteBatch & spriteBatch)
{
    m_backgroundDock.draw(spriteBatch);    
}

void CombatGUIPanel::init(bool isLeft)
{
    m_isLeft = isLeft;
    m_backgroundDock.init(Feintgine::ResourceManager::getTexture("./Assets/Textures/frame.png"),glm::vec2(0,0), glm::vec2(1600, 250),Feintgine::Color(255, 255, 255, 255));

}

void CombatGUIPanel::update(float deltaTime)
{
    m_backgroundDock.setPos(m_pos);
}