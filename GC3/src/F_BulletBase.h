#pragma once
#include <SpriteBatch.h>
#include <GLTexture.h>
#include "F_EnemyBasic.h"
#include "ParticleBatch2D.h"
#include <F_Sprite.h>
#include "GuardianShield.h"
#include "EnemyAmplifier.h"
#include <EffectBatch.h>
class EnemyGuardian;

class F_BulletBase
{
public:
	F_BulletBase();

	~F_BulletBase();

	void init(const glm::vec2 & pos, const glm::vec2 & dim, const Feintgine::Color & color,
		const Feintgine::F_Sprite & sprite, float depth,float dmg,
		Feintgine::ParticleBatch2D * hitParticleBatch = nullptr);



	void init(const glm::vec2 & pos, const glm::vec2 & dim, const Feintgine::Color & color,
		const Feintgine::F_AnimatedObject & animation, float depth, float dmg, 
		Feintgine::ParticleBatch2D * hitParticleBatch = nullptr);

	void init(const glm::vec2 & pos, const glm::vec2 & dim, const Feintgine::Color & color,
		const std::string & animationPath, float depth, float dmg,
		Feintgine::ParticleBatch2D * hitParticleBatch = nullptr);

	void setBulletAnimationAction(const std::string & actionName);

	void setBulletAnimationAngle(float angle);

	virtual void draw(Feintgine::SpriteBatch & spriteBatch);

	virtual void drawLight(Feintgine::LightBatch & lightBatch);

	void setAlpha(float val);

	void setDamage(float dmg);

	bool checkColiderWithEmeny(const F_BaseEnemy & enemy );

	bool checkColiderWithGuardian(const EnemyGuardian & enemy);

	bool checkColiderWithAmplifier(const EnemyAmplifier & enemy);

	void setScale(const glm::vec2 & scale);

	virtual void update(float deltaTime, std::vector<FairyBase *> enemy,
		std::vector<EnemyGuardian *> guardians, std::vector<EnemyAmplifier *> amplifiers) = 0;

	bool isAlive() const { return m_isAlive; }

	void setLifeTime(float time);

	void setAlive(bool val);

	virtual void destroy();

	glm::vec2 getPos() const { return m_pos; }

	glm::vec2 getDim() const { return m_dims; }

	bool isDone() const { return m_isDone; }

	void setVel(const glm::vec2 & vel);

	void setDestroyAnimName(const std::string & name);

	void setAttenuation(const glm::vec3 & atten);

	bool isFreezed() const { return m_isFreezed; }

	void setFreeze(bool value) { m_isFreezed = value; }

protected:
	glm::vec2 m_pos;
	glm::vec2 m_dims;
	//glm::vec2 m_vel;
	Feintgine::F_Sprite  m_sprite;
	Feintgine::Color m_color;


	bool m_isFreezed = false;

	

	glm::vec3 m_attentionua = glm::vec3(4, 4, 4);
	float m_angle;
	float m_depth;
	float m_lifeTime = 3.0f;
	bool m_isAlive = true;
	glm::vec2 m_scale = glm::vec2(1);

	Feintgine::F_AnimatedObject m_animation;

	std::string m_destroyAnimName;

	bool m_isAnimated = false;

	Feintgine::ParticleBatch2D * m_particleBatch = nullptr;

	int m_particleType = 0;



	bool m_isDone = false;

	//std::vector<F_EnemyBasic> * m_enemies;
	
	float m_damage = 0.0f;

	glm::vec2 m_vel = glm::vec2(0.0f, 30.0f);
};

