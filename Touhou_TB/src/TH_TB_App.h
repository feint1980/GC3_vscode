#pragma once 


#include <IMainGame.h>
#include "TestTBScreen.h"
#include "LoginScene.h"
#include "LoginSceneV2.h"

class TH_TB_App : public Feintgine::IMainGame
{
public:
    TH_TB_App();
    ~TH_TB_App();

    virtual void onInit() override;
    virtual void addScreen() override;
    virtual void onExit() override;

private:

    std::unique_ptr<TestTBScreen> m_test = nullptr;
    std::unique_ptr<LoginScene> m_login = nullptr;
    std::unique_ptr<LoginSceneV2> m_loginV2 = nullptr;

};

