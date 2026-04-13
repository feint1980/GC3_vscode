
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

    float mX = 800;
    float invert = 1.0f;
    if (m_isLeft) invert = -1.0f;
    m_pos = glm::vec2(mX * invert, 0);

    m_backgroundDock.init(Feintgine::ResourceManager::getTexture("./Assets/Textures/frame.png"),m_pos, glm::vec2(250, 550),Feintgine::Color(255, 255, 255, 255));

}

void CombatGUIPanel::update(float deltaTime)
{
    m_backgroundDock.setPos(m_pos);
}
