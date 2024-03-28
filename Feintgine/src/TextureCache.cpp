#include "TextureCache.h"
#include "ImageLoader.h"
#include <iostream>

namespace Feintgine{

	std::mutex  TextureCache:: m_mutex_s;
	TextureCache::TextureCache()
	{
	}


	TextureCache::~TextureCache()
	{
	}

	GLTexture TextureCache::getTexture(const std::string & filePath)
	{

		auto map_interator = _textureMap.find(filePath);

		if (map_interator == _textureMap.end())
		{
			GLTexture generator = ImageLoader::loadPNG(filePath);
			m_mutex_s.lock();
			_textureMap.insert(std::make_pair(filePath, generator));
			m_mutex_s.unlock();
			return generator;
		}

		return map_interator->second;


	}
}
