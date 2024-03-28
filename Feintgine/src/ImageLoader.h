#ifndef _IMAGELOADER_H_
#define _IMAGELOADER_H_

#include "GLTexture.h"
#include <string>
#include "IOManager.h"
#include "picoPNG.h"
#include <mutex>

#include "Error.h"

#include "Window.h"
#include "A_Context_saver.h"


namespace Feintgine
{

	class ImageLoader
	{
	public:
		static GLTexture loadPNG(const std::string & filePath);
		private:
		static std::mutex m_mutex_t;
	};
}

#endif 