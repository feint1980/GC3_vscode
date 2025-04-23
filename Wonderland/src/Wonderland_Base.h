#pragma once
#include <ResourceManager.h>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SDL-TTF-OpenGL3.hpp>

#include <Camera2D.h>
#include <unordered_map>
#include <memory>
#include "W_EntityManipulator.h"


class Wonderland_Base
{
public:
    // Initialize
    Wonderland_Base();
    ~Wonderland_Base();
    void init(Feintgine::Camera2D * camera);
    W_BaseEntity * createEntity(const std::string & entityName, const std::string & animPath, const glm::vec2 & pos);
    // Display
    void draw(Feintgine::SpriteBatch & spriteBatch);
    void drawGUI();
    // Logic update
    void update(float deltaTime);
    void handleInput(Feintgine::InputManager & inputManager);
    // add manipulator
    void addEntityManipulator(W_EntityManipulator * entityManipulator);
    void addNonWaitEntityManipulator(W_EntityManipulator * entityManipulator);

    W_BaseEntity * getEntityByName(const std::string & name);

private:
    std::vector<W_EntityManipulator > m_entityManipulators;
    std::vector<std::unique_ptr<W_BaseEntity>> m_entities;
    std::unordered_map<std::string, W_BaseEntity * > m_entityMap;
    
    lua_State * m_script = nullptr;
    Feintgine::Camera2D * m_camera = nullptr;

};


