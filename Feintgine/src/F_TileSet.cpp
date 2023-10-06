#include "F_TileSet.h"


namespace Feintgine
{



	F_TileSet::F_TileSet()
	{

	}

	F_TileSet::~F_TileSet()
	{

	}

	void F_TileSet::initData(const GLTexture & texture)
	{
		m_texture = texture;
		m_textureDim = glm::vec2(m_texture.width, m_texture.height);
		
	}

	void F_TileSet::draw(SpriteBatch & spriteBatch)
	{
		for (int i = 0; i < m_parts.size(); i++)
		{
			m_parts[i].draw(spriteBatch);
		}
	}

	void F_TileSet::update(float deltaTime)
	{
		for (int i = 0; i < m_parts.size(); i++)
		{
			m_parts[i].update(deltaTime);
		}
	}

	glm::vec4 F_TileSet::calculateUV(int i_x, int i_y)
	{
		glm::vec4 uv(0, 0, 1, 1);
		
		float t_x = 16.0 * i_x;
		float t_y = 16.0 * i_y;

		uv.x = t_x / m_texture.width;
		uv.y = (t_y / m_texture.height ) ;
		uv.z = 16.0 / m_texture.width;
		uv.w = 16.0 / m_texture.height;

		return uv;
	}


	glm::vec2 F_TileSet::calculateJump(int keyFrame)
	{
		glm::vec2 jump = glm::vec2(0);
		float jumpScale = m_texture.width / keyFrame;
		jump.x = jumpScale / m_texture.width;
		return jump;
	}

	void F_TileSet::loadData()
	{
		glm::vec2 t_pos = glm::vec2(0);
// 		F_TilePart part;
// 		part.create(t_pos, glm::vec2(16), calculateUV(0, 0), calculateJump(3), m_texture);
// 		m_parts.push_back(part);
// 		t_pos.x += 16.0;
// 		part.create(t_pos, glm::vec2(16), calculateUV(1, 0), calculateJump(3), m_texture);
// 		m_parts.push_back(part);
// 		t_pos.x += 16.0;
// 		part.create(t_pos, glm::vec2(16), calculateUV(2, 0), calculateJump(3), m_texture);
// 		m_parts.push_back(part);
// 		t_pos.x += 16.0;
// 		part.create(t_pos, glm::vec2(16), calculateUV(3, 0), calculateJump(3), m_texture);
// 		m_parts.push_back(part);
// 		t_pos.x -= 48;
// 		t_pos.y += 16;
// 		part.create(t_pos, glm::vec2(16), calculateUV(0, 1), calculateJump(3), m_texture);
// 		m_parts.push_back(part);
// 		t_pos.x += 16.0;
// 		part.create(t_pos, glm::vec2(16), calculateUV(1, 1), calculateJump(3), m_texture);
// 		m_parts.push_back(part);
// 		t_pos.x += 16.0;
// 		part.create(t_pos, glm::vec2(16), calculateUV(2, 1), calculateJump(3), m_texture);
// 		m_parts.push_back(part);
// 		t_pos.x += 16.0;
// 		part.create(t_pos, glm::vec2(16), calculateUV(3, 1), calculateJump(3), m_texture);
// 		m_parts.push_back(part);
// 		t_pos.x -= 48;
// 		t_pos.y += 16;
// 		part.create(t_pos, glm::vec2(16), calculateUV(0, 2), calculateJump(3), m_texture);
// 		m_parts.push_back(part);
// 		t_pos.x += 16.0;
// 		part.create(t_pos, glm::vec2(16), calculateUV(1, 2), calculateJump(3), m_texture);
// 		m_parts.push_back(part);
// 		t_pos.x += 16.0;
// 		part.create(t_pos, glm::vec2(16), calculateUV(2, 2), calculateJump(3), m_texture);
// 		m_parts.push_back(part);
// 		t_pos.x += 16.0;
// 		part.create(t_pos, glm::vec2(16), calculateUV(3, 2), calculateJump(3), m_texture);
// 		m_parts.push_back(part);
// 		t_pos.x -= 48;
// 		t_pos.y += 16;
// 		part.create(t_pos, glm::vec2(16), calculateUV(0, 3), calculateJump(3), m_texture);
// 		m_parts.push_back(part);
// 		t_pos.x += 16.0;
// 		part.create(t_pos, glm::vec2(16), calculateUV(1, 3), calculateJump(3), m_texture);
// 		m_parts.push_back(part);
// 		t_pos.x += 16.0;
// 		part.create(t_pos, glm::vec2(16), calculateUV(2, 3), calculateJump(3), m_texture);
// 		m_parts.push_back(part);
// 		t_pos.x += 16.0;
// 		part.create(t_pos, glm::vec2(16), calculateUV(3, 3), calculateJump(3), m_texture);
// 		m_parts.push_back(part);

		std::cout << "total " << m_parts.size() << " parts was added \n";
	}

}