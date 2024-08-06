#pragma once 

#include "GUI_icon.h"


class GUI_handler
{
public:
    GUI_handler();
    ~GUI_handler();
    

    void init(const std::string & selectionTexturePath, const glm::vec2 & dim);

    void draw(Feintgine::SpriteBatch & spriteBatch);
    void update(float deltaTime);

    void handleInput(Feintgine::InputManager & inputManager);

    void addIcon(GUI_icon * icon);

    void setIconPos(GUI_icon *  icon, const glm::vec2 & pos);

    private :
    std::vector<GUI_icon * > m_icons;


    EmptyObject m_selectionZone;


};
