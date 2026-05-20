#include "CombatGUIDock_CharacterInfo.h"


CombatGUIDock_CharacterInfo::CombatGUIDock_CharacterInfo()
{

}
CombatGUIDock_CharacterInfo::~CombatGUIDock_CharacterInfo()
{

}


void CombatGUIDock_CharacterInfo::init(const std::string & filePath)
{

}
void CombatGUIDock_CharacterInfo::draw(Feintgine::SpriteBatch & spriteBatch)
{

}
void CombatGUIDock_CharacterInfo::update(float deltaTime)
{

}

void CombatGUIDock_CharacterInfo::loadBackGround(const std::string & filePath)
{
    m_background.init(Feintgine::ResourceManager::getTexture(filePath), m_pos, glm::vec2(850, 200), Feintgine::Color(255, 255, 255, 255));
}
