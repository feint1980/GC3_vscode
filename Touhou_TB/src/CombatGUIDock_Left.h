#ifndef COMBAT_GUIDOCK_LEFT_H
#define COMBAT_GUIDOCK_LEFT_H

#include <TextRenderer.h>
#include "TB_EmptyObject.h"
#include <ResourceManager.h>

class CombatGUIDock_Left 
{
public:
    CombatGUIDock_Left();
    ~CombatGUIDock_Left();

    void init(const std::string & filePath);
    void draw(Feintgine::SpriteBatch & spriteBatch);
    void update(float deltaTime);


private:

    TB_EmptyObject  m_background;

    glm::vec2 m_pos = glm::vec2(0, 0);


};


#endif