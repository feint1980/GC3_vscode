#ifndef COMBAT_GUIDOCK_CHARACTERINFO_H
#define COMBAT_GUIDOCK_CHARACTERINFO_H

#include <TextRenderer.h>
#include "TB_EmptyObject.h"
#include <ResourceManager.h>
#include "LuaManager.h"

class CombatGUIDock_CharacterInfo 
{
public:
    CombatGUIDock_CharacterInfo();
    ~CombatGUIDock_CharacterInfo();

    void init(const std::string & scriptFilePath);

    void loadBackGround(const std::string & filePath);

    void draw(Feintgine::SpriteBatch & spriteBatch);

    void update(float deltaTime);

private:

    TB_EmptyObject  m_background;

    glm::vec2 m_pos = glm::vec2(0, 0);


};


#endif