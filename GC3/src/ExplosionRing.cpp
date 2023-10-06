#include "ExplosionRing.h"



ExplosionRing::ExplosionRing()
{
}


ExplosionRing::ExplosionRing(const Feintgine::F_Sprite & sprite, const glm::vec2 & pos, const glm::vec2 & scale, 
	const glm::vec2 & explosionRate, const Feintgine::Color & color, float depth,float liveRate = 0.1f)
{
	m_sprite = sprite;
	m_pos = pos;
	m_scale = scale;
	m_explosionRate = explosionRate;
	m_color = color;
	m_depth = depth;
	m_liveRate = liveRate;
	
}

ExplosionRing::~ExplosionRing()
{
}

void ExplosionRing::init(const Feintgine::F_Sprite & sprite, const glm::vec2 & pos, const glm::vec2 & scale,
	const glm::vec2 & explosionRate, const Feintgine::Color & color,float depth)
{
	m_sprite = sprite;
	m_pos = pos;
	m_scale = scale;
	m_explosionRate = explosionRate;
	m_color = color;
	m_depth = depth;
}

void ExplosionRing::draw(Feintgine::SpriteBatch & spriteBatch)
{
	glm::vec4 desRect;// (0, 0, 50, 50);
	desRect.x = (m_pos.x ) - (m_sprite.getDim().x * m_scale.x / 2.0f );
	desRect.y = (m_pos.y ) - (m_sprite.getDim().y * m_scale.y / 2.0f );
	desRect.z = m_sprite.getDim().x * m_scale.x;
	desRect.w = m_sprite.getDim().y * m_scale.y;

	spriteBatch.draw(desRect,m_sprite.getUV(), m_sprite.getTexture().id, m_depth, m_color 
		, 0);

}

void ExplosionRing::update(float deltaTime)
{
	if (lifeTime > 0)
	{
		lifeTime -= m_liveRate * deltaTime;
		m_scale += m_explosionRate * deltaTime;
		m_color.a = lifeTime;
	}
	
}

