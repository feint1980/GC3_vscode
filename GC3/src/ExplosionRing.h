#pragma once
#include <glm/glm.hpp>
#include <F_Sprite.h>

class ExplosionRing
{
public:
	ExplosionRing();
	~ExplosionRing();

	ExplosionRing(const Feintgine::F_Sprite & sprite, const glm::vec2 & pos,
		const glm::vec2 & scale, const glm::vec2 & explosionRate, const Feintgine::Color & color, float depth,float liveRate);

	void init(const Feintgine::F_Sprite & sprite, const glm::vec2 & pos, 
		const glm::vec2 & scale, const glm::vec2 & explosionRate, const Feintgine::Color & color,float depth);

	void draw(Feintgine::SpriteBatch & spriteBatch);
	

	void update(float deltaTime);
	float lifeTime = 1.0f;
private :

	glm::vec2 m_pos;
	glm::vec2 m_scale;
	glm::vec2 m_explosionRate;
	Feintgine::F_Sprite m_sprite;

	float m_depth;
	
	float m_liveRate;

	Feintgine::Color m_color;

};

