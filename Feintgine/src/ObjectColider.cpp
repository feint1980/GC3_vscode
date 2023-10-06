#include "ObjectColider.h"



ObjectColider::ObjectColider()
{
	
}


ObjectColider::~ObjectColider()
{
}

void ObjectColider::init(const glm::vec2 & pos, const glm::vec2 & dim)
{
	m_color = Feintgine::Color(255, 0, 0, 255);
	m_pos = pos;
	m_dim = dim;
}

void ObjectColider::draw(Feintgine::DebugRender & renderer)
{
	glm::vec2 offset;
	offset.x = m_pos.x - m_dim.x / 2;
	offset.y = m_pos.y + m_dim.y / 2;

	renderer.drawBox_nonCenter(glm::vec4(offset, m_dim), m_color, 0);
		
}

void ObjectColider::setPos(const glm::vec2 &pos)
{
	m_pos = pos;
}

void ObjectColider::setDim(const glm::vec2 &dim)
{
	m_dim = dim;
}

