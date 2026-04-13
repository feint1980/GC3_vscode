
#ifndef COMBAT_GUIDOCK_H
#define COMBAT_GUIDOCK_H

#include "CombatGUIPanel.h"
#include <TextRenderer.h>
#include "LuaManager.h"

class CombatGUIDock
{
public:
    CombatGUIDock();
    ~CombatGUIDock();

    void init();

    void draw(Feintgine::SpriteBatch & spriteBatch);

    void update(float deltaTime);

    void drawText(TextRenderer * textRenderer);

    void setCurrentCharacter(const std::string & characterID);

    CombatGUIPanel *getPanel(bool isLeft);

    // void setAvatar

private:

    lua_State * m_script = nullptr;

    TB_EmptyObject  m_backgroundDock;
    CombatGUIPanel  m_leftPanel;
    CombatGUIPanel  m_rightPanel;

    TB_EmptyObject  m_currentCharacterAvatar;

    std::string m_currentCharacterName;

    int m_currentHP = 0.0f;
    int m_maxHP = 0.0f;

    int m_currentMP = 0.0f;
    int m_maxMP = 0.0f;

    int m_currentSP = 0.0f;
    int m_maxSP = 0.0f;

    int m_currentAP = 0.0f;
    int m_maxAP = 0.0f;

};


#endif // COMBAT_GUIDOCK_H