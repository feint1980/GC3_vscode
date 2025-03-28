#pragma once
#include "SpriteBatch.h"
#include "GLSLProgram.h"
#include "Camera2D.h"
#include "GLTexture.h"
#include "DebugRender.h"
#include "LightBatch.h"

class EmptyObject
{
public:
	EmptyObject();
	~EmptyObject();
	void draw(Feintgine::SpriteBatch & spriteBatch);
	void drawLight(Feintgine::LightBatch & lightBatch);
	void drawBox(Feintgine::DebugRender & debugRenderer);
	void init(const Feintgine::GLTexture & texture ,const glm::vec2 & pos ,const glm::vec2 & dims, const Feintgine::Color & color);
	void setColor(const Feintgine::Color & color);
	glm::vec2 getPos() const { return m_pos; }
	glm::vec2 getDimentions() const { return m_dims; }
	void setAngle(float angle);

	void setAlpha(GLubyte alpha);

	void setDepth(float target);

	GLubyte getAlpha() const { return m_color.a; }

	void setPos(const glm::vec2 & pos) { m_pos = pos; }
	void setDim(const glm::vec2 & dims) { m_dims = dims; }
	float getAngle() const { return m_angle; }
	void setSPec(float intentse);


	float getSpec() const { return m_spec; }

	void expandingSize(const glm::vec2 & dimMax, const glm::vec2 & howfast);

	void fayde_spec(float min_spec , float max_spec, float fade_speed, bool loop = true);
	void end_spec(float min_spec, float fade_speed);
protected:
	float m_spec = 1.0f;
	float m_angle = 0;
	Feintgine::GLTexture m_texture;
	glm::vec2 m_pos;
	glm::vec2 m_dims;
	Feintgine::Color m_color;
	bool fayde ;
	float m_depth = 0.0f;
//	bool m_faydeMode = false;
	
};

