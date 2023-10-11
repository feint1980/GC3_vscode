#include "App.h"
#include <ScreenList.h>
#include "DataManager.h"
App::App()
{

}


App::~App()
{

	std::cout << "exit \n";
}


void App::onInit()
{
	
	
	
}


void App::addScreen()
{
// 	m_mainmenuScreen = std::make_unique<MainMenuScreen>(&m_window);

 	//m_screenList->addScreen(m_mainmenuScreen.get());

///	m_selectScreen = std::make_unique<SelectScreen>(&m_window);

//	m_higanScreen = std::make_unique<HiganMainMenuScreen>(&m_window);

//	m_shaderToy = std::make_unique<ShaderToy>(&m_window);

//	m_paternTest = std::make_unique<PaternTestScreen>(&m_window);

//	m_testCharScreen = std::make_unique<CharacterTestScreen>(&m_window);


	m_extraDemo = std::make_unique<Extra_DemoScreen>(&m_window);

//	m_testRenderScreen = std::make_unique<TestRenderScreen>(&m_window);

	m_3dScreen = std::make_unique<TestRender3D>(&m_window);

//	m_screenList->addScreen(m_selectScreen.get());

//	m_demo = std::make_unique <DemoScreen>(&m_window);

//	m_replayScreen = std::make_unique<ReplayScreen>(&m_window);

//	m_screenList->addScreen(m_testCharScreen.get());

	m_screenList->addScreen(m_3dScreen.get());
	
//	m_screenList->addScreen(m_higanScreen.get());

//	m_screenList->addScreen(m_shaderToy.get());
//	m_screenList->addScreen(m_paternTest.get());

	m_screenList->addScreen(m_extraDemo.get());
//	m_screenList->addScreen(m_replayScreen.get());

//	m_screenList->addScreen(m_testRenderScreen.get());

	//m_screenList->addScreen(m_newModelScreen.get());
	//m_screenList->addScreen(m_demo.get());

//	m_test2 = std::make_unique <DemoScreen2>(&m_window)m;

//	m_screenList->addScreen(m_test2.get());

 //	m_test = std::make_unique<TestScreeb>(&m_window);
// 
 	//m_screenList->addScreen(m_test.get());
	

	// Main test screen
	//m_screenList->setScreen(m_shaderToy->getScreenIndex());

	// Test Render screen
	//m_screenList->setScreen(m_testRenderScreen->getScreenIndex());


	// Demo screen
	//m_screenList->setScreen(m_extraDemo->getScreenIndex());


	// Replay screen
	//m_screenList->setScreen(m_replayScreen->getScreenIndex());

	// 3D screen
	m_screenList->setScreen(m_3dScreen->getScreenIndex());



	//m_screenList->setScreen(m_selectScreen->getScreenIndex());
	std::cout << " called here \n";
}
void App::onExit()
{

}
