#include "EditorMain.h"


#include <ScreenList.h>
#include <fstream>

EditorMain::EditorMain()
{

}


EditorMain::~EditorMain()
{
	
}


void EditorMain::onInit()
{
	std::ifstream infile("config.cfg");
	int w, h;
	while (infile >> w >> h)
	{
		std::cout << w << "\t" << h << "\b";
	}
	configureScreen("Feint Editor", 1600, 900, 0,false);
	

	setScreenInMiddle();

}


void EditorMain::addScreen()
{
	m_screen = std::make_unique<EditorScreen>(&m_window);

	m_test = std::make_unique<TestCEGUIScreen>(&m_window);

	m_renderTest = std::make_unique<NewRenderModel>(&m_window);

	m_screenList->addScreen(m_screen.get());
	m_screenList->addScreen(m_test.get());
	m_screenList->addScreen(m_renderTest.get());
	//m_screenList->setScreen(m_renderTest->getScreenIndex());
	m_screenList->setScreen(m_screen->getScreenIndex());
	
}
void EditorMain::onExit()
{

}