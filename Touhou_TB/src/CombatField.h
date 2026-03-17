
#ifndef COMBAT_FIELD_H
#define COMBAT_FIELD_H
#include <GLSLProgram.h>
#include <Camera2D.h>
#include <vector>
#include <SpriteBatch.h>
#include <SDL2/SDL_keyboard.h>
#include <GLTexture.h>
#include <ResourceManager.h>

#include "LuaManager.h"

class CombatField
{
public:
    CombatField();
    ~CombatField();

    void init(const std::string & scriptPath, lua_State * script);

    void draw(Feintgine::SpriteBatch & spriteBatch);

    void update(float deltaTime);

private:

    lua_State * m_script = nullptr;

};


#endif // COMBAT_FIELD_H