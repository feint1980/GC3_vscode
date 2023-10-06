#include "KanjiEffectrObject.h"



//const float LIFE_TIME_RATE = 0.1f;

KanjiEffectrObject::KanjiEffectrObject()
{
}


KanjiEffectrObject::~KanjiEffectrObject()
{
}

void KanjiEffectrObject::init(const glm::vec2 & pos, const Feintgine::F_Sprite & sprite, 
	const glm::vec2 dim, const Feintgine::Color & color, const glm::vec2 & scale, float angle)
{
	m_sprite = sprite;
	m_pos = pos;
	m_dim = dim;
	m_scale = scale;
	m_color = color;
	m_angle = angle;
	m_depth = 10.0f;
	
}

void KanjiEffectrObject::setLifeTime(float val)
{
	m_lifeTime = val;
}

void KanjiEffectrObject::draw(Feintgine::SpriteBatch & spriteBatch)
{
	if (m_lifeTime > 0)
	{
		glm::vec4 desRect;
		desRect.x = m_pos.x - (m_sprite.getDim().x * m_scale.x) / 2.0f;
		desRect.y = m_pos.y - (m_sprite.getDim().y * m_scale.y) / 2.0f;
		desRect.z = m_sprite.getDim().x  * m_scale.x;
		desRect.w = m_sprite.getDim().y  * m_scale.y;
		spriteBatch.draw(desRect, m_sprite.getUV(), m_sprite.getTexture().id, 10, m_color, m_angle);
		//std::cout << "showing \n";
	}
}

void KanjiEffectrObject::setFlag(int val)
{
	m_effectFlag = val;
}


void KanjiEffectrObject::setShake(float time, float freq)
{
	m_shakeTime = time;
	m_shakeFreq = freq;
}

void KanjiEffectrObject::update(float deltaTime)
{
	//std::cout << "showing \n";
	if (m_lifeTime > 0)
	{
		//std::cout << "alive  \n";
		//std::cout << m_lifeTime << "\n";
		m_lifeTime -= m_lifeTimeRate * deltaTime;
		if (m_lifeTime < 1.0f)
		{
			m_color.a = m_lifeTime * m_alphaRate;
		}
	}
	// Has scale up effect
	if (m_effectFlag & EFFECT_FLAG_SCALE_UP)
	{
		m_scale += m_lifeTimeRate * deltaTime;
	}
	// Has glow up effect
	if (m_effectFlag & EFFECT_FLAG_GLOW_UP)
	{
		//std::cout << "update glow " << m_color.r << "\n";
		m_color.change(15, .022f *deltaTime, 400);
	}

	updateShake(deltaTime);


}

void KanjiEffectrObject::updateShake(float deltaTime)
{
	if (m_shakeTime > 0.0f)
	{
		m_shakeTime -= 0.1f * deltaTime;
		glm::vec2 randomPos = glm::vec2(feint_common::Instance()->randomFloat(-m_shakeFreq, m_shakeFreq), feint_common::Instance()->randomFloat(-m_shakeFreq, m_shakeFreq));
		randomPos += m_pos;
		m_pos = randomPos;

	}
}

void KanjiEffectrObject::setAlphaRate(float val)
{
	m_alphaRate = val;
	m_color.a *= m_alphaRate;
}

void KanjiEffectrObject::setDepth(float dep)
{
	m_depth = dep;
}

void KanjiEffectrObject::setLifeTimeRate(float val)
{
	m_lifeTimeRate = val;
}

