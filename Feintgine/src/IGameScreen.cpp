#include "IGameScreen.h"
#include <iostream>

namespace Feintgine
{


	IGameScreen::IGameScreen()
	{

	}
	IGameScreen::~IGameScreen()
	{

	}

	int IGameScreen::getNextScreenIndex() const
	 {
		return SCREEN_INDEX_NULL;
	 }
	int IGameScreen::getPreviousScreenIndex() const
	 {
		return SCREEN_INDEX_NULL;
	 }

	void IGameScreen::build()
	{

	}
	void IGameScreen::destroy()
	{

	}

	void IGameScreen::onEntry()
	{

	}
	void IGameScreen::onExit()
	{

	}

	void IGameScreen::update(float deltaTime)
	{
		
		
	}
	void IGameScreen::draw()
	{
	
	}

	
	void IGameScreen::checkInput()
	{

	}

	void IGameScreen::startScreen()
	{
		if (!startup)
		{
			m_alpha += FADE_SPEED;
			if (m_alpha >= 1)
			{
				startup = true;
			}
		}
		else
		{
			if (changeNext)
			{
				m_alpha -= FADE_SPEED;
				if (m_alpha <= 0)
				{
					m_currentState = ScreenState::CHANGE_NEXT;
					startup = false;
				}
			}
		}
	}

	void IGameScreen::changeNextScreen()
	{
		changeNext = true;

	}

	void IGameScreen::changePrevScreen()
	{
		changeBack = true;
	}

}