
#include "GUI_handler.h"


GUI_handler::GUI_handler()
{

}


GUI_handler::~GUI_handler()
{

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

