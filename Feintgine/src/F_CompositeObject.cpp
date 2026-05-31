

#include "F_CompositeObject.h"

namespace Feintgine
{

void F_CompositeObject::addObject( const std::string & spriteNameWithPacket, const glm::vec2 & posOffset, const glm::vec2 & scale, const Feintgine::Color & color, float angle, float depth)
{
    m_objectList.push_back({Feintgine::SpriteManager::Instance()->getSprite(spriteNameWithPacket), posOffset, scale, color, angle, depth});
}


void F_CompositeObject::draw(Feintgine::SpriteBatch & spriteBatch)
{

}


}