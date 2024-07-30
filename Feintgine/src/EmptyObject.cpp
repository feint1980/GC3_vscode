#include "EmptyObject.h"
#include <iostream>

EmptyObject::EmptyObject()
{

}


EmptyObject::~EmptyObject()
{
}
void EmptyObject::init(Feintgine::GLTexture texture, glm::vec2 pos, glm::vec2 dims, Feintgine::Color color)
{
	m_texture = texture;
	m_pos = pos;
	m_dims = dims;
	m_color = color;
	fayde = false;
}

void EmptyObject::setAngle(float angle)
{
	m_angle = angle;
}

void EmptyObject::setColor(const Feintgine::Color & color)
{
	m_color = color;
}

void EmptyObject::setAlpha(GLubyte alpha)
{
	m_color.a = alpha;
}

void EmptyObject::setDepth(float target)
{
	m_depth = target;
}

void EmptyObject::setSPec(float intentse)
{
	m_spec = intentse;
	//m_color.a *= m_spec;
	//std::cout << m_spec << "set spec called \n";
	


}

void EmptyObject::expandingSize(const glm::vec2 & dimMax, const glm::vec2 & howfast)
{
	if (m_dims.x < dimMax.x || m_dims.y < dimMax.y)
	{
		m_dims.x += howfast.x;
		m_dims.y += howfast.y;
	}
}

void EmptyObject::fayde_spec(float min_spec, float max_spec, float fade_speed , bool loop)
{
	if (loop)
	{
		if (fayde)
		{
			//m_spec -= fade_speed;
			setSPec(m_spec - fade_speed);
		
			if (m_spec < min_spec)
			{
				fayde = false;
			}
		}
	}

	if (!fayde)
	{
		//m_spec += fade_speed;
		setSPec(m_spec + fade_speed);
		if (m_spec > max_spec)
		{
			fayde = true;
		}
	}

}

void EmptyObject::end_spec(float min_spec, float fade_speed)
{
	if (m_spec > min_spec)
	{
		//m_spec -= fade_speed;
		setSPec(m_spec - fade_speed);
	}

	
}

void EmptyObject::drawLight(Feintgine::LightBatch & lightBatch)
{

}


void EmptyObject::draw(Feintgine::SpriteBatch & spriteBatch)
{
	const glm::vec4 uvrect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 desRect;
	desRect.x = m_pos.x - m_dims.x / 2.0f;
	desRect.y = m_pos.y - m_dims.y / 2.0f;
	desRect.z = m_dims.x;
	desRect.w = m_dims.y;
	spriteBatch.draw(desRect, uvrect, m_texture.id, m_depth, m_color, m_angle);

}

/*
void EmptyObject::draw(Feintgine::SpriteBatch & spriteBatch)
{
	const glm::vec4 uvrect(0.0f, 0.0f, 1.0f, 1.0f);

	Feintgine::Color specColor = m_color;
	specColor.r *= m_spec;
	specColor.g *= m_spec;
	specColor.b *= m_spec;


	glm::vec4 desRect;
	desRect.x = m_pos.x - m_dims.x /2.0f;
	desRect.y = m_pos.y - m_dims.y /2.0f;
	desRect.z = m_dims.x;
	desRect.w = m_dims.y;
	spriteBatch.draw(desRect, uvrect, m_texture.id, m_depth, specColor, m_angle, m_spec);
}

void EmptyObject::drawLight(Feintgine::SpriteBatch & spriteBatch)
{
	const glm::vec4 uvrect(-1.0f, -1.0f, 2, 2);

	Feintgine::Color specColor = m_color;
	specColor.r *= m_spec;
	specColor.g *= m_spec;
	specColor.b *= m_spec;


	glm::vec4 desRect;
	desRect.x = m_pos.x - m_dims.x / 2.0f;
	desRect.y = m_pos.y - m_dims.y / 2.0f;
	desRect.z = m_dims.x;
	desRect.w = m_dims.y;
	spriteBatch.drawLight(desRect, uvrect, 10, specColor, m_angle, 1);
}
*/
void EmptyObject::drawBox(Feintgine::DebugRender & debugRenderer)
{
	debugRenderer.drawBox_center(glm::vec4(m_pos, m_dims), Feintgine::Color(100, 100, 255, 255), m_angle);
}
