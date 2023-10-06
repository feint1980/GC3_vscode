#include "GC3_EmptyObject.h"
#include <iostream>

GC3_EmptyObject::GC3_EmptyObject()
{

}


GC3_EmptyObject::~GC3_EmptyObject()
{

}
void GC3_EmptyObject::init(Feintgine::GLTexture texture, glm::vec2 pos, glm::vec2 dims, Feintgine::Color color)
{
	m_texture = texture;
	m_pos = pos;
	m_dims = dims;
	m_color = color;
	fayde = false;
}

void GC3_EmptyObject::setAngle(float angle)
{
	m_angle = angle;
}



void GC3_EmptyObject::setAlpha(GLubyte alpha)
{
	m_color.a = alpha;
}

void GC3_EmptyObject::setDepth(float target)
{
	m_depth = target;
}

void GC3_EmptyObject::setSPec(float intentse)
{
	m_spec = intentse;
	//m_color.a *= m_spec;
	//std::cout << m_spec << "set spec called \n";
	


}

void GC3_EmptyObject::expandingSize(const glm::vec2 & dimMax, const glm::vec2 & howfast)
{
	if (m_dims.x < dimMax.x || m_dims.y < dimMax.y)
	{
		m_dims.x += howfast.x;
		m_dims.y += howfast.y;
	}
}

void GC3_EmptyObject::fayde_spec(float min_spec, float max_spec, float fade_speed , bool loop)
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

void GC3_EmptyObject::end_spec(float min_spec, float fade_speed)
{
	if (m_spec > min_spec)
	{
		//m_spec -= fade_speed;
		setSPec(m_spec - fade_speed);
	}

	
}


void GC3_EmptyObject::draw(Feintgine::SpriteBatch & spriteBatch)
{
	const glm::vec4 uvrect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 desRect;
	desRect.x = m_pos.x - m_dims.x /2.0f;
	desRect.y = m_pos.y - m_dims.y /2.0f;
	desRect.z = m_dims.x;
	desRect.w = m_dims.y;
	spriteBatch.draw(desRect, uvrect, m_texture.id, m_depth, m_color, m_angle);
}


void GC3_EmptyObject::drawBox(Feintgine::DebugRender & debugRenderer)
{
	debugRenderer.drawBox_center(glm::vec4(m_pos, m_dims), Feintgine::Color(100, 200, 200, 255), m_angle);
}

