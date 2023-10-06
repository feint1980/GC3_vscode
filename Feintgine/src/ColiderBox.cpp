#include "ColiderBox.h"



ColiderBox::ColiderBox()
{
	m_color = Feintgine::Color(255, 0, 0, 255);
}


ColiderBox::~ColiderBox()
{
}

bool ColiderBox::checkInside(glm::vec2 mousePos)
{
	if (mousePos.x > m_pos.x - m_dim.x / 2.0f && mousePos.x < m_pos.x + m_dim.x / 2.0f &&
		mousePos.y > m_pos.y - m_dim.y / 2.0f && mousePos.y < m_pos.y + m_dim.y / 2.0f)
	{

		return true;
	}
	return false;
}

void ColiderBox::draw(Feintgine::DebugRender & renderer)
{
	
	
	renderer.drawBox_center(glm::vec4(m_pos, m_dim), color, 0);
}


void ColiderBox::init(glm::vec2 pos, glm::vec2 dim, int ID)
{
	m_pos = pos;
	m_dim = dim;
	m_ID = ID;
}

void ColiderBox::setPos(glm::vec2 pos)
{
	m_pos = pos;
}

void ColiderBox::setDim(glm::vec2 dim)
{
	m_dim = dim;
}

void ColiderBox::setSelected(bool value)
{
	
	selected = value;
	if (selected)
	{
		color = m_selectedColor;
	}
	else
	{
		color = m_color;
	}
}
