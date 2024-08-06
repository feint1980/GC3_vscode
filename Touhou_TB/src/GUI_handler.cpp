
#include "GUI_handler.h"


GUI_handler::GUI_handler()
{

}


GUI_handler::~GUI_handler()
{

}

void GUI_handler::init(const std::string & selectionTexturePath,const glm::vec2 & dim)
{

    m_selectionZone.init(Feintgine::ResourceManager::getTexture(selectionTexturePath), glm::vec2(5000, 0), dim, Feintgine::Color(255, 255, 255, 255));
}

void GUI_handler::addIcon(GUI_icon * icon)
{
    if(icon)
    {
        m_icons.push_back(icon);

    }
   

}

void GUI_handler::setIconPos(GUI_icon *  icon, const glm::vec2 & pos)
{

    for(int i = 0; i < m_icons.size(); i++)
    {
        if(m_icons[i] == icon)
        {
            m_icons[i]->setPos(pos);
        }
    }
}

void GUI_handler::draw(Feintgine::SpriteBatch & spriteBatch)
{
    for(int i = 0; i < m_icons.size(); i++)
    {
        m_icons[i]->draw(spriteBatch);
    }

}

void GUI_handler::handleInput(Feintgine::InputManager & inputManager)
{

}

void GUI_handler::update(float deltaTime)
{
    for(int i = 0; i < m_icons.size(); i++)
    {
        m_icons[i]->update(deltaTime);
    }
}

