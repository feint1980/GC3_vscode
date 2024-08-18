#pragma once 

#include "GUI_icon.h"
#include "F_Lua_BaseEntity.h"

class BattleScene;

class GUI_handler
{
public:
    GUI_handler();
    ~GUI_handler();
    

    void init(const std::string & selectionTexturePath, const glm::vec2 & dim);

    void draw(Feintgine::SpriteBatch & spriteBatch);
    void update(float deltaTime);

    void handleInput(Feintgine::InputManager & inputManager, lua_State * luaState);

    void addIcon(GUI_icon * icon);

    void removeIcon(GUI_icon * icon);

    void setIconPos(GUI_icon *  icon, const glm::vec2 & pos);

    void setPhase(int phaseType, int sides);

    void registerBattleScene(BattleScene * scene);
    
    void registerCamera(Feintgine::Camera2D * camera);

    void setFocusColor(const Feintgine::Color & color);

    GUI_icon * getSelectedIcon(GUI_icon * icon);

    private :
    std::vector<GUI_icon * > m_icons;

    GUI_icon * m_selectedIcon = nullptr;

    EmptyObject m_selectionZone;

    int m_phaseType = 0; // 0 -> skill/items, 1 -> slot
    int m_SelectionSide = 0; // 1 -> left, 2 -> right , 3 -> both

    BattleScene * m_battleScene = nullptr;
    Feintgine::Camera2D * m_cam;

};
