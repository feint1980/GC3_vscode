#pragma once

#include "F_Orreries_Sun.h"

class F_Player_Sun_Manager
{
public:
	F_Player_Sun_Manager();
	~F_Player_Sun_Manager();




	void update(const glm::vec2 &  pos, float deltaTime, std::vector<FairyBase *>  enemies,
		std::vector<EnemyGuardian *> guardians, std::vector<EnemyAmplifier *> amplifiers, std::vector<EnemyBulletBase * > bullets);

	void draw(Feintgine::SpriteBatch & spriteBatch);

	void drawLight(Feintgine::LightBatch & lightBatch);


	void setFocus(bool value);

	void setFire(bool value);


	void init(const glm::vec2 & pos);

	void spawn(int count, float lifeTime);

	void activeNondirectionLaser();

	Feintgine::Color getSunColor(int index);

	void handleFire(float deltaTime);

	void handleBullets();

	void offLaser();
	void setParticle(Feintgine::ParticleBatch2D * particleBatch);

	//void spawn(float time);


	void registerAudioEngine(Feintgine::AudioEngine * audioEngine);
private:

	glm::vec2 m_pos;

	float m_angle;
	float m_radius = 45.0f;
	float t_radius;

	float m_lifeTime;

	float m_angleRate = 0.1f;

	float m_angleRate_nonDirect = 1.0f;

	float m_additionalRad = 40.0f; 


	bool m_isFocus = false;

	bool m_isFire = false;

	bool m_isNonDirectionLaser = false;

	float m_balanceUnfocusRate = 1.0f;
	float m_balancefocusRate = 1.0f;


	float m_fireThreshold = 2.5f;
	float m_fireRate = 0.1f;  
	float m_fireCount = 0.0f;

	std::vector<F_Orreries_Sun *> m_suns;
	std::vector<F_Orreries_Sun *> m_refSuns;

	Feintgine::ParticleBatch2D * m_particleBatch;

	std::vector<F_BulletStraight *> m_bullets;

	Feintgine::AudioEngine * m_audioEngine;

	Feintgine::SoundEffect m_startSound;
	
};

