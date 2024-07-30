#pragma once

#include <ResourceManager.h>
#include "F_Lua_BaseEntity.h"
#include "Slot.h"


class BattleScene
{
public:
    BattleScene();
    ~BattleScene();

    void init(Feintgine::Camera2D * camera);

    Slot * addSlot(int row, int colum, int side);

    void draw(Feintgine::SpriteBatch & spriteBatch);
    void update(float deltaTime);

    void handleInput(Feintgine::InputManager & inputManager);
protected:

    lua_State * m_script;

    std::vector<F_Lua_BaseEntity *> m_luaEntities;
    std::vector<Slot *> m_slots;

    Feintgine::Camera2D * m_camera;

};