#pragma once
#include <GLTexture.h>
#include <ResourceManager.h>
#include <SpriteBatch.h>
#include "F_BulletStraight.h"
#include "F_HomingBullet.h"
#include <iostream>
#include "F_BaseEnemy.h"
#include <ParticleBatch2D.h>
#include <SpriteManager.h>
#include <F_Sprite.h>
#include <LightBatch.h>
#include "F_MarisaRocket_small.h"

#include "F_MarisaLaser.h"
#include "F_ReimuWave.h"
#include "EnemyAmplifier.h"



const int BULLET_TYPE_REIMU_HOMING = 1;
const int BULLET_TYPE_MARISA_ROCKET = 2;
const int BULLET_TYPE_REIMU_NEEDLE = 3;
const int BULLET_TYPE_MARISA_LASER = 4;


class F_PlayerAccessory
{
public:
	F_PlayerAccessory();
	~F_PlayerAccessory();

	void init(const glm::vec2 & pos, const glm::vec2 & dim, const Feintgine::F_Sprite & sprite,bool isLeft = true);

	void draw(Feintgine::SpriteBatch & spriteBatch);

	void drawLight(Feintgine::LightBatch & lightBatch);

	void drawDebug(Feintgine::DebugRender & renderer);

	void update(float deltaTime, std::vector<FairyBase *>  enemies);

	void setBoolRotate(bool val);

	bool isRorate() const { return m_isRotate; }

	void setBoolFocus(bool val);

	void setPos(const glm::vec2 & pos);

	void setType(int val);

	void setFire(bool val);

	glm::vec2 getOffsetedPos();

	glm::vec2 getOffsetPosFocus();


	void setBulletType(int val);

	glm::vec2 getPos() const { return m_pos; }


	void clearBullet();

	void initLaser(const Feintgine::GLTexture & texture, const glm::vec2 & pos, const glm::vec2 & dim,
		const Feintgine::Color & color, float depth, float angle, float dps , const Feintgine::F_Sprite & starSprite);

	void initFocusLaser(const Feintgine::GLTexture & texture, const glm::vec2 & pos, const glm::vec2 & dim,
		const Feintgine::Color & color, float depth, float angle, float dps, const Feintgine::F_Sprite & starSprite);
	Feintgine::ParticleBatch2D * getParticleBatch() const { return m_particleBatch; };

	bool changeColor(int channel, float rate, float maxVal);

	void resetStack();

	void setParentColor(bool val);

	std::vector<F_BulletBase *> getBullets();

	void syncLaser(float deltaTime);

	void setLaserEnergy(float value);

	float getLaserEnergy();

	glm::vec2 getRocketDirection(std::vector<FairyBase *> enemies);

	//void setEnemyPointer(F_EnemyBasic * emeny);

	protected:


	F_BaseEnemy * getNearstEnemy(const glm::vec2 & pos, std::vector<FairyBase *> enemy);

	EnemyAmplifier * getNearstAmplifier(const glm::vec2 & pos, std::vector<EnemyAmplifier *> enemy);

	Feintgine::F_Sprite m_sprite;
	Feintgine::Color m_color = Feintgine::Color(255,255,255,255);

	Feintgine::ParticleBatch2D * m_particleBatch;

	float m_angle;
	glm::vec2 m_pos;
	glm::vec2 m_additionalPos = glm::vec2(0);
	glm::vec2 m_dims;
	float m_depth;
	//int m_direction = 1;

	bool m_isRotate;
	bool m_isFocus; 
	bool m_isLeft;

	int m_type = 1;
	float m_stack = 0.0f;
	float maxStack = 1.0f;

	float m_rotSpeed = 0.075f;

	float destination = -10.5f;

	float offsetX = 17.5f;
	float savedOffset;
	float turnRate =0.0f;

	std::vector<F_HomingBullet *> m_bullets;
	std::vector<F_MarisaRocket_small *> m_bullets_a;
	std::vector<F_ReimuWave *> m_bullets_b;

	float m_energy;


	bool m_isFire = false;

	glm::vec4 desRect;

	glm::vec3 m_attentionua;
	glm::vec3 t_attentionua;
	glm::vec3 f_attentionua;


	float fireRate = 0.0f;
	float delayBullet = 0.34f;

	bool resetFirerate = false;

	int m_bulletType = 1;

	F_MarisaLaser m_laser;
	F_MarisaLaser m_laserFocus;

	bool isLaserOff = false;
	bool isFocusLaserOff = false;

	bool isParentColor = false;

	bool isPeak = false;

	//Feintgine::Color m_firingColor;

	//F_EnemyBasic * m_enemy = nullptr;
};

