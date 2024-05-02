#pragma once
#include "F_Sprite.h"

#include <LightBatch.h>

#include "EnemyBulletBase.h"

#include "F_BaseEnemy.h"
#include "FairyBase.h"
#include <AudioEngine.h>

class F_Non_Direction_Laser
{
public:
	F_Non_Direction_Laser();
	~F_Non_Direction_Laser();


	void init(const glm::vec2 & scale, const Feintgine::F_Sprite & sprite,
		const Feintgine::Color & color);

	void draw(Feintgine::SpriteBatch & spriteBatch);

	void drawRayLight(Feintgine::LightBatch & lightBatch);


	void update(const glm::vec2 &pos, float angle, float deltaTime, std::vector<FairyBase *>  enemy,
		std::vector<EnemyBulletBase * > bullets);

	//void setAngle(float angle);

	int getColorFlag(const Feintgine::Color & color);

	void registerAudioEngine(Feintgine::AudioEngine * audioEngine);

	void updateState(float deltaTime);

	void updateScale(float deltaTime);

	void spawn(float lifeTime);

	//glm::vec2 rotatePoint(const glm::vec2& pos, float angle);

	float getLifeTime() const { return m_lifeTime; }

	bool isVisible() const { return m_isVisible; }


	bool checkColliderWithEnemyBullet(const EnemyBulletBase & bullet);

	bool checkColliderWithEnemy(const F_BaseEnemy & enemy);


private : 

	bool m_isVisible = false;
	bool m_isSwitchHappen = false;
	bool m_isSwitchSizeHappen = false;


	glm::vec3 m_attenuation;// = glm::vec3(5.0f, 8.0f, 50.0f);

	glm::vec3 t_attenuation = m_attenuation;
	Feintgine::F_Sprite m_sprite;
	glm::vec2 m_scale;

	glm::vec2 c_scale;

	glm::vec2 m_pos;

	glm::vec4 desRect;

	Feintgine::Color m_color;
	Feintgine::Color t_color;

	float m_angle = 0.0;

	float m_tScaleMax = 2.9f;

	float maxColorVal = 0.6f;
	float minColorVal = -0.0001f;

	//Feintgine::SoundEffect m_startSound;

	int m_colorFlag = 0;

	float m_lifeTime = 1.0f;

};

