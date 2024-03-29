#ifndef _TEXTURECACHE_H_
#define _TEXTURECACHE_H_

#include <map>
#include "GLTexture.h"
#include <string>
#include <mutex>
#include <unordered_map>
#include <vector>
namespace Feintgine{

	
	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();
		GLTexture getTexture(const std::string & filePath);
		void uploadBuffer(const std::string & filePath, const GLTexture & texture);

	private:
		static std::mutex m_mutex_s;
		std::unordered_map<std::string, GLTexture> _textureMap;
		
	};
}
#endif