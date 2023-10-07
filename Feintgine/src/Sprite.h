#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <GL/glew.h>
#include "Vertex.h"
#include "GLTexture.h"
#include <cstddef>
#include <string>

namespace Feintgine
{

	class Sprite
	{
	public:
		Sprite();
		~Sprite();

		void init(float x, float y, float width, float height, std::string texturePath);
		void draw();

	private:
		float _x;
		float _y;
		float _width;
		float _height;
		GLuint _vboID;
		Vertex vertexData[6];
		GLTexture _texture;


	};
}

#endif 