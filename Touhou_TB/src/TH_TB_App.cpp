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
    // todo

    configureScreen("TH TB", 1600, 900, 0,false);
}


void TH_TB_App::addScreen()
{
    m_test = std::make_unique<TestTBScreen>(&m_window); 
    m_screenList->addScreen(m_test.get());

    m_screenList->setScreen(m_test->getScreenIndex());


}

void TH_TB_App::onExit()
{

}