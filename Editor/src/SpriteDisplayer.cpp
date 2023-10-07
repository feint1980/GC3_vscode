#include "SpriteDisplayer.h"



SpriteDisplayer::SpriteDisplayer()
{
}


SpriteDisplayer::~SpriteDisplayer()
{
}

void SpriteDisplayer::init(glm::vec2 pos, glm::vec2 dim, Feintgine::F_Sprite sprite)
{
	
	m_pos = pos;
	m_dim = dim;
	m_sprite = sprite ;
	calculateFitScale();
	

}


void SpriteDisplayer::calculateFitScale()
{
	float width = m_sprite.getDim().x;
	float height = m_sprite.getDim().y;

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
// 			offset = height / m_dim.x;
// 			m_fitScale = (width / height) / offset;
			offset = width / m_dim.y;
			m_fitScale = (height / width) / offset;
		}
	}

	

}

void SpriteDisplayer::setSprite(Feintgine::F_Sprite sprite)
{
	m_sprite = sprite;
}

bool SpriteDisplayer::checkInside(glm::vec2 mousePos)
{
	if (mousePos.x > m_pos.x - m_dim.x / 2.0f && mousePos.x < m_pos.x + m_dim.x / 2.0f &&
		mousePos.y > m_pos.y - m_dim.y / 2.0f && mousePos.y < m_pos.y + m_dim.y / 2.0f)
	{
		return true;
	}
	return false;
}

void SpriteDisplayer::draw(Feintgine::SpriteBatch & spriteBatch)
{
	
	glm::vec4 desRect;// (0, 0, 50, 50);
// 	desRect.x = m_pos.x - (m_sprite.getDim().x * 1);
// 	desRect.y = m_pos.y - (m_sprite.getDim().y *1);
// 	desRect.z = m_sprite.getDim().x;
// 	desRect.w = m_sprite.getDim().y;
	desRect.x = m_pos.x - (m_sprite.getDim().x * m_fitScale / 2.0f * currentSize);
	desRect.y = m_pos.y - (m_sprite.getDim().y * m_fitScale / 2.0f * currentSize) ;
	desRect.z = m_fitScale  * m_sprite.getDim().x * currentSize;
	desRect.w = m_fitScale  * m_sprite.getDim().y * currentSize;

	//spriteBatch.draw(desRect, uvrect, m_sprite.getTexture().id, m_depth, m_color, 0.0f, m_spec);
	spriteBatch.draw(desRect, m_sprite.getUV(), m_sprite.getTexture().id, 1, Feintgine::Color(255,255,255,255), 0.0f);
	//spriteBatch.draw(desRect, m_sprite.getUV(), m_sprite.getTexture().id, m_depth, m_color, m_spec);
}

void SpriteDisplayer::drawBorder(Feintgine::DebugRender & renderer)
{
	if (m_isHover)
	{
		glm::vec2 halfDim = glm::vec2(m_dim.x / 2.0f, m_dim.y / 2.0f);
		renderer.drawBox(glm::vec4(m_pos - halfDim * currentSize, m_dim * currentSize), hoverColor, 0);
	}
	
	//renderer.drawBox_center(glm::vec4(m_pos * currentSize, m_dim * currentSize), currentColor, 0);
}

void SpriteDisplayer::update(glm::vec2 mousePos)
{
	//std::cout << feint_common::Instance()->convertVec2toString(mousePos) << "\n";
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
}
