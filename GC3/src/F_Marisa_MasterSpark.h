#pragma once
#include "F_Sprite.h"

#include <LightBatch.h>

#include "F_MasterSpark_Wave.h"

#include "EnemyBulletBase.h"

#include "F_BaseEnemy.h"

#include <AudioEngine.h>

class F_Marisa_MasterSpark
{
public:
	F_Marisa_MasterSpark();
	~F_Marisa_MasterSpark();

	void setAngle(float angle);


	void draw(Feintgine::SpriteBatch & spriteBatch);

	void drawRayLight(Feintgine::LightBatch & lightBatch);

	void init(const glm::vec2 & scale, const Feintgine::F_Sprite & textureName,
		const Feintgine::Color & color);

	void registerAudioEngine(Feintgine::AudioEngine * audioEngine);


	bool checkColliderWithEnemyBullet(const EnemyBulletBase & bullet);

	bool checkColliderWithEnemy(const F_BaseEnemy & enemy);
	
	void update(float deltaTime, std::vector<F_BaseEnemy *>  enemy,
		std::vector<EnemyBulletBase * > bullets);

	void updateState(float deltaTime);

	void updateScale(float deltaTime);

	void spawn();

	void handleWave(float deltaTime);

	glm::vec2 rotatePoint(const glm::vec2& pos, float angle);

	float getLifeTime() const { return m_lifeTime; }

private:

	glm::vec3 m_attenuation = glm::vec3(20.0f, 8.0f, 5.0f);


	//float t_lifeTime = 30.0f;
	glm::vec3 t_attenuation = m_attenuation;

	std::vector<F_MasterSpark_Wave> m_waves;

	float m_spawnWaveCount = 0.0f;

	bool m_isVisible = false;
	bool m_isSwitchHappen = false;
	bool m_isSwitchSizeHappen = false;

	Feintgine::F_Sprite m_sprite;
	glm::vec2 m_scale;

	glm::vec2 c_scale;

	glm::vec2 m_pos;

	glm::vec4 desRect;

	Feintgine::Color m_color = Feintgine::Color(255, 255, 255, 255);

	float m_angle = 0.0;

	float m_tScaleMax = 2.9f;

	float maxColorVal = 1.0f;
	float minColorVal = -0.0001f;

	Feintgine::SoundEffect m_startSound;

	float m_lifeTime = 1.0f;

};

