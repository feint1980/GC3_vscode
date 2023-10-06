#pragma once
#include <F_AnimatedObject.h>
#include <SpriteBatch.h>
#include <LightBatch.h>
#include <AudioEngine.h>
#include "ExplosionRing.h"
#include <AfterImageParticle.h>
#include <functional>

#include "EnemyBulletBase.h"
#include "F_EnemyBasic.h"

class Yin_Yang_Orb
{
public:
	Yin_Yang_Orb();
	~Yin_Yang_Orb();

	void init( const std::string & animationPath,
		const Feintgine::Color & color, float scale);

	void spawn(const glm::vec2 & pos, float lifeTime, const glm::vec2 & vel);

	void draw(Feintgine::SpriteBatch & spriteBatch);

	void drawNoLight(Feintgine::SpriteBatch & spriteBatch);

	void drawLight(Feintgine::LightBatch & lightBatch);

	void update(float deltaTime, std::vector<F_BaseEnemy *>  enemy, std::vector<EnemyBulletBase * > bullets);

	void setDeathCallback(const std::function <void(void)>& f);

	//void registerExplosionRing(std::vector<ExplosionRing> * rings);

	void registerAudioEngine(Feintgine::AudioEngine * audioEngine);
	
	void setOffsetNoLight(const glm::vec2 & offset);

	bool checkColliderWithEnemyBullet(const EnemyBulletBase & bullet);

	bool checkColliderWithEnemyBulletOuter(const EnemyBulletBase & bullet);

	bool checkColliderWithEnemy(const F_BaseEnemy & enemy);

	glm::vec2 * getPosPointer()
	{
		return &m_pos;
	}

	void setDMG(float val);

protected:

	float suckScale;

	float m_dmg;

	glm::vec3 m_lightColor;

	glm::vec2 offsetNolight;

	glm::vec2 m_pos;

	glm::vec2 m_dim;

	float m_scale;

	glm::vec2 m_vel;

	float m_lifeTime;

	float m_angle;

	bool m_isAlive = false;

	bool m_isPeak = false;

	bool m_isVisible = false;

	bool isFinished = true;

	glm::vec3 m_attentionua;
	glm::vec3 t_attentionua;

	Feintgine::SoundEffect m_castSound;
	Feintgine::SoundEffect m_loopSound;
	Feintgine::SoundEffect m_endSound;

	std::function <void(void)> m_deathCallback;


	float colorRate = 1.0f;
	Feintgine::Color m_color;
	Feintgine::Color t_color;
	
	Feintgine::F_AnimatedObject m_animation;
	Feintgine::F_AnimatedObject m_animationFront;
	AfterImageObject m_afterImageParticle;


	std::vector<ExplosionRing> * m_exlosions;
	
};

