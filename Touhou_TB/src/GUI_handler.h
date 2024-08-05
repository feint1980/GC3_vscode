#pragma once 

#include "GUI_icon.h"


class GUI_handler
{
public:
    GUI_handler();
    ~GUI_handler();
    

    void init(const std::string & selectionTexturePath);

    void draw(Feintgine::SpriteBatch & spriteBatch);
    void update(float deltaTime);

    void handleInput(Feintgine::InputManager & inputManager);

    private :
    std::vector<GUI_icon * > m_icons;


    EmptyObject m_selectionZone;


};
