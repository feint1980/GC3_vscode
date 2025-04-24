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
    m_mainMenu = std::make_unique<Wonderland_MainMenu>(&m_window);

    m_prototypeScene = std::make_unique<WonderlandPrototypeScene>(&m_window);

    m_screenList->addScreen(m_mainMenu.get());

    m_screenList->addScreen(m_prototypeScene.get());

    m_screenList->setScreen(m_prototypeScene->getScreenIndex());
}


void WonderlandApp::onExit()
{

}