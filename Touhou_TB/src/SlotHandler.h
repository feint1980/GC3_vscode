

#pragma once
#include "Slot.h"

class BattleScene;
class SlotHandler
{
public:
    SlotHandler();
    ~SlotHandler();


    void init(BattleScene * scene, Feintgine::Camera2D * camera);

    Slot * addSlot(int row, int colum, int side);

    void draw(Feintgine::SpriteBatch & spriteBatch);

    void update(float deltaTime);

    void handleInput(Feintgine::InputManager & inputManager);

    void setActive(bool val);

    void setSelectTargetSlot(Slot * slot);

    void setValidTargetSlot(bool value);

private :

    std::vector<Slot *> m_slots;

    std::vector<Slot *> m_selectedSlots;

    EmptyObject m_hoveredSlot;

    BattleScene * m_scene = nullptr;

    Feintgine::Camera2D * m_camera = nullptr; 

    Slot * m_selectTargetSlot = nullptr;

    bool m_isMoving = false; 

    bool m_isValidTargetSlot = false;

    bool m_isActive = false;

};