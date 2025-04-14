#pragma once 


#include <IMainGame.h>
#include "TestTBScreen.h"
#include "Wonderland_MainMenu.h"
#include "HomeScene.h"
class WonderlandApp : public Feintgine::IMainGame
{
public:
    WonderlandApp();
    ~WonderlandApp();

    virtual void onInit() override;
    virtual void addScreen() override;
    virtual void onExit() override;

private:

    std::unique_ptr<TestTBScreen> m_test = nullptr;
    std::unique_ptr<Wonderland_MainMenu> m_loginV2 = nullptr;
    std::unique_ptr<HomeScene> m_home = nullptr;

};

