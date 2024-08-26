#include "GUI_icon.h"



GUI_icon::GUI_icon()
{
}


GUI_icon::~GUI_icon()
{

}

void GUI_icon::init(const std::string & texturePath, const glm::vec2 & pos, const glm::vec2 & dim)
{
    m_icon.init(Feintgine::ResourceManager::getTexture(texturePath), pos, dim, Feintgine::Color(255, 255, 255, 255));
    m_icon.setDepth(10);
    


}

void GUI_icon::setPos(const glm::vec2 & pos)
{
    m_icon.setPos(pos);
}

void GUI_icon::setDim(const glm::vec2 & dim)
{
    m_icon.setDim(dim);
}

void GUI_icon::draw(Feintgine::SpriteBatch & spriteBatch)
{
    m_icon.draw(spriteBatch);
}

void GUI_icon::update(float deltaTime)
{
    // todo update
}
