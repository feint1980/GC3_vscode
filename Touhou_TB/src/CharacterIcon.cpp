#include "CharacterIcon.h"

CharacterIcon::CharacterIcon()
{

}

CharacterIcon::~CharacterIcon()
{
    
}
void CharacterIcon::init(const std::string & texturePath, const glm::vec2 & dim)
{
    m_portrait.init(Feintgine::ResourceManager::getTexture(texturePath), glm::vec2(0),dim,Feintgine::Color(255, 255, 255, 255));
}

void CharacterIcon::draw(Feintgine::SpriteBatch & spriteBatch)
{
    m_portrait.draw(spriteBatch);
}


