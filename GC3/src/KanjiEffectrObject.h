#pragma once
#include <SpriteBatch.h>
#include <F_Sprite.h>
#include <feint_common.h>


const int EFFECT_FLAG_SCALE_UP = 1;
const int EFFECT_FLAG_GLOW_UP = 2;

class KanjiEffectrObject
{
public:
	KanjiEffectrObject();
	~KanjiEffectrObject();
	
	void init(const glm::vec2 & pos, const Feintgine::F_Sprite & sprite, const glm::vec2 dim,
		const Feintgine::Color & color, const glm::vec2 & scale, float angle);

	void setLifeTime(float val);

	void draw(Feintgine::SpriteBatch & spriteBatch);

	void setFlag(int val);

	void setShake(float time, float freq);

	float getLifeTime() const { return m_lifeTime; }

	virtual void update(float deltaTime);

	void updateShake(float deltaTime);

	void setAlphaRate(float val);

	void setDepth(float dep);

	void setLifeTimeRate(float val);

private:


	float m_depth;

	float m_alphaRate;

	int m_effectFlag = 0;

	Feintgine::Color m_color;
	glm::vec2 m_pos;

	float m_angle;
	glm::vec2 m_scale;

	float m_lifeTimeRate;
	float m_lifeTime;

	Feintgine::F_Sprite m_sprite;

	float m_shakeTime;

	float m_shakeFreq;

	glm::vec2 m_dim;

};

