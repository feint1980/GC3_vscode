#pragma once
#include "EGUI_DrawElement.h"
class CEGUI_BGMLabel
{
public:
	CEGUI_BGMLabel();
	~CEGUI_BGMLabel();

	void initGUI(Feintgine::GUI & t_gui, const glm::vec2 & pos);

	void setText(const std::wstring &  songName, float t_lifeTime );

	void update(float deltaTime);

	void setLifeTime(float t_lifeTime);

private:

	EGUI_DrawElement m_text;

	bool isAlive = false;
	bool isTransit = false;

	float m_tAlpha = 0.0f;


	float lifeTime = 0.0f;
};

