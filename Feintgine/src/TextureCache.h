#ifndef _TEXTURECACHE_H_
#define _TEXTURECACHE_H_

#include <map>
#include "GLTexture.h"
#include <string>
namespace Feintgine{


	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();
		GLTexture getTexture(std::string filePath);
	private:
		std::map<std::string, GLTexture> _textureMap;
	};
}
#endif