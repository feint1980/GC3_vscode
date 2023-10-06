#include "ReplayScreen.h"



ReplayScreen::ReplayScreen()
{
}

int ReplayScreen::getNextScreenIndex() const
{
	return 32;
}

ReplayScreen::ReplayScreen(Feintgine::Window * window)
{
	m_screenIndex = 33;
	std::cout << "number " << SHADER_TEST_MODE << "\n";
	m_window = window;
	m_alpha = 1;

	initShader();
	m_foregroundShader = &m_shader;
	m_backgroundShader = &m_whiteBlackShader;
}

void ReplayScreen::reloadLevel()
{
	m_player.loadRecord("test.txt");
	Extra_DemoScreen::reloadLevel();
	
	//std::cout << "reloadLevel \n";
}

ReplayScreen::~ReplayScreen()
{
}

