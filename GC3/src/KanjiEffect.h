#pragma once

#include "KanjiEffectrObject.h"

class KanjiEffect
{
public:
	KanjiEffect();
	~KanjiEffect();

	void init(const Feintgine::F_Sprite & sprite, const glm::vec2 & pos, const Feintgine::Color & color);

	void draw(Feintgine::SpriteBatch & spriteBatch);

	void update(float deltaTime);

	bool isAlive();


private: 


	Feintgine::Color m_color;

	Feintgine::F_Sprite m_sprite;

	glm::vec2 m_pos;

	KanjiEffectrObject m_fadeScaleText;
	KanjiEffectrObject m_presentText;
	KanjiEffectrObject m_centerText;
	
};

