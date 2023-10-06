#pragma once
#include "F_Sprite.h"
#include "feint_common.h"
class F_SpriteObject
{
public:
	F_SpriteObject();
	~F_SpriteObject();

	void init(const Feintgine::GLTexture & sprite, const glm::vec2 &pos , const glm::vec2 dim,
	float depth, float angle);

	void draw(Feintgine::SpriteBatch & spriteBatch);

	void updateUV(float deltaTime);

private :

	glm::vec4 m_uv;
	Feintgine::GLTexture  m_texture;
	glm::vec2 m_pos;
	glm::vec2 m_dim;
	Feintgine::Color m_color;
	float m_depth;
	float m_angle;

	float UV_updateRate = 0.1f;
	

};

