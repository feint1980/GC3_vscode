#pragma once

#include "F_MarisaStar.h"
#include <AudioEngine.h>


class F_MarisaStarSpawner
{
public:
	F_MarisaStarSpawner();
	~F_MarisaStarSpawner();


	void spawn(int count, float rotationCurve, float spawnRate);

	void loadStar(const Feintgine::F_AnimatedObject & animation);

	void loadStar(const std::string & animationPath);

	Feintgine::Color getStarColor(int index);

	void draw(Feintgine::SpriteBatch & spriteBatch);
	void update( float deltaTime, std::vector<FairyBase *>  enemy,
		std::vector<EnemyBulletBase * > bullets, const glm::vec2 & m_pos);

	void drawLight(Feintgine::LightBatch & lightBatch);

	void updateSpawn(float deltaTime, const glm::vec2 & pos);

	void addStar(const F_MarisaStar & star);

	float getAngleSpawn(int index);

	void registerParticleBatch(Feintgine::ParticleBatch2D * particleBatch);

	void registerAudioEngine(Feintgine::AudioEngine * audioEngine);


private :

	Feintgine::AudioEngine * m_audioEngine;

	Feintgine::ParticleBatch2D * m_hitParticleBatch = nullptr;

	glm::vec2 m_pos;

	std::vector<F_MarisaStar *> m_stars;

	Feintgine::F_AnimatedObject m_starAnim;

	int m_count = 0;
	int m_index = 0;

	float m_spawnRate = 0.0f;

	float m_angleDelta = 0.0f;

	float m_spawnCounter = 0.0f;
};

