#include "DragVertex.h"



DragVertex::DragVertex()
{
}


DragVertex::~DragVertex()
{
}

void DragVertex::setPos( const glm::vec2 & pos)
{
	//m_lastPos = m_pos;
	m_pos = pos;
}

void DragVertex::setPoswithTrack(const glm::vec2 & pos)
{
	m_lastPos = m_pos;
	m_pos = pos;
}

void DragVertex::setDim(const glm::vec2 & dim)
{
	m_dim = dim;
}

void DragVertex::init(glm::vec2 pos, glm::vec2 dim)
{
	m_pos = pos;
	m_dim = dim;
	//m_lastPos = m_pos;
}

void DragVertex::add(glm::vec2 val)
{
	m_pos += val;
}

void DragVertex::draw(Feintgine::DebugRender & renderer)
{
	renderer.drawBox(glm::vec4(m_pos, m_dim), Feintgine::Color(255, 255, 255, 255), 0);
}

bool DragVertex::checkInside(const glm::vec2 & mousePos)
{
	if (mousePos.x > m_pos.x - m_dim.x && mousePos.x < m_pos.x + m_dim.x
		&& mousePos.y < m_pos.y + m_dim.y && mousePos.y > m_pos.y - m_dim.y)
	{
		return true;
	}
	return false;
}

