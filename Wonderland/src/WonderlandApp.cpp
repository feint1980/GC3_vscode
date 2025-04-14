#include "WonderlandApp.h"
#include <ScreenList.h>


WonderlandApp::WonderlandApp()
{

}


WonderlandApp::~WonderlandApp() 
{   

    std::cout << "exit \n";
}


void WonderlandApp::onInit()
{
    // todosmake
    
    configureScreen("Wonderland", 1280, 720, 0,false);
    setScreenInMiddle();
    
}


void WonderlandApp::addScreen()
{
    m_loginV2 = std::make_unique<Wonderland_MainMenu>(&m_window);

    m_screenList->addScreen(m_loginV2.get());

    m_home = std::make_unique<HomeScene>(&m_window);

    m_screenList->addScreen(m_home.get());

    m_test = std::make_unique<TestTBScreen>(&m_window); 
    m_screenList->addScreen(m_test.get());

    m_screenList->setScreen(m_loginV2->getScreenIndex());
}


void WonderlandApp::onExit()
{

}