
#ifndef COMBAT_GUIDOCK_H
#define COMBAT_GUIDOCK_H

#include "CombatGUIPanel.h"
#include <ResourceManager.h>
#include "LuaManager.h"

class CombatGUIDock
{
public:
    CombatGUIDock();
    ~CombatGUIDock();

    void init();

    void draw(Feintgine::SpriteBatch & spriteBatch);

    void update(float deltaTime);
    
private:

    lua_State * m_script = nullptr;

    TB_EmptyObject  m_backgroundDock;  
    CombatGUIPanel  m_leftPanel;
    CombatGUIPanel  m_rightPanel;

};


#endif // COMBAT_GUIDOCK_H