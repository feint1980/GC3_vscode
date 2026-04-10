
#ifndef COMBAT_GUIDOCK_H
#define COMBAT_GUIDOCK_H

#include "CombatGUIPanel.h"

#include "LuaManager.h"

class CombatGUIDock
{
public:
    CombatGUIDock();
    ~CombatGUIDock();

    void init();

    void draw(Feintgine::SpriteBatch & spriteBatch);

    void update(float deltaTime);

    CombatGUIPanel *getPanel(bool isLeft);

private:

    lua_State * m_script = nullptr;

    TB_EmptyObject  m_backgroundDock;  
    CombatGUIPanel  m_leftPanel;
    CombatGUIPanel  m_rightPanel;

    TB_EmptyObject  m_currentCharacterAvatar;
    // TB_EmptyObject  m_rightPanelDock;

};


#endif // COMBAT_GUIDOCK_H