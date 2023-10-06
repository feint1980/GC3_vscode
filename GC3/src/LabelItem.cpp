#include "LabelItem.h"



LabelItem::LabelItem()
{
}


LabelItem::~LabelItem()
{
}


void LabelItem::init(const glm::vec2 & pos, const std::string & text, Feintgine::Color color, float scale, int alignment)
{
	m_pos = pos;
	m_text = text;
	m_color = color;
	m_scale = scale;
	m_alignment = alignment;
	m_lifeTime = TEXT_DEFAULT_TIME;
}

void LabelItem::draw(TextRenderer & textRenderer, const Feintgine::Camera2D cam)
{
	
	textRenderer.renderText(cam, feint_common::Instance()->convertStringtoWstring(m_text.c_str()), m_pos,
		m_color, m_scale, m_alignment);
}

void LabelItem::update(float deltaTime)
{
	m_lifeTime -= TEXT_DECAY_RATE * deltaTime;
	if (m_lifeTime < 0)
	{
		m_color.a = m_lifeTime;
		m_isExpired = true;
	}
}
