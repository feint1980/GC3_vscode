#include "FieldLayout.h"


FieldLayout::FieldLayout()
{

}

FieldLayout::~FieldLayout()
{

}

void FieldLayout::init(int side)
{
    m_side = side;

    for (int i = 0; i < ROW_SIZE; i++)
    {
        for (int j = 0; j < COL_SIZE; j++)
        {
            m_fieldSlot[i][j].row = i;
            m_fieldSlot[i][j].col = j;
        }
    }
    // map update 
    m_fieldSlotMap.reserve(ROW_SIZE * COL_SIZE);
    m_fieldSlotMap[FrontTop] = m_fieldSlot[0][0];
    m_fieldSlotMap[CenterTop] = m_fieldSlot[0][1];
    m_fieldSlotMap[RearTop] = m_fieldSlot[0][2];
    m_fieldSlotMap[FrontMid] = m_fieldSlot[1][0];
    m_fieldSlotMap[CenterMid] = m_fieldSlot[1][1];
    m_fieldSlotMap[RearMid] = m_fieldSlot[1][2];
    m_fieldSlotMap[FrontBot] = m_fieldSlot[2][0];
    m_fieldSlotMap[CenterBot] = m_fieldSlot[2][1];
    m_fieldSlotMap[RearBot] = m_fieldSlot[2][2];

}