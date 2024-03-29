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

	void TextureCache::uploadBuffer(const std::string & filePath, const GLTexture & texture)
	{
		auto it = _textureMap.find(filePath);
		if(it != _textureMap.end())
		{
			it->second = texture;
		}
		

	}

	GLTexture TextureCache::getTexture(const std::string & filePath)
	{

		auto map_interator = _textureMap.find(filePath);

		if (map_interator == _textureMap.end())
		{
			GLTexture generator = ImageLoader::loadPNG(filePath);
	
			_textureMap.insert(std::make_pair(filePath, generator));
			//m_mutex_s.unlock();
			return generator;
		}

		return map_interator->second;


	}
}
