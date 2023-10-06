#include "SimpleObject.h"



SimpleObject::SimpleObject()
{
}


SimpleObject::~SimpleObject()
{
}
void SimpleObject::init(const glm::vec2 & pos, const glm::vec2 & dimentions, Feintgine::GLTexture & texture, Feintgine::Color color, const glm::vec2 & tileDims)
{
	m_pos = pos;
	m_dims = dimentions;
	m_texture.init(texture, tileDims);
	m_color = color;


}
void SimpleObject::changeColor(Feintgine::Color &color)
{
	m_color = color;
}
void SimpleObject::setPos(const glm::vec2 & pos)
{
	m_pos = pos;
}

void SimpleObject::destroy()
{

}
void SimpleObject::drawDebug(Feintgine::DebugRender & renderer)
{
	glm::vec4 destRect;
	destRect.x = m_pos.x - m_dims.x / 2.0f;
	destRect.y = m_pos.y - m_dims.y / 2.0f;
	destRect.z = m_dims.x;
	destRect.w = m_dims.y;

	glm::vec4 outerBox;
	outerBox.x = m_pos.x - m_dims.x * 1.5;
	outerBox.y = m_pos.y - m_dims.y * 1.5;
	outerBox.z = m_dims.x * 3.0f;
	outerBox.w = m_dims.y * 3.0f;

	renderer.drawBox(destRect, Feintgine::Color(0, 0, 255, 255), 0);
	renderer.drawBox(outerBox, Feintgine::Color(255, 0, 255, 255), 0);
}

void SimpleObject::draw(Feintgine::SpriteBatch & spriteBatch)
{
	glm::vec4 destRect;
	destRect.x = m_pos.x - m_dims.x / 2.0f;
	destRect.y = m_pos.y - m_dims.y /2.0f ;
	destRect.z = m_dims.x;
	destRect.w = m_dims.y;

	glm::vec4 uvRect = m_texture.getUVs(tileIndex);

	if (m_direction == -1) {

		uvRect.x += 1.0f / m_texture.dims.x;
		uvRect.z *= -1;
	}
	// Draw the sprite
	spriteBatch.draw(destRect, uvRect, m_texture.texture.id, m_depth, m_color,  1.0f);
}
void SimpleObject::setDirection(const int d)
{
	m_direction = d;
}

void SimpleObject::setDepth(float depth)
{
	m_depth = depth;
}
