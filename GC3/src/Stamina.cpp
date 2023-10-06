#include "Stamina.h"
#include <iostream>


Stamina::Stamina()
{
}


Stamina::~Stamina()
{
}

void Stamina::draw(Feintgine::SpriteBatch & spriteBatch ,float bar_size)
{
	float finalCount = m_dims.y * bar_size;
	const glm::vec4 uvrect(0.0f, 0.0f, 1.0f, 1.0f);

	glm::vec4 desRect;
	desRect.x = m_pos.x;
	desRect.y = m_pos.y - m_dims.y / 2;
	desRect.w = m_dims.x;
	desRect.z = finalCount;
	spriteBatch.draw(desRect, uvrect, m_texture.id, 0.0f, m_color,  1.0f);
}
