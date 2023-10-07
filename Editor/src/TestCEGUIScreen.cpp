#include "TestCEGUIScreen.h"



TestCEGUIScreen::TestCEGUIScreen()
{
}

TestCEGUIScreen::TestCEGUIScreen(Feintgine::Window * window)
{
	m_window = window;
	m_screenIndex = 2;
	
	
}

TestCEGUIScreen::~TestCEGUIScreen()
{
}

int TestCEGUIScreen::getNextScreenIndex() const
{
	return 4;
}

int TestCEGUIScreen::getPreviousScreenIndex() const
{
	return 4;
}

void TestCEGUIScreen::build()
{
	
}

void TestCEGUIScreen::destroy()
{
	
}

void TestCEGUIScreen::onEntry()
{
	std::cout << "soemthing \n";
	initGUI();
}

void TestCEGUIScreen::onExit()
{
	
}

void TestCEGUIScreen::update(float deltaTime)
{
	checkInput();
}

void TestCEGUIScreen::draw()
{
	m_gui.draw();
}

void TestCEGUIScreen::checkInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt))
	{
		m_gui.onSDLEvent(evnt);
		m_game->onSDLEvent(evnt);
	}
}

void TestCEGUIScreen::handleInput(Feintgine::InputManager & inputManager)
{

}

void TestCEGUIScreen::initGUI()
{
	m_gui.init("GUI");
	m_gui.loadScheme("TaharezLook.scheme");
	m_gui.loadScheme("VanillaSkin.scheme");
	m_gui.loadScheme("WindowsLook.scheme");

	m_gui.setFont("DejaVuSans-12");
	
	//CEGUI::ImagesetManager::getSingleton()
	
	//CEGUI:: ImagesetManager::getSingleton().createImagesetFromImageFile("ImageForStaticImage", "GPN-2000-001437.tga");
// 
// 	CEGUI::DefaultWindow * label = static_cast<CEGUI::DefaultWindow *>
// 		(m_gui.createWidget("TaharezLook/Label", glm::vec4(0.5, 0.5, 0.2f, 0.1f), glm::vec4(0.0f), "test"));
// 	label->setText("it works ");
	//m_gui.getContext()->setRootWindow(CEGUI::WindowManager::getSingleton().loadLayoutFromFile("feint.layout"));
	
}
