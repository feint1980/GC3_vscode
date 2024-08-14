
#include "Slot.h"

Slot::Slot()
{

}

Slot::~Slot()
{

}


void Slot::setTargetSlot(Slot * slot)
{
    m_targetSlot = slot;
    m_isMoving = true;
}

void Slot::init(int row, int colum, int side)
{
    m_index = glm::ivec2(row, colum);
    m_side = side;
    float xFactor = 150;
    float yFactor = -100;
    if(m_side == 1)
    {
        xFactor = -xFactor;
    }
    
    m_actualPos = glm::vec2(m_index.x * xFactor, m_index.y * yFactor);
    m_actualPos.y += 100; // up

    m_circle.init(Feintgine::ResourceManager::getTexture("./Assets/Textures/circle.png"), 
    m_actualPos, glm::vec2(120, 40), Feintgine::Color(255, 255, 0, 255));
}

void Slot::draw(Feintgine::SpriteBatch & spriteBatch)
{
    m_circle.draw(spriteBatch);
}

void Slot::update(float deltaTime)
{
    if (m_targetSlot)
    {
        if(m_isMoving)
        {
            float distance = glm::length(m_actualPos - m_targetSlot->getPos());
            if(distance > 2.5f)
            {
                m_actualPos = glm::mix(m_actualPos, m_targetSlot->getPos(), 0.1f);
            }
            else
            {
                m_actualPos = m_targetSlot->getPos();
                m_isMoving = false;
                m_index = m_targetSlot->getIndex();
                //m_targetSlot = nullptr; may be later
            }
        }
        //m_targetPos = m_targetSlot->getPos();
    }
}

void Slot::setState(int state)
{
    m_state = state;
    switch (m_state)
    {
    case 0:
        m_circle.setColor(Feintgine::Color( 255, 255, 0, 255));
        break;
    case 1:
        m_circle.setColor(Feintgine::Color( 255, 0, 0, 255));
        break;
    
    default:
        break;
    }
}

bool Slot::isHovered(const glm::vec2 & mousePos)
{
   if (mousePos.x > m_actualPos.x - m_circle.getDimentions().x / 2.0f && mousePos.x < m_actualPos.x + m_circle.getDimentions().x / 2.0f &&
		mousePos.y > m_actualPos.y - m_circle.getDimentions().y / 2.0f && mousePos.y < m_actualPos.y + m_circle.getDimentions().y / 2.0f)
	{
		return true;
	}
	return false;
}