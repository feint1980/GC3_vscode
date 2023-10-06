#pragma once

#include "KanjiEffect.h"
#include <vector>


class KanjiEffectManager
{
public:
	KanjiEffectManager();
	~KanjiEffectManager();

	void addKanjiEffect(const KanjiEffect & kanjiEffect);


	void draw(Feintgine::SpriteBatch & spriteBatch);

	void update(float deltaTime);


private:
	std::vector <KanjiEffect> m_kanjiObject;

};

