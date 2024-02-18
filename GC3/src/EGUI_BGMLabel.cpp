#include "EGUI_BGMLabel.h"



CEGUI_BGMLabel::CEGUI_BGMLabel()
{
}


CEGUI_BGMLabel::~CEGUI_BGMLabel()
{
}

void CEGUI_BGMLabel::initGUI(Feintgine::GUI & t_gui, const glm::vec2 & pos)
{
	m_text.init("CEGUI_ChapterLabel_m_text1",
		pos);
	
}

void CEGUI_BGMLabel::setText(const std::wstring & songName, float t_lifeTime)
{
	m_text.setText(songName);
	m_text.setAlpha(0);
	lifeTime = t_lifeTime;
	
}

void CEGUI_BGMLabel::update(float deltaTime)
{
	if (isAlive)
	{
		if (lifeTime > 0.0f)
		{
			lifeTime -= 0.01f * deltaTime;
			if (lifeTime <= 1.0f)
			{
				//m_text1.set
				m_text.setAlpha(lifeTime);
			
			}
		}
		else
		{
			isAlive = false;
		}
	}
	if (isTransit)
	{
		m_tAlpha += 0.01f * deltaTime;
		m_text.setAlpha(m_tAlpha);
		if (m_tAlpha >= 1.0f)
		{
			isTransit = false;
			isAlive = true;
		}
	}
}

void CEGUI_BGMLabel::setLifeTime(float t_lifeTime)
{
	lifeTime = t_lifeTime;
	isTransit = true;
}
