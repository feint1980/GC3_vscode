#pragma once
#include "F_BulletStraight.h"

#define RAD_90_DEGREE 1.57079633f
#define RAD_270_DEGREE 7.71238899f

#define MAX_SPEED 35.0f

class F_MarisaRocket_small : public F_BulletStraight
{
public:
 	F_MarisaRocket_small();
 	~F_MarisaRocket_small();
// 
// 	F_MarisaRocket_small(const glm::vec2 & pos, const glm::vec2 & dim, const Feintgine::Color & color,
// 		const std::string & animationPath, float depth, float dmg,
// 		Feintgine::ParticleBatch2D * hitParticleBatch = nullptr);

	virtual void update(float deltaTime, std::vector<FairyBase *> enemy) override;
	void setIsFocus(bool val);
	void setScale(float val);

	void setDirection(const glm::vec2 & direction);

	void setLightColoFlag(int colorFlag);

	virtual void draw(Feintgine::SpriteBatch & spriteBatch);

	void drawLight(Feintgine::LightBatch & lightBatch);

	virtual void destroy() override;

	void setParticleType(int type);
private :

	glm::vec3 f_attentionua;

	glm::vec4 m_lightColor;
	float accelerateRate = 0.5f;
	glm::vec2 m_direction;
	float m_speed = 1.0f;

	glm::vec2 m_lightPos;

	glm::vec2 m_additionPos;

	glm::vec2 t_additionPos;

	float m_calculatedAngle;

	bool m_isFocusRocket = false;
};

