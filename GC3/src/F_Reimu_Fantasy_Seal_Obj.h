#pragma once
#include <F_Sprite.h>
#include <SpriteBatch.h>
#include <LightBatch.h>
#include <feint_common.h>
#include <functional>
#include <ParticleBatch2D.h>
#include "ExplosionRing.h"
#include <AudioEngine.h>
#include "EnemyBulletBase.h"
#include "F_EnemyBasic.h"

#include <EffectBatch.h>
const int FANTASY_SEAL_BORDER = 350;
class F_Reimu_Fantasy_Seal_Obj
{
public:
	F_Reimu_Fantasy_Seal_Obj();
	~F_Reimu_Fantasy_Seal_Obj();

	void init(const Feintgine::F_Sprite & sprite , const glm::vec2 & pos, 
		const glm::vec2 dim, const Feintgine::Color & color);


	void registerEffectBatch(Feintgine::EffectBatch * effectBatch);

	void draw(Feintgine::SpriteBatch & spriteBatch);

	void drawLight(Feintgine::LightBatch & lightBatch);	

	void update(float deltaTime, std::vector<F_BaseEnemy *>  enemy, std::vector<EnemyBulletBase * > bullets);

	bool isAlive() const { return  m_isAlive; }

	void registerParticleBatch(Feintgine::ParticleBatch2D * particleBatch);

	void registerExplosionRing(std::vector<ExplosionRing> * rings);

	void setCircleAngle(float circleAngle);

	void setAttenuation(const glm::vec3 & attenuation);

	void registerAudioEngine(Feintgine::AudioEngine * audioEngine);

	void setDeathCallback(const std::function <void(void)>& f);

	F_BaseEnemy * getNearstEnemy(const glm::vec2 & pos, std::vector<F_BaseEnemy *> enemy);

	bool checkColliderWithEnemyBullet(const EnemyBulletBase & bullet);

	bool checkColliderWithEnemy(const F_BaseEnemy & enemy);

	void roll();

	void setLifeTime(float val, float randomRange);

	glm::vec4 getOrbColor(int num);

	glm::vec2 getPos() const { return m_pos; }
	
	void setLightID(int val);

	void setScale(float val);

	void setDMG(float val);


private:

	bool m_isExplode = false;

	bool m_isAlive = true;
	glm::vec2 m_pos;
	glm::vec2 m_vel;
	glm::vec2 m_dim;
	Feintgine::F_Sprite m_sprite;
	Feintgine::F_Sprite m_explosionSprite;

	Feintgine::SoundEffect m_end1;
	Feintgine::SoundEffect m_end2;
	Feintgine::SoundEffect m_end3;

	float m_dmg;

	float m_circleAngle = 0.0f;
	float m_circleRadius = 0.0f;

	bool isLocked = true;

	float m_lifeTime = 40.0f;
	float m_lifeTimeRate = 0.1f;

	bool isDecided = false;
	//glm::vec2 m_vel;

	glm::vec2 randomRad;

	float decideInterval = 0.0f;
	float m_scale = 2.0f;

	float m_lightScale = 0.0f;
	glm::vec3 t_attentionua;
	glm::vec3 m_attentionua;

	Feintgine::Color m_color;

	int lightID = 0;

	Feintgine::ParticleBatch2D * m_hitParticleBatch = nullptr;

	std::function <void(void)> m_deathCallback;

	Feintgine::EffectBatch * m_effectBatch = nullptr;

	std::vector<ExplosionRing> * m_exlosions = nullptr;
	//float m_depth;
};

