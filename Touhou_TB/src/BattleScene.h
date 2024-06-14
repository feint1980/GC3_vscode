#pragma once

#include <ResourceManager.h>
#include "F_Lua_BaseEntity.h"


class BattleScene
{
public:
    BattleScene();
    ~BattleScene();


    void draw(Feintgine::SpriteBatch & spriteBatch);
    void update(float deltaTime);
protected:

    lua_State * m_script;


    std::vector<F_Lua_BaseEntity *> m_luaEntities;



};