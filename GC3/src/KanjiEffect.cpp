#include "KanjiEffect.h"



KanjiEffect::KanjiEffect()
{
}


KanjiEffect::~KanjiEffect()
{
}

void KanjiEffect::init(const Feintgine::F_Sprite & sprite, const glm::vec2 & pos, const Feintgine::Color & color)
{
	m_pos = pos;
	m_sprite = sprite;
	m_color = color;
	m_fadeScaleText.init(m_pos, m_sprite, m_sprite.getDim(), Feintgine::Color(255, 10, 10, 255), glm::vec2(0.8), 0);
	m_fadeScaleText.setLifeTime(2.5f);
	m_fadeScaleText.setLifeTimeRate(0.125f);
	m_fadeScaleText.setFlag(1);
	m_fadeScaleText.setAlphaRate(0.6f);


	m_presentText.init(m_pos, m_sprite, m_sprite.getDim(), Feintgine::Color(255,10,10,255), glm::vec2(0.8), 0);
	m_presentText.setLifeTime(12.7f);
	m_presentText.setLifeTimeRate(0.125f);
	m_presentText.setFlag(0);
	m_presentText.setAlphaRate(1.0f);
	m_presentText.setShake(12.7, 0.1f);

	m_centerText.init(m_pos, m_sprite, m_sprite.getDim(), Feintgine::Color(0, 0, 0, 255), glm::vec2(0.72), 0);
	m_centerText.setLifeTime(12.7f);
	m_centerText.setLifeTimeRate(0.125f);
	m_centerText.setFlag(2);
	m_centerText.setAlphaRate(.1f);
	m_centerText.setDepth(22.0f);
	m_centerText.setShake(12.7, 0.2f);



// 	m_presentText.init(m_pos, m_sprite, m_sprite.getDim(), Feintgine::Color(255, 0, 0, 255), glm::vec2(0.8), 0);
// 	m_presentText.setLifeTime(22.7f);
// 	m_presentText.setLifeTimeRate(0.18f);
// 	m_presentText.setFlag(0);
// 	m_presentText.setAlphaRate(1.0f);
// 
// 
// 	m_centerText.init(m_pos, m_sprite, m_sprite.getDim(), Feintgine::Color(0, 0, 0, 255), glm::vec2(0.72), 0);
// 	m_centerText.setLifeTime(22.7f);
// 	m_centerText.setLifeTimeRate(0.18f);
// 	m_centerText.setFlag(2);
// 	m_centerText.setAlphaRate(.1f);
// 	m_centerText.setDepth(22.0f);
	//m_centerText.set


	


}

void KanjiEffect::draw(Feintgine::SpriteBatch & spriteBatch)
{
	if (m_fadeScaleText.getLifeTime() > 0.0f)
	{
		m_fadeScaleText.draw(spriteBatch);
	}
	
	if (m_presentText.getLifeTime() > 0.0f)
	{
		m_presentText.draw(spriteBatch);
	}

	if (m_centerText.getLifeTime() > 0.0f)
	{
		m_centerText.draw(spriteBatch);
	}

}

void KanjiEffect::update(float deltaTime)
{
	if (m_fadeScaleText.getLifeTime() > 0.0f)
	{
		m_fadeScaleText.update(deltaTime);
	}
	if (m_presentText.getLifeTime() > 0.0f)
	{
		m_presentText.update(deltaTime);
	}

	if (m_centerText.getLifeTime() > 0.0f)
	{
		m_centerText.update(deltaTime);
		//m_centerText.updateShake(deltaTime);
	}
	//m_centerText.setP


}

bool KanjiEffect::isAlive()
{
	return (m_fadeScaleText.getLifeTime() + m_presentText.getLifeTime() + m_centerText.getLifeTime() > 0.0f);
}
