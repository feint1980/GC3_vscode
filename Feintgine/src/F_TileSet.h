
#ifndef _F_TILESET_H_
#define _F_TILESET_H_

#include "F_TilePart.h"
#include <iostream>

namespace Feintgine
{

	class F_TileSet
	{
	public:
		F_TileSet();
		~F_TileSet();
		void initData(const GLTexture & texture);
		void draw(SpriteBatch & spriteBatch);
		void update(float deltaTime);
		glm::vec4 calculateUV(int i_x, int i_y);
		glm::vec2 calculateJump(int keyFrame);
		void loadData();

	private:

		GLTexture m_texture;
		std::vector<F_TilePart> m_parts;
		glm::vec2 m_textureDim;
		int row = 4;
		int collum = 12;
	};

}

#endif