#include "TextureCache.h"
#include "ImageLoader.h"
#include <iostream>

namespace Feintgine{

	TextureCache::TextureCache()
	{
	}


	TextureCache::~TextureCache()
	{
	}

	GLTexture TextureCache::getTexture(std::string filePath)
	{

		auto map_interator = _textureMap.find(filePath);

		if (map_interator == _textureMap.end())
		{
			GLTexture generator = ImageLoader::loadPNG(filePath);

			_textureMap.insert(std::make_pair(filePath, generator));

			

			return generator;
		}

		return map_interator->second;


	}
}
