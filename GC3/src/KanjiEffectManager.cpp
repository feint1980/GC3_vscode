#include "KanjiEffectManager.h"



KanjiEffectManager::KanjiEffectManager()
{
}


KanjiEffectManager::~KanjiEffectManager()
{
}

void KanjiEffectManager::addKanjiEffect(const KanjiEffect & kanjiEffect)
{
	m_kanjiObject.push_back(kanjiEffect);
}

void KanjiEffectManager::draw(Feintgine::SpriteBatch & spriteBatch)
{
	for (int i = 0; i < m_kanjiObject.size(); i++)
	{
		m_kanjiObject[i].draw(spriteBatch);
	}
}

void KanjiEffectManager::update(float deltaTime)
{
	for (int i = 0; i < m_kanjiObject.size(); i++)
	{
		if (!m_kanjiObject[i].isAlive())
		{
			m_kanjiObject.erase(m_kanjiObject.begin() + i);
		}
		m_kanjiObject[i].update(deltaTime);
	}
}

