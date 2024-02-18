#include "EGUI_ChapterLabel.h"



CEGUI_ChapterLabel::CEGUI_ChapterLabel()
{
}


CEGUI_ChapterLabel::~CEGUI_ChapterLabel()
{
}

void CEGUI_ChapterLabel::initGUI(Feintgine::GUI & t_gui, Feintgine::GUI & t_gui2, const glm::vec2 & pos)
{
	m_text1.init("CEGUI_ChapterLabel_m_text1",
		pos);

	m_text2.init( "CEGUI_ChapterLabel_m_text2",
		glm::vec2(pos.x, pos.y + 0.05f));


	//m_text1.setAlignment(2);
	//m_text2.setAlignment(2);
}

void CEGUI_ChapterLabel::update(float deltaTime)
{
	if (isAlive)
	{


		if (lifeTime > 0.0f)
		{
			lifeTime -= 0.01f * deltaTime;
			if (lifeTime <= 1.0f)
			{
				//m_text1.set
				m_text1.setAlpha(lifeTime);
				m_text2.setAlpha(lifeTime);
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
		m_text1.setAlpha(m_tAlpha);
		m_text2.setAlpha(m_tAlpha);
		if (m_tAlpha >= 1.0f)
		{
			isTransit = false;
			isAlive = true;
		}
	}
	
}

void CEGUI_ChapterLabel::setText(const std::wstring & msg1, const std::wstring & msg2, float t_lifeTime)
{
	std::wstring tmsg1 = L"[colour='FFFFFA00']";
	tmsg1.append(msg1);
	m_text1.setText(tmsg1);
	m_text2.setText(msg2);
	m_text1.setAlpha(0);
	m_text2.setAlpha(0);
	lifeTime = t_lifeTime;
	//isTransit = true;
	m_tAlpha = 0.0f;
}

void CEGUI_ChapterLabel::setLifeTime(float t_lifeTime)
{
	lifeTime = t_lifeTime;
	isTransit = true;
	m_tAlpha = 0.0f;
}
