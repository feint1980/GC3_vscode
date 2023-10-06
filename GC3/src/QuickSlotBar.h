#pragma once
#include <SpriteBatch.h>
#include <glm/glm.hpp>
#include <GLTexture.h>

class QuickSlotBar
{
public:
	QuickSlotBar();
	~QuickSlotBar();
	void init(glm::vec2 & pos, glm::vec2 & dim, int slots);
	void draw(Feintgine::SpriteBatch & spriteBatch);
	private:
		glm::vec2 m_pos;
		glm::vec2 m_dim;
		Feintgine::Color mcolor;
		Feintgine::GLTexture m_texture;
};

