#include "CSlot.h"

CSlot::CSlot()
{

}

CSlot::~CSlot()
{

}

CSlot::CSlot(const std::string & texturePath, int colum, int row, int side)
{
    init(texturePath, colum, row, side);
}


void CSlot::draw(Feintgine::SpriteBatch & spriteBatch)
{
    m_circle.draw(spriteBatch);
}

void CSlot::update(float deltaTime)
{

}

void CSlot::init(const std::string & texturePath, int colum, int row, int side)
{
    m_index = glm::ivec2( colum,row);
    m_side = side;

    float xFactor = 150;
    float yFactor = -100;
    if(m_side == 1)
    {
        xFactor = -xFactor;
    }
    
    m_actualPos = glm::vec2(m_index.x * xFactor, m_index.y * yFactor);
    m_actualPos.y += 100; // up

    m_circle.init(Feintgine::ResourceManager::getTexture(texturePath), 
    m_actualPos, glm::vec2(120, 40), Feintgine::Color((colum -1 ) * (255/2), (row -1 ) * (255/2), 125, 255));

}

