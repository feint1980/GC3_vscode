#pragma once
#include "F_Player.h"
#include "BackGroundMap.h"
#include <AudioEngine.h>
#include "EnemyGuardian.h"
const int IS_REIMU = 0;
const int IS_MARISA = 1;
const int IS_PATCHOULI = 2;


class BulletTypeDemo
{
public:
	BulletTypeDemo();
	~BulletTypeDemo();

	void init(Feintgine::AudioEngine & audioEngine);

	void update(float deltaTime);

	void draw(Feintgine::SpriteBatch & spriteBatch);

	void drawDecription(Feintgine::Camera2D & camera, TextRenderer & renderer);

	void updateSelection(int val);


	void toggleFocus();

	void toggleType();


private : 


	float m_counter = 0.0f;

	float m_rate = 0.1f;
	F_Player m_reimu;
	F_Player m_marisa;
	BackGroundMap m_bg;
	int m_selection = -1;

	std::vector<FairyBase *> m_enemies;

	std::vector<EnemyGuardian *> m_guardians;

	std::vector<EnemyAmplifier *> m_amplifiers;

	std::vector<EnemyBulletBase *> m_bullets;
	float t_fadeRate = 0.085f;
	float t_counter = 0.0f;
	bool m_isShowBG = false;
	bool m_isBGswitching = true;
	bool m_isShowReimu = false;
	bool m_isReimuswitching = true;
	bool m_isShowMarisa = false;
	bool m_isMarisaswitching = true;

	glm::vec2 textOffset = glm::vec2(0, -100);
	glm::vec2 textOffsetDescript = glm::vec2(0, -150);

	int m_marisaShootType = 2;
	int m_reimuShootType = 1;
	bool isFocus = false;

};

