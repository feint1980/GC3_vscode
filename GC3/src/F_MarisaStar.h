#pragma once
#include <F_AnimatedObject.h>
#include <LightBatch.h>
#include <ParticleBatch2D.h>
#include "EnemyBulletBase.h"

#include "AfterImageParticle.h"

#include "F_BaseEnemy.h"
#include "FairyBase.h"
#include <AudioEngine.h>
class F_MarisaStar
{
public:
	F_MarisaStar();
	~F_MarisaStar();

	void init(const glm::vec2 & scale, const Feintgine::F_AnimatedObject & animation,
		const Feintgine::Color & color,const glm::vec2 & vel,const glm::vec2 & pos,int afterImageCount, float afterImageRate);

	void registerAudioEngine(Feintgine::AudioEngine * audioEngine);

	void loadStarSound(const std::string & filePath);

	void loadEndSound(const std::string & filePath);

	void draw(Feintgine::SpriteBatch & spriteBatch);

	void drawLight(Feintgine::LightBatch & lightBatch);

	void update(float deltaTime, std::vector<FairyBase *>  enemy,
		std::vector<EnemyBulletBase * > bullets);

	void updateColor(float deltaTime);

	void setVel(const glm::vec2 & vel);

	//bool isAlive() const {return m_lifeTime > 0; }

	void destroy();

	bool isDestroy() const { return m_isDestroy; }

	bool isRemoved() const { return m_isRemove; }

	void registerParticleBatch(Feintgine::ParticleBatch2D * particleBatch);

	void setNumberOfParticle(int val);


	bool checkColliderWithEnemyBullet(const EnemyBulletBase & bullet);


	void setLifeTime(float val);

	bool checkColliderWithEnemy(const F_BaseEnemy & enemy);


	protected:
	Feintgine::F_AnimatedObject m_animation;
	glm::vec2 m_pos;
	glm::vec2 m_scale;
	Feintgine::Color m_color;

	glm::vec2 * p_pos;

	int m_numberOfSpark = 8;

	glm::vec3 m_attentionua;// = glm::vec3(15.0f, 22.5f, 24.0f);
	
	glm::vec3 m_sparkAttenua = glm::vec3(8.0f, 14.0f, 7.0f);
	glm::vec3 t_sparkAttenua ;

	glm::vec3 t_attentionua;

	float m_lifeTime = 6.2f;

	float m_alphaTime = 1.0f;

	float m_angle;

	bool m_isDestroy = false;

	bool m_isRemove = false;

	bool m_hasInited = false;

	float randomScale;
	float randomR;
	float randomG;
	float randomB;

	Feintgine::ParticleBatch2D * m_hitParticleBatch = nullptr;

	glm::vec2 m_vel;
	glm::vec2 m_acce = glm::vec2(1);

	AfterImageObject m_afterImageParticle;

	Feintgine::AudioEngine * m_audioEngine = nullptr;

	Feintgine::SoundEffect m_startSound;

	Feintgine::SoundEffect m_endSound;
};

