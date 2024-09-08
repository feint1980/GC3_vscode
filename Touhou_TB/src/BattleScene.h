#pragma once

#include <ResourceManager.h>
#include "F_Lua_BaseEntity.h"
#include "Slot.h"
#include "F_Lua_EntityManipulator.h"
#include "GUI_handler.h"
#include "SlotHandler.h"

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SDL-TTF-OpenGL3.hpp>

class BattleScene
{
public:
    BattleScene();
    ~BattleScene();

    void init(Feintgine::Camera2D * camera);

    Slot * addSlot(int row, int colum, int side);

    F_Lua_BaseEntity * addEntity(Slot * slot, const std::string & animationPath,const std::string & portraitPath, const glm::vec2 & scale = glm::vec2(1.0f, 1.0f));

    void draw(Feintgine::SpriteBatch & spriteBatch);

    void drawGUI();

    void update(float deltaTime);

    void handleInput(Feintgine::InputManager & inputManager);

    void pickActiveEntity(F_Lua_BaseEntity * entity);

    void setMoveTargetSlot(F_Lua_BaseEntity * entity, Slot * slot);

    void addEntityManipulator(F_Lua_EntityManipulator * entityManipulator);

    void addNonWaitEntityManipulator(F_Lua_EntityManipulator * entityManipulator);

    GUI_handler * createGUIHandler(const std::string & selectionTexturePath, const glm::vec2 & dim);

    SlotHandler * createSlotHandler();

    GUI_icon * createIcon(const std::string & texturePath, const glm::vec2 & pos, const glm::vec2 & dim);

    void GUIHandlerAddIcon(GUI_icon * icon);

    void GUIHandlerRemoveIcon(GUI_icon * icon);

    void GUIHandlerClearIcons();

    void SlotHandlerSetValidSlot(bool isValidSlot);

    void setPhase(int phaseType, int sides);

    void setGUIHandlerIconPos(GUI_icon * icon, const glm::vec2 & pos);

    void setGUIHandlerFocusColor(const Feintgine::Color & color);

    void setDescriptionBoxPos(const glm::vec2 & pos);

    void setDescriptionBoxDim(const glm::vec2 & dim);

    GUI_icon * setGUIHandlerSelectedIcon(GUI_icon * icon);

    void initTGUI(SDL_Window * window);

    bool checkIfSlotEmpty(Slot * slot);

    Feintgine::Camera2D * getCamera() const { return m_camera; }

    void clearEntityTasks(F_Lua_BaseEntity * entity);

    F_Lua_BaseEntity * getEntityBySlot(Slot * slot);

protected:

    lua_State * m_script;

    F_Lua_BaseEntity * m_currentEntity = nullptr;

    bool m_isMove = false;

    std::vector<F_Lua_BaseEntity *> m_entities;
  
  //  std::vector<Slot *> m_slots;

    SlotHandler * m_slotHandler = nullptr;

    std::vector<GUI_icon *> m_icons;

    std::vector<Slot * > m_selectedSlot;

    std::vector<F_Lua_EntityManipulator *> m_entityManipulators;

    std::vector<F_Lua_EntityManipulator *> m_nonWaitManipulators;

    Feintgine::Camera2D * m_camera;

    GUI_handler * m_guiHandler = nullptr;


    // TGUI section start
    tgui::Gui * m_tgui = nullptr;

    tgui::RichTextLabel::Ptr m_iconDescription = nullptr;
    tgui::RichTextLabel::Ptr m_iconName = nullptr;
    tgui::RichTextLabel::Ptr m_iconTurnCost = nullptr;
    tgui::RichTextLabel::Ptr m_iconManaCost = nullptr;


    EmptyObject m_descriptionBox;

    // TGUI section end

    int m_phaseType = 0; // 0 -> skill/items/icons, 1 -> slot
    int m_SelectionSide = 0; // 1 -> left, 2 -> right , 3 -> both
};