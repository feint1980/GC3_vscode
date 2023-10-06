#include "F_ReimuWave.h"



F_ReimuWave::F_ReimuWave()
{
	m_vel = glm::vec2(0, 22);
}


F_ReimuWave::~F_ReimuWave()
{

}

void F_ReimuWave::draw(Feintgine::SpriteBatch & spriteBatch)
{
	if (!m_isAnimated)
	{
		glm::vec4 desRect;
		desRect.x = m_pos.x - (m_sprite.getDim().x * m_scale.x) / 2.0f;
		desRect.y = m_pos.y - (m_sprite.getDim().y * m_scale.y) / 2.0f;
		desRect.z = m_sprite.getDim().x  * m_scale.x;
		desRect.w = m_sprite.getDim().y  * m_scale.y;
		spriteBatch.draw(desRect, m_sprite.getUV(), m_sprite.getTexture().id, m_depth, m_color, m_angle);
	}
	else
	{
		glm::vec2 additionalPos;
		//if (radToDegree(m_animation.getAngle() == 90))
		//{
		additionalPos.x = (m_animation.getDim().x * 0.5f) - m_animation.getDim().y * 0.5f ;
		//}


		m_animation.setPos(m_pos + additionalPos);
		//m_animation.setScale(glm::vec2(1.0));
		m_animation.draw(spriteBatch);
	}
}

// void F_ReimuWave::draw(Feintgine::SpriteBatch & spriteBatch)
// {
// 	glm::vec2 additionalPos;
// 
// 
// 	additionalPos.x = (m_animation.getDim().x * 0.5f * m_scale.x);
// 
// 
// 
// 	m_animation.setPos(m_pos + additionalPos);
// 	//m_animation.setScale(glm::vec2(1.0));
// 	m_animation.draw(spriteBatch);
//}
