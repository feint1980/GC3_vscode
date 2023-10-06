#include "TitleLabel.h"



TitleLabel::TitleLabel()
{
	lifeTime = 12.0f;

	liveTime = 0.05f;
}


TitleLabel::~TitleLabel()
{
}

void TitleLabel::init(const glm::vec2 & pos, const std::wstring & firstSign, 
	const std::wstring & secondSign, const Feintgine::Color & color, const Feintgine::Color & color2)
{
	m_pos = pos;
	m_message = firstSign;
	m_subMesage = secondSign;
	m_color = color;
	m_color2 = color2;
	startCount = true;
	m_color.a = 0.0f;
	m_color2.a = 0.0f;
}

void TitleLabel::setLifeTime(float value)
{
	lifeTime = value;
}

void TitleLabel::update(float deltaTime)
{
	if (lifeTime > 0)
	{
	
		lifeTime -= liveTime * deltaTime;
		
	}
	if (isFade)
	{
		m_color.a = lifeTime;
		m_color2.a = lifeTime;
		return;
	}
	if (startCount)
	{
		if (m_color.a < 1.0f)
		{
			m_color.a += FADE_TIME * deltaTime;
			m_color2.a += FADE_TIME * deltaTime;
		}
		else
		{
			isFade = true;
			//startCount = false;
			
		}
				
	}
}

void TitleLabel::draw(TextRenderer * textRenderer)
{
	textRenderer->renderBorderText(*GlobalValueClass::Instance()->savedCamera, m_message, m_pos,
		m_color, m_scale, ALIGN_FT_CENTER);

	glm::vec2 subPos = m_pos;
	subPos.y = subPos.y - 30;
	textRenderer->renderBorderText(*GlobalValueClass::Instance()->savedCamera, m_subMesage, subPos,
		m_color2, m_scale * 0.65f, ALIGN_FT_CENTER);
	if (!set)
	{
		set = true;
		totalWidth = textRenderer->getTotalScale();
	}
}

