#ifndef _IMAGELOADER_H_
#define _IMAGELOADER_H_

#include "GLTexture.h"
#include <string>
#include "IOManager.h"
#include "picoPNG.h"

#include "Error.h"

namespace Feintgine
{

	class ImageLoader
	{
	public:
		static GLTexture loadPNG(const std::string & filePath);
	};
}

#endif 