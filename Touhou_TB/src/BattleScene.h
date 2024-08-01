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

    F_Lua_BaseEntity * addEntity(Slot * slot, const std::string & animationPath, const glm::vec2 & scale = glm::vec2(1.0f, 1.0f));

    void draw(Feintgine::SpriteBatch & spriteBatch);
    void update(float deltaTime);

    void handleInput(Feintgine::InputManager & inputManager);

    void pickActiveEntity(F_Lua_BaseEntity * entity);

protected:

    lua_State * m_script;

    F_Lua_BaseEntity * m_currentEntity = nullptr;

    std::vector<F_Lua_BaseEntity *> m_entities;
    std::vector<Slot *> m_slots;

    Feintgine::Camera2D * m_camera;

};