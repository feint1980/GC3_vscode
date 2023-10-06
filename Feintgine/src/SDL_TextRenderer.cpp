
#include "SDL_TextRenderer.h"
#include <iostream>
namespace Feintgine {
	void SDL_TextRenderer::init(const std::string & filePath, int size)
	{

		std::cout << "attemp to init SDL Text renderer \n";
		if (TTF_Init() < 0) {
			std::cout << "Error when init TTF \n";
		}
		int was_init = TTF_WasInit();	

		if (was_init == 1)
		{
			std::cout << "SDL Text renderer Init successfully \n";
		}
		else if (was_init == 0)
		{
			std::cout << "SDL Text renderer Init failed \n";
		}
	}

	void SDL_TextRenderer::dispose()
	{
		atexit(TTF_Quit);
	}

}
