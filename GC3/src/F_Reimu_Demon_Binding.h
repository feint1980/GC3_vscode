#pragma once
#include <F_Sprite.h>
#include <SpriteBatch.h>
#include <LightBatch.h>
#include <feint_common.h>
#include <F_AnimatedObject.h>
#include <AudioEngine.h>
#include <Camera2D.h>
#include <AfterImageParticle.h>
#include "EnemyBulletBase.h"
#include "F_EnemyBasic.h"
#include "FairyBase.h"
class F_Reimu_Demon_Binding
{
public:
	F_Reimu_Demon_Binding();
	~F_Reimu_Demon_Binding();

 	void init(const std::string & animationPath, const std::string & animationSupportPath , const glm::vec2 & pos,
 		const glm::vec2 dim, const Feintgine::Color & color);

	void setLifeTime(float lifetime);

	void registerSound(Feintgine::AudioEngine * audioEngine);

	void draw(Feintgine::SpriteBatch & spriteBatch);

	void drawLight(Feintgine::LightBatch & lightBatch);

	void update(float deltaTime, std::vector<FairyBase *>  enemy, std::vector<EnemyBulletBase * > bullets);

	bool isAlive() const { return  m_isAlive; }

	bool isVisible() const { return m_isVisible; }

	bool checkColliderWithEnemyBullet(const EnemyBulletBase & bullet);

	bool checkColliderWithEnemy(const F_BaseEnemy & bullet);

	glm::vec2 getPos() const { return m_pos; }

	glm::vec2 * getOffsetPosPointer()
	{
		return &m_offsetPos;
	}

	glm::vec2 * getPosPointer()
	{
		return &m_pos;
	}

	void registerCamera(Feintgine::Camera2D * camera);
	

private :

	glm::vec2 m_pos;
	glm::vec2 m_offsetPos;
	//glm::vec2 m_vel;
	glm::vec2 m_dim;
	//Feintgine::F_Sprite m_sprite;

	float m_lifeTime;

	bool m_isVisible = false;

	bool m_isPeak = false;

	Feintgine::F_AnimatedObject m_animObj;
	Feintgine::F_AnimatedObject m_helper;
	Feintgine::F_AnimatedObject m_animObj2;

	Feintgine::SoundEffect m_castSound;
	Feintgine::SoundEffect m_loopSound;
	Feintgine::SoundEffect m_endSound;

	Feintgine::Camera2D * m_camera;

	glm::vec3 m_attentionua;
	glm::vec3 t_attentionua;

	AfterImageObject m_afterImageParticle;

	Feintgine::Color m_color;
	bool m_isAlive = true;
};

