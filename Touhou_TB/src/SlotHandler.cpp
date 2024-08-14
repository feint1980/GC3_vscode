#include "SlotHandler.h"
#include "BattleScene.h"

SlotHandler::SlotHandler()
{
    
}

SlotHandler::~SlotHandler()
{

}

Slot * SlotHandler::addSlot(int row, int colum, int side)
{
    Slot * slot = new Slot();
    slot->init(row, colum, side);
    m_slots.push_back(slot);
    return slot;
}

void SlotHandler::setSelectTargetSlot(Slot * slot)
{
    m_selectTargetSlot = slot;
    m_isMoving = true;
}

void SlotHandler::setActive(bool val)
{
    m_isActive = val;
    
}

void SlotHandler::draw(Feintgine::SpriteBatch & spriteBatch)
{
    for(int i = 0 ; i < m_slots.size(); i++)
    {
        m_slots[i]->draw(spriteBatch);
    }
    if(m_isActive)
    {
        m_hoveredSlot.draw(spriteBatch);
    }
}

void SlotHandler::update(float deltaTime)
{
    for(int i = 0 ; i < m_slots.size(); i++)
    {
        m_slots[i]->update(deltaTime);
    }
    if(m_selectTargetSlot)
    {   
        if(m_isMoving)
        {
            float distance = glm::length(m_hoveredSlot.getPos() - m_selectTargetSlot->getPos());
            glm::vec2 offset(0,10);
            if(distance > 2.5f)
            {
                m_hoveredSlot.setPos(glm::mix(m_hoveredSlot.getPos(), m_selectTargetSlot->getPos() + offset, 0.25f));
            }
            else
            {
                m_hoveredSlot.setPos(m_selectTargetSlot->getPos() + offset);
                m_isMoving = false;
            }
        }
    }
}



void SlotHandler::handleInput(Feintgine::InputManager & inputManager)
{

}

void SlotHandler::init(BattleScene * scene, Feintgine::Camera2D * camera)
{
    m_scene = scene;
    m_camera = camera;
    m_isActive = false;
    m_hoveredSlot.init(Feintgine::ResourceManager::getTexture("./Assets/Textures/circle.png"),
    glm::vec2(0, 0), glm::vec2(120, 40), Feintgine::Color(0, 255, 0, 255));
}