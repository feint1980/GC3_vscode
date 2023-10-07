#include "ObjectDisplayer.h"



ObjectDisplayer::ObjectDisplayer()
{
}


ObjectDisplayer::~ObjectDisplayer()
{
}

void ObjectDisplayer::init(glm::vec2 pos, glm::vec2 dim, const EditObject & object)
{
	m_pos = pos;
	m_dim = dim;
	m_object = object;
	m_object.setPos(m_pos);
	//calculateFitScale();
}

void ObjectDisplayer::calculateFitScale()
{
	glm::vec2 fulldim = m_object.getFullDimObject();
	float width = fulldim.x;
	float height = fulldim.y;

	if (width > m_dim.x || height > m_dim.y)
	{


		float offset;
		if (width < height)
		{
			offset = height / m_dim.x;
			m_fitScale = (width / height) / offset;

		}
		else if (height < width)
		{
			offset = width / m_dim.y;
			m_fitScale = (height / width) / offset;
		}
		else
		{
			m_fitScale = 1.0f;
		}
	}
	m_object.setFitScale(m_fitScale);



}

void ObjectDisplayer::setObject(const EditObject  & object)
{
	m_object = object;
}

bool ObjectDisplayer::checkInside(glm::vec2 mousePos)
{
	if (mousePos.x > m_pos.x - m_dim.x / 2.0f && mousePos.x < m_pos.x + m_dim.x / 2.0f &&
		mousePos.y > m_pos.y - m_dim.y / 2.0f && mousePos.y < m_pos.y + m_dim.y / 2.0f)
	{
		return true;
	}
	return false;
}

void ObjectDisplayer::draw(Feintgine::SpriteBatch &spriteBatch)
{

	m_object.draw(spriteBatch);
}

void ObjectDisplayer::drawBorder(Feintgine::DebugRender & renderer)
{
	if (m_isHover)
	{
	
		glm::vec2 halfDim = glm::vec2(m_dim.x / 2.0f, m_dim.y / 2.0f);
		renderer.drawBox(glm::vec4(m_pos - halfDim * currentSize, m_dim * currentSize), hoverColor, 0);
	}
}

void ObjectDisplayer::setHover(bool value)
{
	m_isHover = value;
}

void ObjectDisplayer::update(glm::vec2 mousePos)
{
	if (checkInside(mousePos))
	{
		m_isHover = true;

	}
	else
	{
		m_isHover = false;

	}
	if (m_isHover)
	{

		if (currentSize < enlargeSize)
		{
			currentSize += 0.05f;
			
		}
	}
	else
	{
		if (currentSize > 1.0f)
		{
			currentSize -= 0.05f;
		}

	}
	m_object.setEnlargeSize(currentSize);
}

