#include "SpellcardSelector.h"



SpellcardSelector::SpellcardSelector()
{
}


SpellcardSelector::~SpellcardSelector()
{
}

void SpellcardSelector::addSpell( SpellcardIcon * spellcard)
{
	m_spellscards.push_back(spellcard);

	float m_circleAngleRate = 360.0f / m_spellscards.size();
}


void SpellcardSelector::clearAllSpells()
{

	for (int i = 0; i < m_spellscards.size(); i++)
	{
		m_spellscards.erase(m_spellscards.begin() + i);
		delete m_spellscards[i];
	}
	m_spellscards.clear();
}

void SpellcardSelector::draw(Feintgine::SpriteBatch & spriteBatch)
{
	for (int i = 0; i < m_spellscards.size(); i++)
	{
		m_spellscards[i]->draw(spriteBatch);
	}
}

void SpellcardSelector::update(float deltaTime)
{
	for (int i = 0; i < m_spellscards.size(); i++)
	{
		m_spellscards[i]->update(deltaTime);
	}
}

void SpellcardSelector::setPos(const glm::vec2 & pos)
{
	m_pos = pos;
}


void SpellcardSelector::arrangeSpellcard(bool motion)
{
	//std::cout << "current selection is " << m_currentSelection << "\n";
	for (int i = 0; i < m_spellscards.size(); i++)
	{
		m_spellscards[i]->setPos(m_pos + getArrangedPos(i), motion);
		m_spellscards[i]->setScale(normalScale);

		// Reset depth
		m_spellscards[i]->setDepth(80);
		// Set depth base on Y pos
		m_spellscards[i]->setDepth(80 - m_spellscards[i]->getTPos().y);
		//m_spellscards[i]->setFocus(false);
	}


	m_spellscards[m_currentSelection]->setScale(focusScale);
	//m_spellscards[m_currentSelection]->setFocus(true);

}

void SpellcardSelector::changeSpellcardForward()
{
// 	if (!m_spellscards[0].isMoving())
// 	{
		m_currentSelection++;
		if (m_currentSelection >= m_spellscards.size())
		{
			m_currentSelection = 0;
		}
		arrangeSpellcard(true);
		m_switchSound.play();
	//}
}

void SpellcardSelector::updateSpellStates(int playerGraze)
{


	for (int i = 0; i < m_spellscards.size(); i++)
	{
		if (playerGraze >= m_spellscards[i]->getGrazeCost())
		{
			m_spellscards[i]->setFocus(true);
		
		}
		else
		{
			m_spellscards[i]->setFocus(false);
		}
	}
}

void SpellcardSelector::changeSpellcardBackward()
{
// 	if (!m_spellscards[0].isMoving())
// 	{
		m_currentSelection--;
		if (m_currentSelection < 0)
		{
			m_currentSelection = m_spellscards.size() - 1;
		}
		m_switchSound.play();
		arrangeSpellcard(true);
	//}
}

glm::vec2 SpellcardSelector::getArrangedPos(int index)
{
	glm::vec2 retVal;
	//std::cout << "index " << (m_currentSelection - index) << "\n";
	//std::cout << "angle " << (360 / m_spellscards.size()) << "\n";
	float total = (m_currentSelection - index) * (360.0f / m_spellscards.size());
	//std::cout << "total " << total << "\n";
	

	retVal.x = cos(degreeToRad(total - 90)) * m_ringRadius;
	retVal.y = sin(degreeToRad(total - 90)) * m_ringRadius;

	//std::cout << "arrange val " << feint_common::Instance()->convertiVec2toString(retVal) << "\n";
	return retVal;

}

void SpellcardSelector::registerAudio(Feintgine::AudioEngine * audioEngine)
{
	m_switchSound = audioEngine->loadSoundEffect("Sounds/sfx/se_item00.wav");
	m_switchSound.setVolume(20.0f);
}
