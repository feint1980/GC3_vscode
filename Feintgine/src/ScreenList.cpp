#include "ScreenList.h"
#include "IGameScreen.h"


namespace Feintgine
{
	ScreenList::ScreenList(IMainGame * game) :
		m_game(game)
	{

	}
	ScreenList::~ScreenList()
	{
		destroy();
	}

	IGameScreen*  ScreenList:: moveNext()
	{
		IGameScreen * currentGameScrren = getCurrentGameScreen();
		if (currentGameScrren->getNextScreenIndex() != SCREEN_INDEX_NULL)
		{
			m_currentScreenIndex = currentGameScrren->getNextScreenIndex();
		}
		return getCurrentGameScreen();

	}
	IGameScreen * ScreenList::movePrevious()
	{
		IGameScreen * currentGameScrren = getCurrentGameScreen();
		if (currentGameScrren->getPreviousScreenIndex() != SCREEN_INDEX_NULL)
		{
			m_currentScreenIndex = currentGameScrren->getPreviousScreenIndex();
		}
		return getCurrentGameScreen();

	}

	void ScreenList::setScreen(int nextScreen)
	{
		//std::cout << "setScreen " << nextScreen << "\n";
		m_currentScreenIndex = nextScreen;
	}

	void ScreenList::addScreen(IGameScreen * newScreen)
	{
		newScreen->m_screenIndex = m_screens.size();
		m_screens.push_back(newScreen);
		newScreen->build();
		newScreen->setParentGame(m_game);
	}

	void ScreenList::destroy()
	{
		for (int i = 0; i < m_screens.size(); i++)
		{
			m_screens[i]->destroy();
	
		}
		m_screens.resize(0);
		m_currentScreenIndex = SCREEN_INDEX_NULL;
	}
	IGameScreen * ScreenList::getCurrentGameScreen()
	{

		if (m_currentScreenIndex == SCREEN_INDEX_NULL)
		{
			return nullptr;
		}
		std::cout << "m_currentScreenIndex " << m_currentScreenIndex << "\n";
		return m_screens[m_currentScreenIndex];
	}
	void ScreenList::onExit()
	{

	}


}