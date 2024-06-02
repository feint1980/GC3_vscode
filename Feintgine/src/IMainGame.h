#ifndef _IMAINGAME_H_
#define _IMAINGAME_H_

#include <memory>
#include "ScreenList.h"
#include "Window.h"
#include "Feintgine.h"
#include "IGameScreen.h"
#include "InputManager.h"
#include "EngineSetting.h"

#include <thread>
#include <chrono>


const float ACCEPTABLE_LOST_FRAME = 55.0f;

const float MS_PER_SECOND = 1000;
const float TARGET_FRAMETIME = MS_PER_SECOND / 60;
namespace Feintgine
{
	class IGameScreen;

	class IMainGame
	{
	public:
		IMainGame();
		virtual ~IMainGame();
		bool anykey = false;
		void run();
		void exitGame();

		virtual void onInit() = 0;
		virtual void addScreen() = 0; 
		virtual void onExit() = 0;

		void onSDLEvent(SDL_Event & evnt);

		InputManager getInputManager()  { return m_inputManager; }


		const float getFps() const { return fps; }

		Window getWindow() const { return m_window; }

		void updateTimer(float deltaTime);

		void configureScreen(std::string name, int screenWidth, int screenHeight, int t_flag ,bool saveContext = false);
		void setScreenInMiddle();
		bool init();

		InputManager m_inputManager;
	protected:
		virtual void update(float deltaTime);
		virtual void draw();
		virtual void checkInput();

	
		bool initSystem();

		std::vector< std::thread >m_drawThreads;
		std::vector<std::thread> m_captureThreads;
		
		
		std::unique_ptr<ScreenList> m_screenList;
		IGameScreen * m_currentScreen = nullptr;
		bool m_isRunning = false;
		float fps;
		Window m_window;
		


		int convertedWidth;
		int convertedHeight;

		SDL_DisplayMode m_current;
		

		bool m_isLoaded = false;

	};
}
#endif


