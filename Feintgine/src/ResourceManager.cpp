#include "ResourceManager.h"

namespace Feintgine{

	TextureCache ResourceManager::_textureCache;

	IOFileCache ResourceManager::m_IOCache;

	GLTexture ResourceManager::getTexture(const std::string & filePath)
	{
		return _textureCache.getTexture(filePath);

	}


	void ResourceManager::rewriteTexture(const std::string & filePath, const GLTexture & texture)
	{
		_textureCache.uploadBuffer(filePath, texture);
	}

	std::vector<char> ResourceManager::getPreloadedFile(const std::string & filePath)
	{
		return m_IOCache.getBuffer(filePath);
	}

	std::vector<wchar_t> ResourceManager::getPreloadedFile(const std::string & filePath, bool isWchar)
	{
		return m_IOCache.getBuffer(filePath, isWchar);
	}
	

}
