#include "TH_TB_App.h"
#include <ScreenList.h>


TH_TB_App::TH_TB_App()
{

}


TH_TB_App::~TH_TB_App() 
{   

    std::cout << "exit \n";
}


void TH_TB_App::onInit()
{
    // todos
    configureScreen("TH TB", 1600, 900, 0,false);
    setScreenInMiddle();
    
}


void TH_TB_App::addScreen()
{

    m_login = std::make_unique<LoginScene>(&m_window);

    
    m_screenList->addScreen(m_login.get());

    m_loginV2 = std::make_unique<LoginSceneV2>(&m_window);

    m_screenList->addScreen(m_loginV2.get());

    m_test = std::make_unique<TestTBScreen>(&m_window); 
    m_screenList->addScreen(m_test.get());



    m_screenList->setScreen(m_loginV2->getScreenIndex());
}


void TH_TB_App::onExit()
{

}