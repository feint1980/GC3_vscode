#include "F_EmptyObject.h"

namespace Feintgine {

	void F_EmptyObject::init(F_Sprite sprite, glm::vec2 pos, glm::vec2 scalingFactor, Feintgine::Color color)
	{
		m_sprite = sprite;
		m_pos = pos;
		m_scale = scalingFactor;
		m_color = color;

	}

	void F_EmptyObject::setPos(glm::vec2 pos)
	{
		m_pos = pos;
	}

	void F_EmptyObject::setScaleWithActualSize(glm::vec2 dim)
	{
		glm::vec2 scale = dim / m_sprite.getTextureDim();

		m_scale = scale;
	}


	void F_EmptyObject::setScale(glm::vec2 scale)
	{
		m_scale = scale;
	}

	void F_EmptyObject::setColor(Feintgine::Color color)
	{
		m_color = color;
	}

	void F_EmptyObject::draw(Feintgine::SpriteBatch & spriteBatch)
	{
		//const glm::vec4 uvrect(0.0f, 0.0f, 1.0f, 1.0f);
		glm::vec4 desRect;// (0, 0, 50, 50);
		desRect.x = m_pos.x - (m_sprite.getDim().x * m_scale.x / 2.0f);
		desRect.y = m_pos.y - (m_sprite.getDim().y * m_scale.y / 2.0f);
		desRect.z = m_scale.x * m_sprite.getDim().x;
		desRect.w = m_scale.y * m_sprite.getDim().y;
	
		spriteBatch.draw(desRect, m_sprite.getUV(), m_sprite.getTexture().id, m_depth, m_color, m_angle);

	}

	F_EmptyObject::F_EmptyObject()
	{
	}


	F_EmptyObject::~F_EmptyObject()
	{
	}
}
