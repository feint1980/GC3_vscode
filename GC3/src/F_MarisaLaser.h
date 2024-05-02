#pragma once
#include "GC3_EmptyObject.h"
#include "F_Sprite.h"
#include "F_SpriteObject.h"
#include <ParticleBatch2D.h>
class F_BaseEnemy;
class EnemyGuardian;
class EnemyAmplifier;
class FairyBase;

//class Feintgine::ParticleBatch2D;

class F_MarisaLaser
{
public:
	F_MarisaLaser();
	~F_MarisaLaser();


	void init(const Feintgine::GLTexture & texture ,const glm::vec2 & pos, const glm::vec2 & dim,
		const Feintgine::Color & color, float depth, float angle, float dps, const Feintgine::F_Sprite & starSprite,float dmg);

	void draw(Feintgine::SpriteBatch & spriteBatch);

	void update(float deltaTime, const glm::vec2 pos, std::vector<FairyBase *>  enemies,
		std::vector<EnemyGuardian *> guardians, std::vector<EnemyAmplifier *> amplifiers, bool updateColor = true);


	bool checkColiderWithEmeny(const F_BaseEnemy & enemy);

	bool checkColiderWithGuardian(const EnemyGuardian & enemy);

	bool checkColiderWithAmplifier(const EnemyAmplifier & enemy);

	void drawHitbox(Feintgine::DebugRender & debugRenderer);

	void updateUV(float deltaTime);

	bool isVisible() const { return m_isVisible; }

	void setVisible(bool val);

	void setMaxMinColorVal(float t_max, float t_min);

	void drawStar(Feintgine::SpriteBatch & spriteBatch);

	void drawRayLight(Feintgine::LightBatch & lightBatch);

	void setStarScale(float val);

	void setAlpha(float val);

	void setAttenuation(const glm::vec3 & atten);

	void setRotation(float value);

	float getEnergy();

	void setEnergy(float energy);

	void updateEnergyBar(float deltaTime);

	void toggleSwitchEnergy();

	void setParticle(Feintgine::ParticleBatch2D * particleBatch);

	void createParticle(F_BaseEnemy * enemy);

	void updateEnergyLocked(float deltaTime);

	void setColorRate(const glm::vec3 & colorRate);

	void setSparkAttenuation(const glm::vec3 & color);

	//void setAttenuation(const glm::vec3 & atten);

private:

	bool m_isSwitchHappen;
	bool m_isVisible;
	Feintgine::GLTexture  m_texture;
	glm::vec2 m_pos;
	glm::vec2 m_dim;
	Feintgine::Color m_color;
	float m_depth;
	float m_angle;
	float m_dps;

	float m_energyChangeTimer;

	float m_particleCooldown = 0.0f;


	//bool isReady = fa

	bool m_isLowPower = false;

	float m_rateR = 1.0f;
	float m_rateG = 1.0f;
	float m_rateB = 1.0f;

	float m_pernaltyRate = 1.0f;


	float m_energy = 8.0f;
	float m_energyCounter = 0.0f;
	bool m_energySwitching = false;

	bool m_energyLocked = false;

	float m_dmg;

	F_SpriteObject m_spriteObject;
	float updateUVRate = 0.035f;

	float m_rotation = degreeToRad(-90.0f);

	Feintgine::ParticleBatch2D * m_particleBatch ;

	//glm::vec3(20.0f, 11.0f, 5.0f);
	glm::vec3 m_attenuation = glm::vec3(20.0f, 11.0f, 5.0f);


	glm::vec3 t_attenuation;


	glm::vec3 m_sparkAttenuation = glm::vec3(7.0f, 5.0f, 12.0f);
	glm::vec3 t_sparkAttenuation;

	float m_starAngle = 0.0f;
	Feintgine::F_Sprite m_starSprite;

	float maxColorVal;
	float minColorVal;

	float m_starScale = 1.0f;
	glm::vec4 m_uvrect;// = glm::vec4(0.0f, 0.0f, 5.0f, 1.0f);


	
};

