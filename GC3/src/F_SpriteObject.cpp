#include "F_SpriteObject.h"



F_SpriteObject::F_SpriteObject()
{
}


F_SpriteObject::~F_SpriteObject()
{
}



void F_SpriteObject::init(const Feintgine::GLTexture & sprite, const glm::vec2 &pos, const glm::vec2 dim, float depth, float angle)
{
	//m_sprite = sprite;
	m_pos = pos;
	m_dim = dim;
	m_depth = depth;
	m_angle = angle;

	// debug log 
	//std::cout << "sprite name " << m_sprite.getName();
	//std::cout << "get texture dim " << feint_common::Instance()->convertiVec2toString(m_sprite.getTextureDim());

	//m_uv = m_sprite.getUV();
}

void F_SpriteObject::draw(Feintgine::SpriteBatch & spriteBatch)
{
	glm::vec4 desRect;

	//spriteBatch.draw(desRect, m_sprite.getUV(), m_sprite.getTexture().id, m_depth , m_color, m_angle);
}

void F_SpriteObject::updateUV(float deltaTime)
{
	m_uv;
}
