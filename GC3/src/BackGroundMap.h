#pragma once
#include <SpriteBatch.h>

#include <ResourceManager.h>
#include <GLTexture.h>

class BackGroundMap
{
public:
	BackGroundMap();
	~BackGroundMap();


	void init(const Feintgine::GLTexture & texture ,const glm::vec2 & pos, const glm::vec2 & dim);

	void draw(Feintgine::SpriteBatch & spriteBatch);

	void setColor(const Feintgine::Color & color);

	void update(float deltaTime);
	void resetUV();

	Feintgine::Color getColor() const { return m_color; }
	
	bool changeColor(int channel, float rate, float maxVal);
		

private:


	Feintgine::GLTexture m_texture;
	Feintgine::Color m_color = Feintgine::Color(255, 255, 255, 255);
	glm::vec4 m_uv = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec2 m_pos;
	glm::vec2 m_dims;

};

