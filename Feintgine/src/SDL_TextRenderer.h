#ifndef SDL_TEXTRENDERER_H_
#define SDL_TEXTRENDERER_H_

#include "SDL2/SDL_ttf.h"
#include <string>

namespace Feintgine {



	class SDL_TextRenderer
	{

	public:
		void init(const std::string & filePath, int size);

		void dispose();


	};
}

#endif 
