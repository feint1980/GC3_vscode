

#include "Window.h"
#include "Error.h"
//#include <api/GL/wglext.h>
#include "feint_common.h"
#include "A_Context_saver.h"
namespace Feintgine{



	
	Window::Window()
	{
	}


	Window::~Window()
	{
	}
	void Window::setPos(int x, int y)
	{
		SDL_SetWindowPosition(m_sdlWindow, x, y);
	}
	int Window::create(const std::string &windowName, int screenWidth, int screenHeight, unsigned int windowFlag)
	{


		int i;

		// Declare display mode structure to be filled in.
		SDL_DisplayMode current;

		SDL_Init(SDL_INIT_VIDEO);

		// Get current display mode of all displays.
		for (i = 0; i < SDL_GetNumVideoDisplays(); ++i) {

			int should_be_zero = SDL_GetCurrentDisplayMode(i, &current);

			if (should_be_zero != 0)
			{
				// In case of error...
				SDL_Log("Could not get display mode for video display #%d: %s", i, SDL_GetError());
			}

			else
			{
				// On success, print the current display mode.
				SDL_Log("Display #%d: current display mode is %dx%dpx @ %dhz.", i, current.w, current.h, current.refresh_rate);
			}

		}
		int defaultDisplay = 0;
		SDL_Log("Use display %d as main display", defaultDisplay);

 		


		if (glContext)
		{
			std::cout << "destroy old context \n";
			SDL_GL_DeleteContext(glContext);
		}
		SDL_DisplayMode DM;
		SDL_GetDesktopDisplayMode(0, &DM);
		//SDL_GetCurrentDisplayMode(0, &DM);
		auto Width = DM.w;
		auto Height = DM.h;
		m_screenHeight = screenHeight;
		m_screenWidth = screenWidth;
		m_resolutionWidth = Width;
		m_resolutionHeight = Height;
		m_refreshRate = DM.refresh_rate;

		feint_common::Instance()->setResolution(glm::vec2(m_screenWidth, m_screenHeight));
// 		if (windowFlag & FULLSCREEN)
// 		{
// 			std::cout << "calculate new solution \n";
// 			m_screenWidth = m_resolutionWidth;
// 			m_screenHeight = m_resolutionHeight;
// 		}
		
		m_aspectRatio =  (float)m_screenWidth /(float)m_resolutionWidth;
		std::cout << "new aspect is " << m_aspectRatio << "\n";

		Uint32 flags = SDL_WINDOW_OPENGL;
		flags |= SDL_WINDOW_ALLOW_HIGHDPI;
		if (windowFlag & INVISIBLE)
		{
			flags |= SDL_WINDOW_HIDDEN;

		}
		if (windowFlag & FULLSCREEN)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}

		if (windowFlag & BORDERLESS)
		{
			flags |= SDL_WINDOW_BORDERLESS;
		}
		
		m_sdlWindow = SDL_CreateWindow(windowName.c_str(), 10, 30, m_screenWidth, m_screenHeight, flags);
		int w;
		int h;
		//SDL_SetWindowSize(m_sdlWindow, 1280, 720);
		SDL_GetWindowSize(m_sdlWindow, &w, &h);
		std::cout << "created at " << w << " and " << h << "\n";
		
		
		
		if (m_sdlWindow == nullptr)
		{
			fatalError("ko tao dc , chac thieu RAM !");
			F_Logger::Instance()->writeLog("ko tao dc , chac thieu RAM !");
		}
	 
		glContext = SDL_GL_CreateContext(m_sdlWindow);
		if (glContext == nullptr)
		{
			fatalError("ko tao dc context OPENGL , chac card cui` ! ");
			F_Logger::Instance()->writeLog("ko tao dc context OPENGL , chac card cui` ! ");
		}
		GLenum error = glewInit();
		if (error != GLEW_OK)
		{
			fatalError("glew co van de ");
			F_Logger::Instance()->writeLog("glew co van de ");
		}
		std::cout << "context is " << glContext << "\n";
		// F_Logger::Instance()->writeLog("context is " + std::to_string((int)glContext));
		// F_Logger::Instance()->writeLog("Window create has no problem");

		glClearColor(0, 0, 0, 0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		A_Context_saver::getContext_saver()->saveContext(m_sdlWindow,glContext);
		
		std::cout << "init window OK \n";

// 		PFNWGLSWAPINTERVALEXTPROC       wglSwapIntervalEXT = NULL;
// 		PFNWGLGETSWAPINTERVALEXTPROC    wglGetSwapIntervalEXT = NULL;
// 		SDL_Log("Init Vsync for application");
// 		if (WGLExtensionSupported("WGL_EXT_swap_control"))
// 		{
// 			SDL_Log("WGLExtensionSupported !");
// 			// 			// Extension is supported, init pointers.
// 			wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
// 			// 
// 			// 			// this is another function from WGL_EXT_swap_control extension
// 			wglGetSwapIntervalEXT = (PFNWGLGETSWAPINTERVALEXTPROC)wglGetProcAddress("wglGetSwapIntervalEXT");
// 		}
// 		wglSwapIntervalEXT(0);

		return 0;
	}
	void Window::swapBuffer()
	{

		SDL_GL_SwapWindow(m_sdlWindow);
	}

	void Window::loadContext(SDL_GLContext context)
	{
		glContext = context;
		SDL_GL_MakeCurrent(m_sdlWindow, glContext);
		std::cout << "context load is " << glContext << "\n";
		
	}

	void Window::deleteWindow()
	{
		
		SDL_DestroyWindow(m_sdlWindow);
	}


 	bool Window::WGLExtensionSupported(const char *extension_name)
 	{
		SDL_Log("WGLExtensionSupported start ");
		// this is pointer to function which returns pointer to string with list of all wgl extensions
/*		PFNWGLGETEXTENSIONSSTRINGEXTPROC _wglGetExtensionsStringEXT = NULL;

		// determine pointer to wglGetExtensionsStringEXT function
		_wglGetExtensionsStringEXT = (PFNWGLGETEXTENSIONSSTRINGEXTPROC)wglGetProcAddress("wglGetExtensionsStringEXT");

		if (strstr(_wglGetExtensionsStringEXT(), extension_name) == NULL)
		{
			// string was not found
			return false;
		}

		// extension is supported
		return true;*/
		return false; // not support for now
 	}


	void Window::saveContext(SDL_GLContext context)
	{
		m_savedContext = context;
	}

	void Window::storageCamPos(glm::vec2 pos)
	{
		m_cameraStorePos = pos;
	}

}