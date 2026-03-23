#include "CharacterIcon.h"

CharacterIcon::CharacterIcon()
{

}

CharacterIcon::~CharacterIcon()
{
    
}
void CharacterIcon::init(const std::string & texturePath, int side,const glm::vec2 & dim)
{
    m_portrait.init(Feintgine::ResourceManager::getTexture(texturePath), glm::vec2(0),dim,Feintgine::Color(255, 255, 255, 255));
    m_side = side;
    Feintgine::Color red = Feintgine::Color(255, 0, 0, 255);
    Feintgine::Color blue = Feintgine::Color(0, 0, 255, 255);

    if(m_side == 1)
    {
        m_border.init(Feintgine::ResourceManager::getTexture("./Assets/TB_GUI/faces/face_border.png"), glm::vec2(0),dim * 1.05f,red);
    }
    else if (m_side == 2)
    {
        m_border.init(Feintgine::ResourceManager::getTexture("./Assets/TB_GUI/faces/face_border.png"), glm::vec2(0),dim * 1.05f,blue);
    }
    m_portrait.setDepth(2);
    m_portrait.setDepth(3);

}

void CharacterIcon::draw(Feintgine::SpriteBatch & spriteBatch)
{
    m_portrait.draw(spriteBatch);
    m_border.draw(spriteBatch);
}


