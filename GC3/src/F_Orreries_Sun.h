#pragma once
#include "F_PlayerAccessory.h"
#include <F_AnimatedObject.h>

#include "F_BulletStraight.h"
#include "F_MarisaLaser.h"
#include "F_Non_Direction_Laser.h"


class F_Orreries_Sun 
{
public:
	F_Orreries_Sun();
	~F_Orreries_Sun();


	void draw(Feintgine::SpriteBatch & spriteBatch);

	void setPos(const glm::vec2 & pos);

	void init(const std::string & animationPath, int id);

	void update(float deltaTime, std::vector<FairyBase *>  enemies,
		std::vector<EnemyBulletBase * > bullets);

	void initLaser(const Feintgine::GLTexture & texture, const glm::vec2 & pos,
		const glm::vec2 & dim, const Feintgine::Color & color, float depth, float angle, float dps,
		const Feintgine::F_Sprite & starSprite);

	void setLifeTime(float lifeTime);

// 	void initNonDirectLaser(const glm::vec2 & scale,
// 		const Feintgine::F_Sprite & sprite);

	void drawLight(Feintgine::LightBatch & lightBatch);

	void fireNonDirectionLaser();

	bool checkColliderWithEnemyBullet(const EnemyBulletBase & bullet);

	bool checkColliderWithEnemy(const F_BaseEnemy & enemy);

	void updateState(float deltaTime);

	void spawn(float time);

	bool isAlive() const { return m_isALive; }

	bool isDone() const { return m_isDone; }

	void updateMovement(float deltaTime);

	void fireNormal();

	void showLaser(bool val);

	void registerParticle(Feintgine::ParticleBatch2D * particleBatch);

	glm::vec4 getLaserColor(int num);

	Feintgine::Color getColor(int index);

	void setAngle(float angle);

	void registerAudioEngine(Feintgine::AudioEngine * audioEngine);

	std::vector<F_BulletStraight *> m_bullets;

	//void setRadius(float m_ra)

private : 



	F_MarisaLaser m_laser;

	glm::vec2 m_dim;
	Feintgine::F_AnimatedObject  m_animation;
	Feintgine::F_AnimatedObject m_bulletAnim; 

	glm::vec2 m_pos;
	glm::vec2 t_pos;
	glm::vec3 m_attentionua;
	glm::vec3 t_attentionua;
	float m_time;
	int m_id;
	
	float m_angle;

	float m_lifeTime;

	bool m_isVisible = false;
	bool m_isSwitchHappen = false;


	int m_hitCount = 0;

	glm::vec2 m_vector;//= t_pos - m_pos;

	bool m_isALive = false;
	bool m_isDestroy = false;
	bool m_isDone = false;
	//bool m_isSwitchSizeHappen = false;

	F_Non_Direction_Laser m_nonDirectionLaser;
	
	Feintgine::ParticleBatch2D * m_particleBatch;
	//F_PrimaryBullet m_primary;

	Feintgine::Color m_color;

	Feintgine::AudioEngine * m_audioEngine;

};

