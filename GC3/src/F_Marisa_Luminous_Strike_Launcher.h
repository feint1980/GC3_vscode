#pragma once
#include "F_Marisa_Luminous_Strike.h"
#include "F_Marisa_Luminous_Charge.h"
#include "F_MarisaStar.h"
#include "F_BaseEnemy.h"
#include "EnemyBulletBase.h"
#include <AudioEngine.h>

class F_Marisa_Luminous_Strike_Launcher 
{
public:
	F_Marisa_Luminous_Strike_Launcher();


	~F_Marisa_Luminous_Strike_Launcher();

	void chargeStar(int count);

	void draw(Feintgine::SpriteBatch & spriteBatch);

	void update(float deltaTime, std::vector<FairyBase *>  enemy,std::vector<EnemyBulletBase * > bullets);


	void drawLight(Feintgine::LightBatch & lightBatch);

	void updateSpawn(float deltaTime);
	void loadAnimation(const std::string & animationPath);

	void registerParticleBatch(Feintgine::ParticleBatch2D * particleBatch);

	Feintgine::Color getStarColor(int index);

	void registerAudioEngine(Feintgine::AudioEngine * audioEngine);


	//void loadEndSound(const std::string & filePath);

	//void sth(std::vector<F_BaseEnemy *>  enemy);
private: 

	F_Marisa_Luminous_Strike * m_mainStrike;

	std::vector<F_Marisa_Luminous_Charge *> m_chargeStar;

	Feintgine::F_AnimatedObject m_chargeAnimation;

	Feintgine::ParticleBatch2D * m_hitParticleBatch = nullptr;

	int m_count = 0;

	int m_totalCount;

	float m_spawnCounter = 0.0f;

	float m_launchCounter = 0.0f;
	float m_launchTime = 0.0f;

	bool m_launched = false;

	Feintgine::AudioEngine * m_audioEngine;

	Feintgine::SoundEffect m_chargeSound;


};

