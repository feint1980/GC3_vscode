#include <windows.h>
#include "IMainGame.h"
#include "Timing.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include "F_oEvent.h"
#include "F_ScreenCapture.h"

namespace Feintgine
{
	IMainGame::IMainGame()
	{
		m_screenList = std::make_unique<ScreenList>(this);
	}


	IMainGame::~IMainGame()
	{
	}

	void IMainGame::run()
	{

		if (!init())
		{
			return;
		}
		FpsLimiter limiter;
		limiter.setMaxFPS(ENGINE_targetFPS);
		Uint32 prevTicks = SDL_GetTicks();
		m_isRunning = true;

		
		while (m_isRunning)
		{
			
			Uint32 newTicks = SDL_GetTicks();
			Uint32 frameTime = newTicks - prevTicks;
			prevTicks = newTicks;
			
			float totalDeltaTime =  frameTime / (MS_PER_SECOND / ENGINE_targetFPS);
			
// 			if (SDL_GetNumVideoDisplays() > 1)
// 			{
// 				index = SDL_GetWindowDisplayIndex(m_window.getWindow());
// 			}
// 			
// 			
// 			SDL_GetCurrentDisplayMode(index, &m_current);

			
			while (totalDeltaTime > 0.0f)
			{
			
				float deltaTime = std::min(totalDeltaTime,1.0f);
				//std::cout << "delta time " << deltaTime << "\n";
							
				update(deltaTime);
				totalDeltaTime -= deltaTime;
				checkInput();
				
			}
			
			
// 			SDL_Event evnt;
// 			while (SDL_PollEvent(&evnt))
// 			{
// 				onSDLEvent(evnt);
// 			}
			m_inputManager.update();

			//m_drawThreads.emplace_back([&] {
			//	draw();
			//});

			//for (auto& t : m_drawThreads)
			//{
			//	if (t.joinable())
			//	{
			//		t.join();
			//	}
			//}

			//F_ScreenCapture::Instance()->saveData();
			
			draw();
			fps = limiter.end();
			m_window.swapBuffer();
									
		}
	}
	void IMainGame::exitGame()
	{
		m_screenList->onExit();

		if (m_screenList)
		{
			m_screenList->destroy();
			m_screenList.reset();
		}
		m_isRunning = false;

	}

	bool IMainGame::init()
	{
		Feintgine::initFeint();
		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

		if (!initSystem())
		{
			return false;
		}
		
		onInit();

		addScreen();

		
		m_currentScreen = m_screenList->getCurrentGameScreen();
		m_currentScreen->onEntry();
		m_currentScreen->setRunning();
		
		
		return true;

	}
	bool IMainGame::initSystem()
	{
		// 1366 x 768
		// 1920 x 1080

		m_window.create("GC3", 1366, 768, 0);

		return true;
	}

	void IMainGame::update(float deltaTime)
	{
		if (m_currentScreen)
		{
			switch (m_currentScreen->getState())
			{ 
			case ScreenState::RUNNING :
				if (ENGINE_isGameRunning)
				{				
					m_currentScreen->update(deltaTime);
				}
				
				
				break;
			case ScreenState::CHANGE_NEXT:
				m_currentScreen->onExit();
				m_currentScreen = m_screenList->moveNext();
				if (m_currentScreen)
				{
					m_currentScreen->setRunning();
					m_currentScreen->onEntry();
				}
				break;

			case ScreenState::CHANGE_PREVIOUS:
				m_currentScreen->onExit();
				m_currentScreen = m_screenList->movePrevious();
				if (m_currentScreen)
				{
					m_currentScreen->setRunning();
					m_currentScreen->onEntry();
				}
				break;
			case ScreenState::EXIT_APPLICATION:
				exitGame();
				break;


			default:
				break;
			}
		}
		else
		{
			exitGame();
		}
	}
	void IMainGame::draw()
	{

		if (m_currentScreen && m_currentScreen->getState() == ScreenState::RUNNING)
		{
			m_currentScreen->draw();
		}
	}

	void IMainGame::checkInput()
	{
		m_currentScreen->checkInput();
	}

	void IMainGame::onSDLEvent(SDL_Event & evnt)
	{
		switch (evnt.type) {
		
		
		case SDL_WINDOWEVENT_CLOSE:
			exitGame();
			break;
		case SDL_QUIT:
			exitGame();
			break;
		case SDL_MOUSEMOTION:
			m_inputManager.setMouseCoords((float)evnt.motion.x, (float)evnt.motion.y);
			break;
		case SDL_KEYDOWN:
			m_inputManager.pressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			m_inputManager.releaseKey(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			m_inputManager.pressKey(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			m_inputManager.releaseKey(evnt.button.button);
			break;
		}
		if (evnt.key.keysym.scancode)
		{
			anykey = true;
		}
		else
		{
			anykey = false;
		}
	
		
	}


	void IMainGame::updateTimer(float deltaTime)
	{

	}

	void IMainGame::configureScreen(std::string name, int screenWidth, int screenHeight, int t_flag, bool saveContext)
	{
		SDL_GLContext context = m_window.getGLContext();
	
		
		m_window.deleteWindow();	
		m_window.create(name, screenWidth, screenHeight, t_flag);
		if (saveContext)
		{
			m_window.loadContext(context);
		}
	//	m_window.setPos( SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
		
	}
	void IMainGame::setScreenInMiddle()
	{
		m_window.setPos( SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	}

}

