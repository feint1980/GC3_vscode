#include "BackGroundMap.h"



BackGroundMap::BackGroundMap()
{
}


BackGroundMap::~BackGroundMap()
{
}

void BackGroundMap::init(const Feintgine::GLTexture & texture, const glm::vec2 & pos, const glm::vec2 & dim)
{
	m_texture = texture;
	m_pos = pos;
	m_dims = dim;
}

void BackGroundMap::draw(Feintgine::SpriteBatch & spriteBatch)
{
	glm::vec4 desRect;
	desRect.x = m_pos.x - m_dims.x /2.0f;
	desRect.y = m_pos.y - m_dims.y /2.0f;
	desRect.z = m_dims.x;
	desRect.w = m_dims.y;
	spriteBatch.draw(desRect, m_uv, m_texture.id, -15, m_color, 0);
}

void BackGroundMap::setColor(const Feintgine::Color & color)
{
	m_color = color;
}



void BackGroundMap::update(float deltaTime)
{
	//m_uv.x += 0.1f * deltaTime;
	m_uv.y += 0.005f *deltaTime;
// 	if (m_uv.y >= 1.0f)
// 	{
// 		m_uv.y -= 1.0f;
// 	}
// 	if (m_uv.y <= .5f)
// 	{
// 		m_uv.y += .5f;
// 	}

	
}

void BackGroundMap::resetUV()
{
	m_uv = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
}

bool BackGroundMap::changeColor(int channel, float rate, float maxVal)
{
	return m_color.change(channel, rate, maxVal);
}
