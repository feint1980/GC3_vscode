#ifndef F_UVOBJECT_H
#define F_UVOBJECT_H 
#include "F_Sprite.h"
#include "SpriteBatch.h"
#include <iostream>
#include "GLTexture.h"

namespace Feintgine{


class F_UVObject
{
public:
	F_UVObject() = default;

	~F_UVObject() = default;

	void init(const F_Sprite & sprite, const glm::vec2 & pos, const glm::vec2 & scalingFactor,const Feintgine::Color & color);

	void init(const GLTexture & texture, const glm::vec2 & pos, const glm::vec2 & scalingFactor, const Feintgine::Color & color);

	void setPos(const glm::vec2 & pos);

	void setScaleWithActualSize(const glm::vec2 & dim);

	void setScale(const glm::vec2 & scale);

	void setColor(const Feintgine::Color & color);

	glm::vec2 getPos() const { return m_pos; }

	glm::vec2 getScale() const { return m_scale; }

	void draw(Feintgine::SpriteBatch & spriteBatch);

	F_Sprite getSprite() const { return m_sprite; }

	Feintgine::Color getColor() const { return m_color; }

	void setDepth(float depth) { m_depth = depth; }

	void setAngle(float angle) { m_angle = angle; }

	void update(float deltaTime);


private :

	F_Sprite m_sprite;

	glm::vec2 m_pos;
	glm::vec2 m_scale;

	glm::vec4 m_uv;
	glm::vec4 m_trackUV;

	GLTexture m_texture;

	float timer = 0;

	Feintgine::Color m_color;
	float m_depth;
	float m_angle = 0;
	float m_trackUVYCrop = 1.2f;

};

}
#endif