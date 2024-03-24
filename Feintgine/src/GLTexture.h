#ifndef _GLTEXTURE_H_
#define _GLTEXTURE_H_

#include <GL/glew.h>
#include <atomic>
namespace Feintgine
{

	struct GLTexture{
		GLuint id;
		int width;
		int height;

	};

	struct a_GLTexture{
		std::atomic <GLuint> id;
		std::atomic <int> width;
		std::atomic <int> height;
	};
}
#endif