#pragma once
#include "EGUI_DrawElement.h"
class CEGUI_ChapterLabel
{
public:
	CEGUI_ChapterLabel();
	~CEGUI_ChapterLabel();



	void initGUI(Feintgine::GUI & t_gui, Feintgine::GUI & t_gui2,const glm::vec2 & pos);

	void update(float deltaTime);

	void setText(const std::wstring & msg1, const std::wstring & msg2, float t_lifeTime);
	void setLifeTime(float t_lifeTime);

private :

	EGUI_DrawElement m_text1;
	EGUI_DrawElement m_text2;

	bool isAlive = false;
	bool isTransit = false;

	float m_tAlpha = 0.0f;


	float lifeTime = 0.0f;
};

