#include "ObjectSlot.h"

// 

ObjectSlot::ObjectSlot()
{

}


ObjectSlot::~ObjectSlot()
{

}

void ObjectSlot::draw(Feintgine::DebugRender & renderer)
{
	if (show)
	{

		//glm::vec2 halfDim = glm::vec2(m_dim.x / 2.0f, m_dim.y / 2.0f);
		//renderer.drawBox(glm::vec4(m_pos - halfDim * currentSize, m_dim * currentSize), m_color, 0);
		renderer.drawBox(glm::vec4(m_pos, m_dim ), m_color, 0);
	}
	
}

void ObjectSlot::setPos(glm::vec2 pos)
{
	m_pos = pos;
}

void ObjectSlot::setDim(glm::vec2 dim)
{
	m_dim = dim;
}

bool ObjectSlot::onHover(const glm::vec2 & mousePos)
{
	if (mousePos.x > m_pos.x  && mousePos.x < m_pos.x + m_dim.x &&
		mousePos.y > m_pos.y && mousePos.y  < m_pos.y + m_dim.y)
	{
		m_color = Feintgine::Color(0, 255, 255, 255);
		if (currentSize < enlargeSize)
		{
			currentSize += 0.05f;
		}		
		show = true;
		return true;
	}
	else
	{
		if (currentSize > 1.0f)
		{
			currentSize -= 0.05f;
		}
		m_color = Feintgine::Color(255, 255, 255, 255);
		show = false;
		return false;
	}

	
		
}

glm::vec2 ObjectSlot::getOffsetPos()
{
	glm::vec2 halfDim = m_dim / 2.0f;
	return m_pos + halfDim;
}

void ObjectSlot::addObject(TemplateObject object)
{
	if (m_object)
	{
		clearObject();
	}
	
	// v_object.init(object.getPrefabFilePath());
	// m_object = &v_object;
	// m_object->setPos(getOffsetPos());
	// m_object->setDim(m_object->getFitDim(m_dim));
}

void ObjectSlot::clearObject()
{
	m_object = nullptr;
}


void ObjectSlot::drawObject(Feintgine::SpriteBatch & spriteBatch)
{
	if (m_object)
	{
		//m_object->draw(spriteBatch);
	}
}

void ObjectSlot::init(glm::vec2 pos, glm::vec2 dim)
{
	m_color = Feintgine::Color(255, 255, 255, 255);
	setPos(pos);
	setDim(dim);
}
