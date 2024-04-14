#pragma once
#include "SpellcardIcon.h"
#include <vector>
#include <feint_common.h>
#include <AudioEngine.h>

const float normalScale = 0.25f;
const float focusScale = 0.5f;

class SpellcardSelector
{
public:
	SpellcardSelector();
	~SpellcardSelector();

	void addSpell(SpellcardIcon * spellcard);

	void draw(Feintgine::SpriteBatch & spriteBatch);

	void update(float deltaTime);

	void setPos(const glm::vec2 & pos);

	void arrangeSpellcard(bool motion);

	void changeSpellcardForward();

	void updateSpellStates(int playerGraze);

	void changeSpellcardBackward();
	glm::vec2 getArrangedPos(int index);

	bool isSwitching() const { return m_spellscards[0]->isMoving(); }

	std::vector<SpellcardIcon *> getSpellcards() const { return m_spellscards; }

	SpellcardIcon * getCurrentSelectCard() { return m_spellscards[m_currentSelection]; }

	void clearAllSpells();

	int getCurrentSelection() const {
		return m_currentSelection;
	}

	void registerAudio(Feintgine::AudioEngine * audioEngine);

private :
	std::vector<SpellcardIcon *> m_spellscards;


	float m_circleAngleRate = 0;

	float m_currentAngle = 0;
	int m_currentSelection = 0;

	float m_ringRadius = 60;

	Feintgine::SoundEffect m_switchSound;

	glm::vec2 m_pos;

};

